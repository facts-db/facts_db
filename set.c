/*
 *  facts_db - in-memory graph database
 *  Copyright 2020 Thomas de Grivel <thoxdg@gmail.com>
 *
 *  Permission to use, copy, modify, and distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "dbg_printf.h"
#include "set.h"

s_item *
new_item (void *data, long len)
{
  s_item *i = malloc(sizeof(s_item));
  if (i) {
    i->data = data;
    i->len = len;
  }
  return i;
}

int item_compare (void *a, void *b)
{
  int cmp;
  s_item *ia;
  s_item *ib;
  long l;
  dbg_printf("item_compare %p %p\n", a, b);
  if (a == b)
    return 0;
  if (!a)
    return -1;
  if (!b)
    return 1;
  ia = (s_item*) a;
  ib = (s_item*) b;
  if (ia->data == ib->data)
    return 0;
  l = ia->len < ib->len ? ia->len : ib->len;
  cmp = memcmp(ia->data, ib->data, l);
  dbg_printf("%c%c %c %c%c\n", ((char*)ia->data)[0],
             ((char*)ia->data)[1],
             cmp < 0 ? '<' : cmp > 0 ? '>' : '=',
             ((char*)ib->data)[0], ((char*)ib->data)[1]);
  dbg_printf("%i %i %c %i %i\n", ((char*)ia->data)[0],
             ((char*)ia->data)[1],
             cmp < 0 ? '<' : cmp > 0 ? '>' : '=',
             ((char*)ib->data)[0], ((char*)ib->data)[1]);
 if (cmp == 0) {
    if (ia->len < ib->len)
      cmp = -1;
    else if (ia->len > ib->len)
      cmp = 1;
  }
  return cmp;
}

int set_save (s_set *s, const char *path)
{
  FILE *fp;
  s_skiplist_node *n;
  assert(s);
  if (!(fp = fopen(path, "w")))
    return -1;
  n = skiplist_node_next(s->skiplist.head, 0);
  while (n) {
    s_item *item = (s_item*) n->value;
    if (fwrite(&item->len, sizeof(item->len), 1, fp) != 1)
      return -1;
    if (fwrite(item->data, item->len, 1, fp) != 1)
      return -1;
    n = skiplist_node_next(n, 0);
  }
  fflush(fp);
  fclose(fp);
  return 0;
}

int max (int a, int b)
{
  if (a < b)
    return b;
  return a;
}

void set_init (s_set *s)
{
  assert(s);
  dbg_printf("set_init %p\n", (void*) s);
  s->size = 0;
  skiplist_init(&s->skiplist, 16, 3.0);
  s->skiplist.compare = item_compare;
}

int set_read (s_set *s, const char *path)
{
  FILE *fp;
  int height;
  unsigned long i;
  s_skiplist_node *last;
  assert(s);
  assert(path);
  dbg_printf("set_open: path: \"%s\"\n", path);
  assert(s);
  s->size = 0;
  height = max(16, log(s->size) / log(3.0)) + 1;
  skiplist_init(&s->skiplist, height, 3.0);
  s->skiplist.compare = item_compare;
  if (!(fp = fopen(path, "r")))
    return -1;
  last = new_skiplist_node(NULL, s->skiplist.max_height);
  for (i = 0; i < s->skiplist.max_height; i++)
    skiplist_node_next(last, i) = s->skiplist.head;
  while (!feof(fp)) {
    uint64_t len;
    void *data;
    unsigned height;
    s_item *item;
    s_skiplist_node *n;
    if (fread(&len, sizeof(len), 1, fp) != 1)
      return -1;
    if (!(data = malloc(len)))
      return -1;
    if (fread(data, len, 1, fp) != 1)
      return -1;
    if (!(item = new_item(data, len)))
      return -1;
    height = skiplist_random_height(&s->skiplist);
    n = new_skiplist_node(item, height);
    for (i = 0; i < height; i++) {
      skiplist_node_next(n, i) = NULL;
      skiplist_node_next(skiplist_node_next(last, i), i) = n;
      skiplist_node_next(last, i) = n;
    }
    s->size++;
  }
  return 0;
}

s_item * set_find (s_set *s, void *data, long len)
{
  s_item item;
  s_skiplist_node *node;
  assert(s);
  assert(data);
  assert(len > 0);
  dbg_printf("set_find %p %p %ld\n", (void*) s, data, len);
  item.data = data;
  item.len = len;
  node = skiplist_find(&s->skiplist, &item);
  if (node) {
    s_item *item = (s_item*) node->value;
    return item;
  }
  return NULL;
}

s_item * set_insert_new (s_set *s, void *data, long len)
{
  s_item *item;
  dbg_printf("set_insert_new %p %p %ld\n", (void*) s, data, len);
  if (!(item = new_item(data, len)))
    return 0;
  skiplist_insert(&s->skiplist, item);
  s->size++;
  return item;
}

s_item * set_insert (s_set *s, void *data, long len)
{
  s_item *item;
  assert(s);
  assert(data);
  assert(len > 0);
  dbg_printf("set_insert %p %p %ld\n", (void*) s, data, len);
  item = set_find(s, data, len);
  if (item)
    return item;
  return set_insert_new(s, data, len);
}

void set_clear (s_set *s)
{
  unsigned long h;
  s_skiplist_node *n;
  assert(s);
  assert(s->skiplist.head);
  n = skiplist_node_next(s->skiplist.head, 0);
  for (h = 0; h < s->skiplist.head->height; h++)
    skiplist_node_next(s->skiplist.head, h) = NULL;
  s->skiplist.length = 0;
  s->size = 0;
  while (n) {
    s_skiplist_node *next = skiplist_node_next(n, 0);
    free(n->value);
    free(n);
    n = next;
  }
}

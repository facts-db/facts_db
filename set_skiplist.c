
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "set_skiplist.h"

s_set_skiplist_set_item *
new_set_skiplist_set_item (s_set *set, long index)
{
  s_set_skiplist_set_item *i = malloc(sizeof(s_set_skiplist_set_item));
  if (i) {
    i->type = SET_SKIPLIST_SET_ITEM;
    i->set = set;
    i->index = index;
  }
  return i;
}

s_set_skiplist_ptr_item *
new_set_skiplist_ptr_item (void *data, long len)
{
  s_set_skiplist_ptr_item *i = malloc(sizeof(s_set_skiplist_ptr_item));
  if (i) {
    i->type = SET_SKIPLIST_PTR_ITEM;
    i->data = data;
    i->len = len;
  }
  return i;
}

int set_skiplist_compare (void *a, void *b)
{
  u_set_skiplist_item *ia;
  u_set_skiplist_item *ib;
  if (a == b)
    return 0;
  if (!a)
    return -1;
  if (!b)
    return 1;
  ia = (u_set_skiplist_item*) a;
  ib = (u_set_skiplist_item*) b;
  if (ia->item.type == SET_SKIPLIST_SET_ITEM) {
    s_set_skiplist_ptr_item ja;
    int cmp;
    ja.type = SET_SKIPLIST_PTR_ITEM;
    ja.data = set_mmap(ia->set_item.set, ia->set_item.index);
    ja.len = ia->set_item.set->index[ia->set_item.index].d.size;
    cmp = set_skiplist_compare(&ja, ib);
    set_munmap(ia->set_item.set, ia->set_item.index);
    return cmp;
  }
  else if (ib->item.type == SET_SKIPLIST_SET_ITEM) {
    int cmp = set_skiplist_compare(ib, ia);
    return -cmp;
  }
  else if (ia->item.type == SET_SKIPLIST_PTR_ITEM &&
           ib->item.type == SET_SKIPLIST_PTR_ITEM) {
    long l = ia->ptr_item.len < ib->ptr_item.len ? ia->ptr_item.len
      : ib->ptr_item.len;
    int cmp = memcmp(ia->ptr_item.data, ib->ptr_item.data, l);
    if (cmp == 0) {
      if (ia->ptr_item.len < ib->ptr_item.len)
        return -1;
      if (ia->ptr_item.len > ib->ptr_item.len)
        return 1;
    }
    return cmp;
  }
  assert(0);
  return -1;
}

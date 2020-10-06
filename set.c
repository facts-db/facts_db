
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "set.h"

int set_open (s_set *s, const char *path)
{
  char *index_path;
  size_t len;
  long index_size;
  long i;
  assert(s);
  assert(path);
  len = strlen(path);
  index_path = alloca(len + 7);
  memcpy(index_path, path, len);
  memcpy(index_path + len, ".index", 7);
  printf("set_open\n path: %s\n index path: %s\n", path, index_path);
  s->data_fp = fopen(path, "a+");
  s->index_fp = fopen(index_path, "a+");
  index_size = ftell(s->index_fp);
  assert(index_size % sizeof(s_set_index_entry) == 0);
  s->size = index_size / sizeof(s_set_index_entry);
  s->max = s->size + 1024;
  s->index = calloc(s->max, sizeof(s_set_index_entry));
  fseek(s->index_fp, SEEK_SET, 0);
  for (i = 0; i < s->size; i++)
    fread(&s->index[i].d, sizeof(s_set_index_entry), 1, s->index_fp);
  if (!s->index) {
    fclose(s->data_fp);
    s->data_fp = NULL;
    fclose(s->index_fp);
    s->index_fp = NULL;
    return -1;
  }
  return 0;
}

int set_resize_index (s_set *s)
{
  assert(s);
  unsigned long max = s->size + 1024;
  s_set_index_entry *index;
  index = realloc(s->index, max * sizeof(s_set_index_entry));
  if (!index)
    return -1;
  s->index = index;
  s->max = max;
  return 0;
}

void * set_mmap (s_set *s, long index)
{
  s_set_index_entry *entry;
  assert(s);
  assert(0 <= index);
  assert(index < s->size);
  entry = &s->index[index];
  if (!entry->mmap_count) {
    if ((entry->data = mmap(NULL, entry->d.size,
                            PROT_READ, MAP_FILE,
                            fileno(s->data_fp),
                            0))
        != MAP_FAILED)
      entry->mmap_count++;
  }
  else
    entry->mmap_count++;
  return entry->data;
}

void set_munmap (s_set *s, long index)
{
  s_set_index_entry *entry;
  assert(s);
  assert(0 <= index);
  assert(index < s->size);
  entry = &s->index[index];
  if (entry->mmap_count) {
    entry->mmap_count--;
    if (!entry->mmap_count)
      munmap(entry->data, entry->d.size);
  }
}

long set_find (s_set *s, void *data, long len)
{
  long i;
  assert(s);
  assert(data);
  assert(len > 0);
  for (i = 0; i < s->size; i++)
    if (set_compare_data(s, i, data, len) == 0)
      return i;
  return -1;
}

long set_append_append (s_set *s, void *data, long len)
{
  s_set_index_entry *entry;
  long i = s->size;
  if (s->size == s->max) {
    set_resize_index(s);
    if (s->size == s->max)
      return -1;
  }
  entry = &s->index[i];
  fseek(s->data_fp, SEEK_END, 0);
  entry->d.offset = ftell(s->data_fp);
  entry->d.size = len;
  entry->mmap_count = 0;
  entry->data = 0;
  fwrite(data, len, 1, s->data_fp);
  fseek(s->index_fp, SEEK_END, 0);
  fwrite(&entry->d, sizeof(s_set_index_entry_on_disk), 1, s->index_fp);
  s->size++;
  return i;
}

long set_append (s_set *s, void *data, long len)
{
  long i;
  assert(s);
  assert(data);
  assert(len > 0);
  i = set_find(s, data, len);
  if (i >= 0)
    return i;
  return set_append_append(s, data, len);
}

int set_compare_data (s_set *s, long index, void *data, long len)
{
  s_set_index_entry *entry;
  void *entry_data;
  int cmp;
  long l;
  assert(s);
  assert(index > 0);
  entry = &s->index[index];
  l = entry->d.size < len ? entry->d.size : len;
  entry_data = set_mmap(s, index);
  cmp = memcmp(entry_data, data, l);
  set_munmap(s, index);
  if (cmp == 0) {
    if (entry->d.size < len)
      return -1;
    if (entry->d.size > len)
      return 1;
  }
  return cmp;
}

int set_compare_keys (s_set *s, long a, long b)
{
  s_set_index_entry *ea;
  s_set_index_entry *eb;
  void *da;
  void *db;
  int cmp;
  long l;
  assert(s);
  assert(a >= 0);
  assert(a < s->size);
  assert(b >= 0);
  assert(b < s->size);
  if (a == b)
    return 0;
  ea = &s->index[a];
  eb = &s->index[b];
  l = ea->d.size < eb->d.size ? ea->d.size : eb->d.size;
  da = set_mmap(s, a);
  db = set_mmap(s, b);
  cmp = memcmp(da, db, l);
  set_munmap(s, a);
  set_munmap(s, b);
  if (cmp == 0) {
    if (ea->d.size < eb->d.size)
      return -1;
    if (ea->d.size > eb->d.size)
      return 1;
  }
  return cmp;
}

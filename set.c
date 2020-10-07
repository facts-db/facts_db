
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "dbg_printf.h"
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
  dbg_printf("set_open: path: \"%s\" index path: \"%s\"\n",
             path, index_path);
  if (!(s->data_fp = fopen(path, "a+")))
    return -1;
  if (!(s->index_fp = fopen(index_path, "a+"))) {
    fclose(s->data_fp);
    s->data_fp = 0;
    return -1;
  }
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

void set_close (s_set *s)
{
  dbg_printf("set_close %p\n", (void*) s);
  fclose(s->data_fp);
  s->data_fp = NULL;
  fclose(s->index_fp);
  s->index_fp = NULL;
}

int set_resize_index (s_set *s)
{
  unsigned long max;
  s_set_index_entry *index;
  dbg_printf("set_resize_index %p\n", (void*) s);
  assert(s);
  max = s->size + 1024;
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
  dbg_printf("set_mmap %p %ld\n", (void*) s, index);
  entry = &s->index[index];
  dbg_printf(" entry->mmap_count: %d\n", entry->mmap_count);
  if (!entry->mmap_count) {
    if ((entry->data = mmap(NULL, entry->d.size,
                            PROT_READ, MAP_PRIVATE | MAP_FILE,
                            fileno(s->data_fp),
                            entry->d.offset))
        == MAP_FAILED) {
      dbg_printf("mmap failed");
      return 0;
    }
    dbg_printf(" mmap entry->data: %p\n", entry->data);
  }
  entry->mmap_count++;
  return entry->data;
}

void set_munmap (s_set *s, long index)
{
  s_set_index_entry *entry;
  assert(s);
  assert(0 <= index);
  assert(index < s->size);
  dbg_printf("set_munmap %p %ld\n", (void*) s, index);
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
  dbg_printf("set_find %p %p %ld\n", (void*) s, data, len);
  for (i = 0; i < s->size; i++)
    if (set_compare_data(s, i, data, len) == 0)
      return i;
  return -1;
}

long set_next_offset (s_set *s)
{
  s_set_index_entry *last;
  if (s->size == 0)
    return 0;
  assert(s->size > 0);
  last = &s->index[s->size - 1];
  return last->d.offset + last->d.size;
}

long set_append_append (s_set *s, void *data, long len)
{
  s_set_index_entry *entry;
  long i = s->size;
  dbg_printf("set_append_append %p %p %ld\n", (void*) s, data, len);
  if (s->size == s->max) {
    set_resize_index(s);
    if (s->size == s->max)
      return -1;
  }
  entry = &s->index[i];
  entry->d.offset = set_next_offset(s);
  fseek(s->data_fp, SEEK_SET, entry->d.offset);
  entry->d.size = len;
  entry->mmap_count = 0;
  entry->data = 0;
  fwrite(data, len, 1, s->data_fp);
  fflush(s->data_fp);
  fseek(s->index_fp, SEEK_SET, i * sizeof(s_set_index_entry_on_disk));
  fwrite(&entry->d, sizeof(s_set_index_entry_on_disk), 1, s->index_fp);
  fflush(s->index_fp);
  s->size++;
  return i;
}

long set_append (s_set *s, void *data, long len)
{
  long i;
  assert(s);
  assert(data);
  assert(len > 0);
  dbg_printf("set_append %p %p %ld\n", (void*) s, data, len);
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
  assert(index >= 0);
  dbg_printf("set_compare_data %p %ld %p %ld\n", (void*) s, index, data, len);
  entry = &s->index[index];
  l = entry->d.size < len ? entry->d.size : len;
  entry_data = set_mmap(s, index);
  dbg_printf("entry_data: %p, data: %p, l: %ld\n", entry_data, data, l);
  dbg_printf("entry_data: %c %c %c %c %c\n", ((char*)entry_data)[0],
         ((char*)entry_data)[1], ((char*)entry_data)[2],
         ((char*)entry_data)[3], ((char*)entry_data)[4]);
  dbg_printf("data: %c %c %c %c %c\n", ((char*)data)[0],
         ((char*)data)[1], ((char*)data)[2],
         ((char*)data)[3], ((char*)data)[4]);
  cmp = memcmp(entry_data, data, l);
  dbg_printf("cmp: %d\n", cmp);
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
  dbg_printf("set_compare_keys %p %ld %ld\n", (void*) s, a, b);
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

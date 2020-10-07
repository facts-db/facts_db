#ifndef SET_H
#define SET_H

#include <stdio.h>

typedef struct set_index_entry_on_disk {
  long offset;
  long size;
} s_set_index_entry_on_disk;

typedef struct set_index_entry {
  s_set_index_entry_on_disk d;
  int mmap_count;
  void *data;
} s_set_index_entry;

typedef struct set {
  FILE *data_fp;
  FILE *index_fp;
  s_set_index_entry *index;
  long max;
  long size;
} s_set;

int    set_open (s_set *s,
                 const char *path);

void   set_close (s_set *s);

int    set_resize_index (s_set *s);

void * set_mmap (s_set *s, long index);

void   set_munmap (s_set *s, long index);

long   set_find (s_set *s,
                 void *data,
                 long len);

long   set_append (s_set *s,
                   void *data,
                   long len);

int    set_compare_data (s_set *s, long index, void *data, long len);

int    set_compare_keys (s_set *s, long i, long j);

#endif /* SET_H */

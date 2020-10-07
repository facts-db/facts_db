#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "skiplist.h"

typedef struct set s_set;

typedef struct set_skiplist_item {
  int type;
} s_set_skiplist_item;

typedef struct set_skiplist_set_item {
  int type;
  s_set *set;
  long index;
} s_set_skiplist_set_item;

typedef struct set_skiplist_ptr_item {
  int type;
  void *data;
  long len;
} s_set_skiplist_ptr_item;

typedef enum {
  SET_SKIPLIST_SET_ITEM,
  SET_SKIPLIST_PTR_ITEM
} e_set_skiplist_item_type;

typedef union {
  s_set_skiplist_item         item;
  s_set_skiplist_set_item set_item;
  s_set_skiplist_ptr_item ptr_item;
} u_set_skiplist_item;

s_set_skiplist_set_item *
new_set_skiplist_set_item (s_set *set, long index);

s_set_skiplist_ptr_item *
new_set_skiplist_ptr_item (void *data, long len);

int set_skiplist_compare (void *a, void *b);


typedef struct set_index_entry_on_disk {
  long offset;
  long size;
} s_set_index_entry_on_disk;

typedef struct set_index_entry {
  s_set_index_entry_on_disk d;
  int mmap_count;
  void *data;
} s_set_index_entry;

struct set {
  FILE *data_fp;
  FILE *index_fp;
  s_set_index_entry *index;
  long max;
  long size;
  s_skiplist sl;
};

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

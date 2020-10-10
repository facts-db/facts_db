#ifndef SET_H
#define SET_H

#include <stdio.h>
#include "skiplist.h"

typedef struct item {
  void *data;
  uint64_t len;
} s_item;

s_item * new_item (void *data,
                   long len);

int          item_compare (void *a,
                           void *b);

typedef struct set {
  long size;
  s_skiplist skiplist;
} s_set;

void     set_init (s_set *s);

void     set_clear (s_set *s);

int      set_read (s_set *s,
                 const char *path);

int      set_write (s_set *s,
                  const char *path);

s_item * set_find (s_set *s,
                   void *data,
                   long len);

s_item * set_insert (s_set *s,
                     void *data,
                     long len);

typedef int (*f_item) (s_item *i);

void     set_each (s_set *s,
                   f_item fn);

typedef int (*f_item_index) (s_item *i,
                             unsigned long index);

void     set_each_index (s_set *s,
                         f_item_index fn);

#endif /* SET_H */

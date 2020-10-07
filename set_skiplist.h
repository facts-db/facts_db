#ifndef SET_SKIPLIST_H
#define SET_SKIPLIST_H

#include "set.h"

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

#endif /* SET_SKIPLIST_H */

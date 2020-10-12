#ifndef ITEM_H
#define ITEM_H

typedef struct item {
  void *data;
  uint64_t len;
} s_item;

s_item * new_item (void *data,
                   long len);

int          item_compare (void *a,
                           void *b);

#endif

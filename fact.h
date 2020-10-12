#ifndef FACT_H
#define FACT_H

#include "item.h"

typedef struct fact {
  s_item *s;
  s_item *p;
  s_item *o;
} s_fact;

typedef int (*f_fact) (s_fact *f);

s_fact * new_fact (s_item *s, s_item *p, s_item *o);
int          fact_compare_spo (void *a, void *b);
int          fact_compare_pos (void *a, void *b);
int          fact_compare_osp (void *a, void *b);

#endif

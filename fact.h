#ifndef FACT_H
#define FACT_H

#include "item.h"

typedef struct fact {
  s_item *s;
  s_item *p;
  s_item *o;
} s_fact;

s_fact * new_fact (s_item *s, s_item *p, s_item *o);
int          fact_compare_spo (s_fact *a, s_fact *b);
int          fact_compare_pos (s_fact *a, s_fact *b);
int          fact_compare_osp (s_fact *a, s_fact *b);

#endif

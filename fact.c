
#include <stdlib.h>
#include "fact.h"

s_fact * new_fact (s_item *s, s_item *p, s_item *o)
{
  s_fact *fact = malloc(sizeof(s_fact));
  if (fact) {
    fact->s = s;
    fact->p = p;
    fact->o = o;
  }
  return fact;
}

int fact_compare_spo (void *a, void *b)
{
  int cmp;
  s_fact *fa;
  s_fact *fb;
  if (a == b)
    return 0;
  if (!a)
    return -1;
  if (!b)
    return 1;
  fa = (s_fact*) a;
  fb = (s_fact*) b;
  cmp = item_compare(fa->s, fb->s);
  if (!cmp)
    cmp = item_compare(fa->p, fb->p);
  if (!cmp)
    cmp = item_compare(fa->o, fb->o);
  return cmp;
}

int fact_compare_pos (void *a, void *b)
{
  int cmp;
  s_fact *fa;
  s_fact *fb;
  if (a == b)
    return 0;
  if (!a)
    return -1;
  if (!b)
    return 1;
  fa = (s_fact*) a;
  fb = (s_fact*) b;
  cmp = item_compare(fa->p, fb->p);
  if (!cmp)
    cmp = item_compare(fa->o, fb->o);
  if (!cmp)
    cmp = item_compare(fa->s, fb->s);
  return cmp;
}

int fact_compare_osp (void *a, void *b)
{
  int cmp;
  s_fact *fa;
  s_fact *fb;
  if (a == b)
    return 0;
  if (!a)
    return -1;
  if (!b)
    return 1;
  fa = (s_fact*) a;
  fb = (s_fact*) b;
  cmp = item_compare(fa->o, fb->o);
  if (!cmp)
    cmp = item_compare(fa->s, fb->s);
  if (!cmp)
    cmp = item_compare(fa->p, fb->p);
  return cmp;
}

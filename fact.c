/*
 *  facts_db - in-memory graph database
 *  Copyright 2020 Thomas de Grivel <thoxdg@gmail.com>
 *
 *  Permission to use, copy, modify, and distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>
#include "fact.h"

void fact_init (s_fact *f, const char *s, const char *p, const char *o)
{
  f->s = s;
  f->p = p;
  f->o = o;
}

s_fact * new_fact (const char *s, const char *p, const char *o)
{
  s_fact *fact = malloc(sizeof(s_fact));
  if (fact) {
    fact->s = s;
    fact->p = p;
    fact->o = o;
  }
  return fact;
}

void delete_fact (s_fact *f)
{
  free(f);
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
  if (fa->s == fb->s)
    cmp = 0;
  else if (!fa->s)
    cmp = -1;
  else if (!fb->s)
    cmp = 1;
  else
    cmp = strcmp(fa->s, fb->s);
  if (!cmp) {
    if (fa->p == fb->p)
      cmp = 0;
    else if (!fa->p)
      cmp = -1;
    else if (!fb->p)
      cmp = 1;
    else
      cmp = strcmp(fa->p, fb->p);
    if (!cmp) {
      if (fa->o == fb->o)
        cmp = 0;
      else if (!fa->o)
        cmp = -1;
      else if (!fb->o)
        cmp = 1;
      else
        cmp = strcmp(fa->o, fb->o);
    }
  }
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
  if (fa->p == fb->p)
    cmp = 0;
  else if (!fa->p)
    cmp = -1;
  else if (!fb->p)
    cmp = 1;
  else
    cmp = strcmp(fa->p, fb->p);
  if (!cmp) {
    if (fa->o == fb->o)
      cmp = 0;
    else if (!fa->o)
      cmp = -1;
    else if (!fb->o)
      cmp = 1;
    else
      cmp = strcmp(fa->o, fb->o);
    if (!cmp) {
      if (fa->s == fb->s)
        cmp = 0;
      else if (!fa->s)
        cmp = -1;
      else if (!fb->s)
        cmp = 1;
      else
        cmp = strcmp(fa->s, fb->s);
    }
  }
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
  if (fa->o == fb->o)
    cmp = 0;
  else if (!fa->o)
    cmp = -1;
  else if (!fb->o)
    cmp = 1;
  else
    cmp = strcmp(fa->o, fb->o);
  if (!cmp) {
    if (fa->s == fb->s)
      cmp = 0;
    else if (!fa->s)
      cmp = -1;
    else if (!fb->s)
      cmp = 1;
    else
      cmp = strcmp(fa->s, fb->s);
    if (!cmp) {
      if (fa->p == fb->p)
        cmp = 0;
      else if (!fa->p)
        cmp = -1;
      else if (!fb->p)
        cmp = 1;
      else
        cmp = strcmp(fa->p, fb->p);
    }
  }
  return cmp;
}

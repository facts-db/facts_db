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
#ifndef FACT_H
#define FACT_H

#define P_FIRST ((void*) 0)
#define P_LAST  ((void*) -1)

typedef struct fact {
  const char *s;
  const char *p;
  const char *o;
} s_fact;

typedef int (*f_fact) (s_fact *f);

void         fact_init (s_fact *f, const char *s, const char *p, const char *o);
s_fact * new_fact (const char *s, const char *p, const char *o);
void  delete_fact (s_fact *f);
int          fact_compare_spo (void *a, void *b);
int          fact_compare_pos (void *a, void *b);
int          fact_compare_osp (void *a, void *b);

#endif

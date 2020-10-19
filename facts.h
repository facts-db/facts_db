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
#ifndef FACTS_H
#define FACTS_H

#include "fact.h"
#include "skiplist.h"
#include "spec.h"

typedef struct facts
{
        s_skiplist *index_spo;
        s_skiplist *index_pos;
        s_skiplist *index_osp;
} s_facts;

void              facts_init (s_facts *facts);

void              facts_destroy (s_facts *facts);

s_facts *     new_facts ();

void       delete_facts (s_facts *facts);

s_fact *          facts_add_fact (s_facts *facts,
                                  s_fact *f);

s_fact *          facts_add_spo (s_facts *facts,
                                 const char *s,
                                 const char *p,
                                 const char *o);

int               facts_remove_fact (s_facts *facts,
                                     s_fact *f);

int               facts_remove_spo (s_facts *facts,
                                    const char *s,
                                    const char *p,
                                    const char *o);

s_fact *          facts_get_fact (s_facts *facts,
                                  s_fact *f);

s_fact *          facts_get_fact_pred (s_facts *facts,
                                       s_fact *f,
                                       s_skiplist_node *pred);

unsigned long     facts_count (s_facts *facts);

typedef struct facts_iterator {
        s_skiplist_node *node;
        s_fact *start;
        s_fact *end;
} s_facts_iterator;

void              facts_iterator (s_facts *facts,
                                  s_facts_iterator *iter,
                                  s_skiplist *tree,
                                  s_fact *start,
                                  s_fact *end);

s_fact *          facts_iterator_next (s_facts_iterator *iter);

void              facts_with_3 (s_facts *facts,
                                s_facts_iterator *iter,
                                const char *s,
                                const char *p,
                                const char *o);

void              facts_with_0 (s_facts *facts,
                                s_facts_iterator *iter);

void              facts_with (s_facts *facts,
                              s_facts_iterator *iter,
                              p_spec spec);

#endif

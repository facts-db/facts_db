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

#include <assert.h>
#include <stdlib.h>
#include "facts.h"

void facts_init (s_facts *facts)
{
  assert(facts);
  skiplist_init(&facts->index_spo, 20, 2.0);
  facts->index_spo.compare = fact_compare_spo;
  skiplist_init(&facts->index_pos, 20, 2.0);
  facts->index_pos.compare = fact_compare_pos;
  skiplist_init(&facts->index_osp, 20, 2.0);
  facts->index_osp.compare = fact_compare_osp;
}

s_facts * new_facts ()
{
  s_facts *facts = malloc(sizeof(s_facts));
  if (facts)
    facts_init(facts);
  return facts;
}

s_fact * facts_add_fact (s_facts *facts, s_fact *f)
{
  s_fact *found;
  assert(facts);
  assert(f);
  if ((found = facts_get_fact(facts, f)))
    return found;
  skiplist_insert(&facts->index_spo, f);
  skiplist_insert(&facts->index_pos, f);
  skiplist_insert(&facts->index_osp, f);
  return f;
}

s_fact * facts_remove_fact (s_facts *facts, s_fact *f)
{
  assert(facts);
  assert(f);
  if (skiplist_remove(&facts->index_spo, f) == f) {
    skiplist_remove(&facts->index_pos, f);
    skiplist_remove(&facts->index_osp, f);
    return f;
  }
  return NULL;
}

s_fact * facts_get_fact (s_facts *facts, s_fact *f)
{
  s_skiplist_node *node;
  assert(facts);
  assert(f);
  node = skiplist_find(&facts->index_spo, f);
  if (node)
    return (s_fact*) node->value;
  return NULL;
}

unsigned long facts_count (s_facts *facts)
{
  assert(facts);
  return facts->index_spo.length;
}

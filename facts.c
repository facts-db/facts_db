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
        facts->index_spo = new_skiplist(20, 2.0);
        assert(facts->index_spo);
        facts->index_spo->compare = fact_compare_spo;
        facts->index_pos = new_skiplist(20, 2.0);
        assert(facts->index_pos);
        facts->index_pos->compare = fact_compare_pos;
        facts->index_osp = new_skiplist(20, 2.0);
        assert(facts->index_osp);
        facts->index_osp->compare = fact_compare_osp;
}

void facts_destroy (s_facts *facts)
{
        delete_skiplist(facts->index_spo);
        delete_skiplist(facts->index_pos);
        delete_skiplist(facts->index_osp);
}

s_facts * new_facts ()
{
        s_facts *facts = malloc(sizeof(s_facts));
        if (facts)
                facts_init(facts);
        return facts;
}

void delete_facts (s_facts *facts)
{
        facts_destroy(facts);
        free(facts);
}

s_fact * facts_add_fact (s_facts *facts, s_fact *f)
{
        s_fact *found;
        assert(facts);
        assert(f);
        if ((found = facts_get_fact(facts, f)))
                return found;
        skiplist_insert(facts->index_spo, f);
        skiplist_insert(facts->index_pos, f);
        skiplist_insert(facts->index_osp, f);
        return f;
}

s_fact * facts_remove_fact (s_facts *facts, s_fact *f)
{
        assert(facts);
        assert(f);
        if ((f = skiplist_remove(facts->index_spo, f))) {
                skiplist_remove(facts->index_pos, f);
                skiplist_remove(facts->index_osp, f);
                return f;
        }
        return NULL;
}

s_fact * facts_get_fact (s_facts *facts, s_fact *f)
{
        s_skiplist_node *node;
        assert(facts);
        assert(f);
        node = skiplist_find(facts->index_spo, f);
        if (node)
                return (s_fact*) node->value;
        return NULL;
}

unsigned long facts_count (s_facts *facts)
{
        assert(facts);
        return facts->index_spo->length;
}

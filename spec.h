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
#ifndef SPEC_H
#define SPEC_H

#include <stdio.h>
#include "binding.h"
#include "fact.h"

typedef const char **p_spec;

/* facts specification
   ===================

   A spec has the following pattern :
    (subject (predicate object)+ NULL)+ NULL
   For instance one fact {s1, p1.1, o1.1} has the spec :
     s1 p1.1 o1.1 NULL NULL
   And four facts of two subjects, each having two properties yield this
   spec :
     s1 p1.1 o1.1 p1.2 o1.2 NULL s2 p2.1 o2.1 p2.2 o2.2 NULL NULL
*/

/* calls malloc */
p_spec spec_clone (p_spec spec);

size_t spec_count_bindings (p_spec spec);

size_t spec_count_facts (p_spec spec);

/* calls malloc to return a new p_spec */
p_spec spec_expand (p_spec spec);

void   spec_print (p_spec spec,
                   FILE *fp);

p_spec spec_sort (p_spec spec);

typedef struct spec_cursor {
        p_spec spec;
        const char *s;
        unsigned long pos;
} s_spec_cursor;

void spec_cursor_init (s_spec_cursor *c,
                       p_spec spec);

int  spec_cursor_next (s_spec_cursor *c,
                       s_fact *f);

s_binding * spec_bindings (p_spec spec);

#endif

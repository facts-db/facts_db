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
#include <stdio.h>
#include <stdlib.h>
#include "spec.h"

/* FIXME: duplicate bindings */
size_t spec_count_bindings (p_spec spec)
{
        size_t count = 0;
        size_t i = 0;
        while (spec[i] || spec[i + 1]) {
                if (spec[i] && spec[i][0] == '?')
                        count++;
                i++;
        }
        return count;
}

size_t spec_count_facts (p_spec spec)
{
        s_spec_cursor c;
        size_t count = 0;
        s_fact f;
        spec_cursor_init(&c, spec);
        while (spec_cursor_next(&c, &f))
                count++;
        return count;
}

/* calls malloc to return a new p_spec */
p_spec spec_expand (p_spec spec)
{
        size_t count;
        assert(spec);
        fprintf(stderr, "spec_expand\n");
        count = spec_count_facts(spec);
        if (count > 0) {
                s_spec_cursor c;
                s_fact f;
                p_spec new = calloc(count * 4 + 1,
                                    sizeof(const char *));
                p_spec n = new;
                spec_cursor_init(&c, spec);
                while (spec_cursor_next(&c, &f)) {
                        *n++ = f.s;
                        *n++ = f.p;
                        *n++ = f.o;
                        *n++ = NULL;
                }
                *n = NULL;
                return new;
        }
        return NULL;
}

int fact_compare_bindings (s_fact *a, s_fact *b)
{
        int ba = 0;
        int bb = 0;
        assert(a);
        assert(b);
        if (a->s[0] == '?')
                ba++;
        if (a->p[0] == '?')
                ba++;
        if (a->o[0] == '?')
                ba++;
        if (b->s[0] == '?')
                bb++;
        if (b->p[0] == '?')
                bb++;
        if (b->o[0] == '?')
                bb++;
        if (ba < bb)
                return -1;
        if (ba > bb)
                return 1;
        return 0;
}

/* this only works on expanded specs : (s, p, o, NULL)*, NULL. */
p_spec spec_sort (p_spec spec)
{
        size_t count;
        size_t i;
        assert(spec);
        fprintf(stderr, "spec_sort\n");
        count = spec_count_facts(spec);
        if (count)
                for (i = 0; i < count - 1; i++) {
                        size_t j;
                        for (j = 0; j < count - i - 1; j++) {
                                s_fact *a = (s_fact*) (spec + j * 4);
                                s_fact *b = (s_fact*) (spec + (j + 1) * 4);
                                if (fact_compare_bindings(a, b) > 0) {
                                        s_fact swap = *a;
                                        *a = *b;
                                        *b = swap;
                                }
                        }
                }
        fprintf(stderr, "spec_sort end\n");
        return spec;
}

void spec_cursor_init (s_spec_cursor *c, p_spec spec)
{
        assert(c);
        assert(spec);
        c->spec = spec;
        c->s = spec[0];
        c->pos = 1;
}

int spec_cursor_next (s_spec_cursor *c, s_fact *f)
{
        const char *p;
        const char *o;
        assert(c);
        assert(f);
        if (!c->s)
                return 0;
        p = c->spec[c->pos];
        if (p) {
                o = c->spec[c->pos + 1];
                if (!o) {
                        fprintf(stderr, "spec_cursor_next: NULL object\n");
                        return 0;
                }
                c->pos += 2;
                f->s = c->s;
                f->p = p;
                f->o = o;
                return 1;
        }
        c->s = c->spec[c->pos + 1];
        c->pos += 2;
        return spec_cursor_next(c, f);
}

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
#include <string.h>
#include "binding.h"

const char ** bindings_get (s_binding *bindings, const char *name)
{
        if (bindings)
                while (bindings->name) {
                        if (strcmp(bindings->name, name) == 0)
                                return bindings->value;
                        bindings++;
                }
        return NULL;
}

const char ** bindings_get_or_die (s_binding *bindings,
                                   const char *name)
{
        const char **b = bindings_get(bindings, name);
        if (!b) {
                fprintf(stderr, "bindings_get: unknown binding: %s\n",
                        name);
                exit(1);
        }
        return b;
}

/* set all bindings values to NULL */

void bindings_nullify (s_binding *bindings)
{
        if (bindings)
                while (bindings->name) {
                        *bindings->value = NULL;
                        bindings++;
                }
}

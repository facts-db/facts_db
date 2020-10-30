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
#ifndef RW_H
#define RW_H

#include <stdio.h>
#include "fact.h"
#include "facts.h"
#include "spec.h"

int read_string_quoted (char *buf,
                        size_t len,
                        FILE *fp);

int write_string_quoted (const char *string,
                         FILE *fp);

int read_string (char *buf,
                 size_t len,
                 FILE *fp);

int write_string (const char *string,
                  FILE *fp);

int read_fact (s_facts *facts,
               s_fact *f,
               FILE *fp);

int write_fact (const s_fact *f,
                FILE *fp);

int read_facts (s_facts *facts,
                FILE *fp);

int write_facts (s_facts *facts,
                 FILE *fp);

int read_facts_log (s_facts *facts,
                    FILE *fp);

int write_fact_log (const char *operation,
                    s_fact *f,
                    FILE *fp);

int write_spec (p_spec spec,
                FILE *fp);

#endif

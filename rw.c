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
#include "rw.h"

int write_string_quoted (const char *string, FILE *fp)
{
        size_t i;
        if (fwrite("\"", 1, 1, fp) != 1)
                return -1;
        for (i = 0; i < strlen(string); i++) {
                switch (string[i]) {
                case '"':
                case '\\':
                        if (fwrite("\\", 1, 1, fp) != 1)
                                return -1;
                default:
                        if (fwrite(string + i, 1, 1, fp) != 1)
                                return -1;
                }
        }
        if (fwrite("\"\n", 2, 1, fp) != 1)
                return -1;
        return 0;
}

int write_string (const char *string, FILE *fp)
{
        if (string[0] == '"' ||
            strchr(string, '\n') ||
            strchr(string, '\\'))
                return write_string_quoted(string, fp);
        if (string[0])
                if (fwrite(string, strlen(string), 1, fp) != 1)
                        return -1;
        if (fwrite("\n", 1, 1, fp) != 1)
                return -1;
        return 0;
}

int read_string_quoted (char *buf, size_t len, FILE *fp)
{
        char c;
        if (fread(&c, 1, 1, fp) != 1)
                return -1;
        while (c != '"') {
                if (len == 1)
                        return -1;
                if (c == '\\')
                        if (fread(&c, 1, 1, fp) != 1)
                                return -1;
                if (!c)
                        return -1;
                *buf = c;
                len--;
                buf++;
                if (fread(&c, 1, 1, fp) != 1)
                        return -1;
        }
        *buf = 0;
        if (fread(&c, 1, 1, fp) != 1)
                return -1;
        if (c != '\n')
                return -1;
        return 0;
}

int read_string (char *buf, size_t len, FILE *fp)
{
        char c;
        assert(buf);
        assert(len > 0);
        if (fread(&c, 1, 1, fp) != 1)
                return -1;
        if (c == '"')
                return read_string_quoted(buf, len, fp);
        while (c != '\n') {
                if (len == 1)
                        return -1;
                if (!c)
                        return -1;
                *buf = c;
                len--;
                buf++;
                if (fread(&c, 1, 1, fp) != 1)
                        return -1;
        }
        *buf = 0;
        return 0;
}

int write_fact (const s_fact *f, FILE *fp)
{
        assert(f);
        assert(fp);
        if (write_string(f->s, fp))
                return -1;
        if (write_string(f->p, fp))
                return -1;
        if (write_string(f->o, fp))
                return -1;
        if (write_string("", fp))
                return -1;
        return 0;
}

int write_facts (s_facts *facts, FILE *fp)
{
        s_facts_cursor c;
        s_fact *f;
        const char *s;
        const char *p;
        const char *o;
        assert(facts);
        facts_with_0(facts, &c, &s, &p, &o);
        while ((f = facts_cursor_next(&c))) {
                if (write_fact(f, fp))
                        return -1;
        }
        fflush(fp);
        return 0;
}

int read_fact (s_facts *facts, s_fact *f, FILE *fp)
{
        char *buf;
        assert(facts);
        assert(f);
        if (!(buf = calloc(FACTS_LOAD_BUFSZ, sizeof(char))))
                return -1;
        if (read_string(buf, FACTS_LOAD_BUFSZ, fp))
                goto error;
        if (!buf[0])
                goto error;
        if (!(f->s = facts_intern(facts, buf)))
                goto error;
        if (read_string(buf, FACTS_LOAD_BUFSZ, fp))
                goto error;
        if (!buf[0])
                goto error;
        if (!(f->p = facts_intern(facts, buf)))
                goto error;
        if (read_string(buf, FACTS_LOAD_BUFSZ, fp))
                goto error;
        if (!buf[0])
                goto error;
        if (!(f->o = facts_intern(facts, buf)))
                goto error;
        if (fread(buf, 1, 1, fp) != 1)
                goto error;
        if (buf[0] != '\n')
                goto error;
        free(buf);
        return 0;
 error:
        free(buf);
        return -1;
}

static int fpeek (FILE *fp)
{
        int c = fgetc(fp);
        if (c >= 0)
                ungetc(c, fp);
        return c;
}

int read_facts (s_facts *facts, FILE *fp)
{
        s_fact f;
        assert(facts);
        while (!feof(fp) && fpeek(fp) != EOF) {
                if (read_fact(facts, &f, fp))
                        return -1;
                if (!facts_add_fact(facts, &f))
                        return -1;
        }
        return 0;
}

int write_fact_log (const char *operation, s_fact *f, FILE *fp)
{
        if (fwrite(operation, strlen(operation), 1, fp) != 1)
                return -1;
        if (fwrite("\n", 1, 1, fp) != 1)
                return -1;
        if (write_fact(f, fp))
                return -1;
        fflush(fp);
        return 0;
}

int read_facts_log (s_facts *facts, FILE *fp)
{
        char operation[32];
        int op = 0;
        s_fact f;
        assert(facts);
        while (!feof(fp) && fpeek(fp) != EOF) {
                if (!fgets(operation, sizeof(operation), fp))
                        return -1;
                if (!strcasecmp(operation, "add\n"))
                        op = 1;
                else if (!strcasecmp(operation, "remove\n"))
                        op = 2;
                else {
                        fprintf(stderr, "facts_load_log:"
                                " unknown operation: %s\n", operation);
                        return -1;
                }
                if (read_fact(facts, &f, fp))
                        return -1;
                if (op == 1) {
                        if (!facts_add_fact(facts, &f))
                                return -1;
                }
                else if (op == 2) {
                        if (!facts_remove_fact(facts, &f))
                                return -1;
                }
        }
        return 0;
}

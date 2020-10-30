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

#include <check.h>
#include <stdlib.h>
#include "facts.h"
#include "rw.h"

s_facts *g_f;

START_TEST (test_facts_init_destroy)
{
        s_facts f;
        facts_init(&f, NULL, 100);
        ck_assert(!facts_count(&f));
        facts_destroy(&f);
}
END_TEST

START_TEST (test_facts_new_delete)
{
        s_facts *f;
        f = new_facts(NULL, 100);
        ck_assert(f);
        ck_assert(!facts_count(f));
        delete_facts(f);
}
END_TEST

void setup_add_fact ()
{
        g_f = new_facts(NULL, 100);
}

void teardown_add_fact ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_add_fact_one)
{
        s_fact a = {"a", "b", "c"};
        s_fact aa = {"a", "b", "c"};
        s_fact *ia;
        ck_assert(facts_count(g_f) == 0);
        ck_assert((ia = facts_add_fact(g_f, &a)));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(ia == facts_add_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(ia == facts_add_fact(g_f, &aa));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_fact_two)
{
        s_fact a  = {"a", "b", "c"};
        s_fact aa = {"a", "b", "c"};
        s_fact b  = {"b", "c", "d"};
        s_fact bb = {"b", "c", "d"};
        s_fact *ia;
        s_fact *ib;
        ck_assert(facts_count(g_f) == 0);
        ck_assert((ia = facts_add_fact(g_f, &a)));
        ck_assert(facts_count(g_f) == 1);
        ck_assert((ib = facts_add_fact(g_f, &b)));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_fact(g_f, &a) == ia);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_fact(g_f, &b) == ib);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_fact(g_f, &aa) == ia);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_fact(g_f, &bb) == ib);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_fact_ten)
{
        s_fact a = {"a", "b", "c"};
        s_fact b = {"b", "c", "d"};
        s_fact c = {"c", "d", "e"};
        s_fact d = {"d", "e", "f"};
        s_fact e = {"e", "f", "g"};
        s_fact f = {"f", "g", "h"};
        s_fact g = {"g", "h", "i"};
        s_fact h = {"h", "i", "j"};
        s_fact i = {"i", "j", "k"};
        s_fact j = {"j", "k", "l"};
        ck_assert(facts_count(g_f) == 0);
        ck_assert(facts_add_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(facts_add_fact(g_f, &b));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_fact(g_f, &c));
        ck_assert(facts_count(g_f) == 3);
        ck_assert(facts_add_fact(g_f, &d));
        ck_assert(facts_count(g_f) == 4);
        ck_assert(facts_add_fact(g_f, &e));
        ck_assert(facts_count(g_f) == 5);
        ck_assert(facts_add_fact(g_f, &f));
        ck_assert(facts_count(g_f) == 6);
        ck_assert(facts_add_fact(g_f, &g));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(facts_add_fact(g_f, &h));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(facts_add_fact(g_f, &i));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_add_fact(g_f, &j));
        ck_assert(facts_count(g_f) == 10);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

void setup_add_spo ()
{
        g_f = new_facts(NULL, 100);
}

void teardown_add_spo ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_add_spo_one)
{
        s_fact *ia;
        ck_assert(facts_count(g_f) == 0);
        ck_assert((ia = facts_add_spo(g_f, "a", "b", "c")));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(ia == facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_spo_two)
{
        s_fact *ia;
        s_fact *ib;
        ck_assert(facts_count(g_f) == 0);
        ck_assert((ia = facts_add_spo(g_f, "a", "b", "c")));
        ck_assert(facts_count(g_f) == 1);
        ck_assert((ib = facts_add_spo(g_f, "b", "c", "d")));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_spo(g_f, "a", "b", "c") == ia);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_spo(g_f, "b", "c", "d") == ib);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_spo_ten)
{
        ck_assert(facts_count(g_f) == 0);
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_add_spo(g_f, "c", "d", "e"));
        ck_assert(facts_count(g_f) == 3);
        ck_assert(facts_add_spo(g_f, "d", "e", "f"));
        ck_assert(facts_count(g_f) == 4);
        ck_assert(facts_add_spo(g_f, "e", "f", "g"));
        ck_assert(facts_count(g_f) == 5);
        ck_assert(facts_add_spo(g_f, "f", "g", "h"));
        ck_assert(facts_count(g_f) == 6);
        ck_assert(facts_add_spo(g_f, "g", "h", "i"));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(facts_add_spo(g_f, "h", "i", "j"));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(facts_add_spo(g_f, "i", "j", "k"));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_add_spo(g_f, "j", "k", "l"));
        ck_assert(facts_count(g_f) == 10);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

void setup_add ()
{
        g_f = new_facts(NULL, 10);
}

void teardown_add ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_add_one)
{
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "a", "b", "c", NULL, NULL}));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "a", "b", "c", NULL, NULL}));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_two)
{
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "a", "b", "c",
                                "d", "e", NULL, NULL}));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "a", "b", "c",
                                "d", "e", NULL, NULL}));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_ten)
{
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "a", "b", "c",
                                "d", "e", NULL,
                                "b", "c", "d",
                                "e", "f",
                                "g", "h", NULL,
                                "i", "j", "k",
                                "l", "m",
                                "n", "o",
                                "p", "q", NULL,
                                "r", "s", "t", NULL, NULL}));
        ck_assert(facts_count(g_f) == 10);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "a", "b", "c",
                                "d", "e", NULL,
                                "b", "c", "d",
                                "e", "f",
                                "g", "h", NULL,
                                "i", "j", "k",
                                "l", "m",
                                "n", "o",
                                "p", "q", NULL,
                                "r", "s", "t", NULL, NULL}));
        ck_assert(facts_count(g_f) == 10);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "a"));
}
END_TEST

START_TEST (test_facts_add_anon)
{
        FILE *fp = fopen("test_facts_add_anon", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "?a", "b", "c",
                                "d", "?e",
                                "?f", "g",
                                "?h", "?i", NULL,
                                "i", "j", "?k",
                                "?l", "m",
                                "?n", "?o", NULL, NULL}));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(!facts_add(g_f, (const char *[]) {
                                "?a", "b", "c",
                                "d", "?e",
                                "?f", "g",
                                "?h", "?i", NULL,
                                "i", "j", "?k",
                                "?l", "m",
                                "?n", "?o", NULL, NULL}));
        ck_assert(facts_count(g_f) == 14);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(facts_find_symbol(g_f, "b"));
        ck_assert(!write_facts(g_f, fp));
}
END_TEST

void setup_remove_fact ()
{
        g_f = new_facts(NULL, 100);
        facts_add_spo(g_f, "a", "b", "c");
        facts_add_spo(g_f, "b", "c", "d");
        facts_add_spo(g_f, "c", "d", "e");
        facts_add_spo(g_f, "d", "e", "f");
        facts_add_spo(g_f, "e", "f", "g");
        facts_add_spo(g_f, "f", "g", "h");
        facts_add_spo(g_f, "g", "h", "i");
        facts_add_spo(g_f, "h", "i", "j");
        facts_add_spo(g_f, "i", "j", "k");
        facts_add_spo(g_f, "j", "k", "l");
}

void teardown_remove_fact ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_remove_fact_one)
{
        s_fact a = {"a", "b", "c"};
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(!facts_remove_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(!facts_find_symbol(g_f, "a"));
        ck_assert(facts_find_symbol(g_f, "j"));
}
END_TEST

START_TEST (test_facts_remove_fact_two)
{
        s_fact a = {"a", "b", "c"};
        s_fact b = {"b", "c", "d"};
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_remove_fact(g_f, &b));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_remove_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_remove_fact(g_f, &b));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(!facts_find_symbol(g_f, "a"));
        ck_assert(!facts_find_symbol(g_f, "b"));
        ck_assert(facts_find_symbol(g_f, "j"));
}
END_TEST

START_TEST (test_facts_remove_fact_ten)
{
        s_fact a = {"a", "b", "c"};
        s_fact b = {"b", "c", "d"};
        s_fact c = {"c", "d", "e"};
        s_fact d = {"d", "e", "f"};
        s_fact e = {"e", "f", "g"};
        s_fact f = {"f", "g", "h"};
        s_fact g = {"g", "h", "i"};
        s_fact h = {"h", "i", "j"};
        s_fact i = {"i", "j", "k"};
        s_fact j = {"j", "k", "l"};
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_fact(g_f, &a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_remove_fact(g_f, &b));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(facts_remove_fact(g_f, &c));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(facts_remove_fact(g_f, &d));
        ck_assert(facts_count(g_f) == 6);
        ck_assert(facts_remove_fact(g_f, &e));
        ck_assert(facts_count(g_f) == 5);
        ck_assert(facts_remove_fact(g_f, &f));
        ck_assert(facts_count(g_f) == 4);
        ck_assert(facts_remove_fact(g_f, &g));
        ck_assert(facts_count(g_f) == 3);
        ck_assert(facts_remove_fact(g_f, &h));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_remove_fact(g_f, &i));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(facts_remove_fact(g_f, &j));
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!facts_find_symbol(g_f, "0"));
        ck_assert(!facts_find_symbol(g_f, "a"));
        ck_assert(!facts_find_symbol(g_f, "b"));
        ck_assert(!facts_find_symbol(g_f, "c"));
        ck_assert(!facts_find_symbol(g_f, "d"));
        ck_assert(!facts_find_symbol(g_f, "e"));
        ck_assert(!facts_find_symbol(g_f, "f"));
        ck_assert(!facts_find_symbol(g_f, "g"));
        ck_assert(!facts_find_symbol(g_f, "h"));
        ck_assert(!facts_find_symbol(g_f, "i"));
        ck_assert(!facts_find_symbol(g_f, "j"));
}
END_TEST

void setup_remove_spo ()
{
        g_f = new_facts(NULL, 100);
        facts_add_spo(g_f, "a", "b", "c");
        facts_add_spo(g_f, "b", "c", "d");
        facts_add_spo(g_f, "c", "d", "e");
        facts_add_spo(g_f, "d", "e", "f");
        facts_add_spo(g_f, "e", "f", "g");
        facts_add_spo(g_f, "f", "g", "h");
        facts_add_spo(g_f, "g", "h", "i");
        facts_add_spo(g_f, "h", "i", "j");
        facts_add_spo(g_f, "i", "j", "k");
        facts_add_spo(g_f, "j", "k", "l");
}

void teardown_remove_spo ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_remove_spo_one)
{
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(!facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 9);
}
END_TEST

START_TEST (test_facts_remove_spo_two)
{
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(facts_count(g_f) == 8);
}
END_TEST

START_TEST (test_facts_remove_spo_ten)
{
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(facts_remove_spo(g_f, "c", "d", "e"));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(facts_remove_spo(g_f, "d", "e", "f"));
        ck_assert(facts_count(g_f) == 6);
        ck_assert(facts_remove_spo(g_f, "e", "f", "g"));
        ck_assert(facts_count(g_f) == 5);
        ck_assert(facts_remove_spo(g_f, "f", "g", "h"));
        ck_assert(facts_count(g_f) == 4);
        ck_assert(facts_remove_spo(g_f, "g", "h", "i"));
        ck_assert(facts_count(g_f) == 3);
        ck_assert(facts_remove_spo(g_f, "h", "i", "j"));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_remove_spo(g_f, "i", "j", "k"));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(facts_remove_spo(g_f, "j", "k", "l"));
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

void setup_with_spo ()
{
        g_f = new_facts(NULL, 100);
        facts_add_spo(g_f, "a", "b", "c");
        facts_add_spo(g_f, "a", "b", "d");
        facts_add_spo(g_f, "a", "e", "d");
        facts_add_spo(g_f, "g", "b", "c");
        facts_add_spo(g_f, "h", "i", "c");
}

void teardown_with_spo ()
{
        delete_facts(g_f);
        g_f = NULL;
}

int fact_equal (s_fact *f, const char *s, const char *p, const char *o)
{
        return (!strcmp(f->s, s) && !strcmp(f->p, p) &&
                !strcmp(f->o, o));
}

START_TEST (test_facts_with_spo_0)
{
        s_fact f;
        const char *s;
        const char *p;
        const char *o;
        s_binding bindings[] = {
                {"?s", &s},
                {"?p", &p},
                {"?o", &o},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "?s", "?p", "?o");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(fact_equal(&f, s, p, o));
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(fact_equal(&f, s, p, o));
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(fact_equal(&f, s, p, o));
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(fact_equal(&f, s, p, o));
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(fact_equal(&f, s, p, o));
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_3)
{
        s_fact f;
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, NULL, &c, "a", "a", "a");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "a", "b", "a");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "a", "b", "c");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "a", "b", "d");
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "a", "b", "e");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "a", "e", "d");
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "a", "e", "g");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "g", "b", "c");
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "h", "i", "c");
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, NULL, &c, "i", "j", "k");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_s)
{
        s_fact f;
        const char *s;
        s_binding bindings[] = {
                {"?s", &s},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "?s", "a", "a");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "b", "a");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "b", "c");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "b", "d");
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "b", "e");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "i", "b");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "i", "c");
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "i", "d");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "j", "k");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_p)
{
        s_fact f;
        const char *p;
        s_binding bindings[] = {
                {"?p", &p},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "a", "?p", "a");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "?p", "b");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "?p", "c");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "?p", "d");
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "?p", "e");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "g", "?p", "c");
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "h", "?p", "b");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "h", "?p", "c");
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "h", "?p", "d");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "i", "?p", "a");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_o)
{
        s_fact f;
        const char *o;
        s_binding bindings[] = {
                {"?o", &o},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "a", "a", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "b", "?o");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "c", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "e", "?o");
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "f", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "b", "c", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "g", "a", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "g", "b", "?o");
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "g", "c", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "h", "a", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "h", "i", "?o");
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "i", "j", "?o");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_sp)
{
        s_fact f;
        const char *s;
        const char *p;
        s_binding bindings[] = {
                {"?s", &s},
                {"?p", &p},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "?s", "?p", "a");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "?p", "c");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!strcmp(f.p, p));
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!strcmp(f.p, p));
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!strcmp(f.p, p));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "?p", "d");
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!strcmp(f.p, p));
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.s, s));
        ck_assert(!strcmp(f.p, p));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "?p", "e");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_po)
{
        s_fact f;
        const char *p;
        const char *o;
        s_binding bindings[] = {
                {"?p", &p},
                {"?o", &o},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "0", "?p", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "a", "?p", "?o");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!strcmp(f.o, o));
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!strcmp(f.o, o));
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "b", "?p", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "g", "?p", "?o");
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "h", "?p", "?o");
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.p, p));
        ck_assert(!strcmp(f.o, o));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "i", "?p", "?o");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

START_TEST (test_facts_with_spo_os)
{
        s_fact f;
        const char *o;
        const char *s;
        s_binding bindings[] = {
                {"?o", &o},
                {"?s", &s},
                {NULL, NULL} };
        s_facts_cursor c;
        ck_assert(facts_count(g_f) == 5);
        facts_with_spo(g_f, bindings, &c, "?s", "a", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "b", "?o");
        fact_init(&f, "a", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!strcmp(f.s, s));
        fact_init(&f, "g", "b", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!strcmp(f.s, s));
        fact_init(&f, "a", "b", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!strcmp(f.s, s));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "c", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "e", "?o");
        fact_init(&f, "a", "e", "d");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!strcmp(f.s, s));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "f", "?o");
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "i", "?o");
        fact_init(&f, "h", "i", "c");
        ck_assert(fact_compare_spo(&f, facts_cursor_next(&c)) == 0);
        ck_assert(!strcmp(f.o, o));
        ck_assert(!strcmp(f.s, s));
        ck_assert(!facts_cursor_next(&c));
        facts_with_spo(g_f, bindings, &c, "?s", "j", "?o");
        ck_assert(!facts_cursor_next(&c));
}
END_TEST

void setup_write ()
{
        g_f = new_facts(NULL, 10);
}

void teardown_write ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_write_facts_empty)
{
        FILE *fp = fopen("test_write_facts_empty", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!write_facts(g_f, fp));
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_empty"
                          " test_facts_empty"));
}
END_TEST

START_TEST (test_write_facts_one)
{
        FILE *fp = fopen("test_write_facts_one", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(!write_facts(g_f, fp));
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_one"
                          " test_facts_one"));
}
END_TEST

START_TEST (test_write_facts_two)
{
        FILE *fp = fopen("test_write_facts_two", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(!write_facts(g_f, fp));
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_two"
                          " test_facts_two"));
}
END_TEST

START_TEST (test_write_facts_ten)
{
        FILE *fp = fopen("test_write_facts_ten", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(facts_add_spo(g_f, "c", "d", "e"));
        ck_assert(facts_add_spo(g_f, "d", "e", "f"));
        ck_assert(facts_add_spo(g_f, "e", "f", "g"));
        ck_assert(facts_add_spo(g_f, "f", "g", "h"));
        ck_assert(facts_add_spo(g_f, "g", "h", "i"));
        ck_assert(facts_add_spo(g_f, "h", "i", "j"));
        ck_assert(facts_add_spo(g_f, "i", "j", "k"));
        ck_assert(facts_add_spo(g_f, "j", "k", "l"));
        ck_assert(!write_facts(g_f, fp));
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_ten"
                          " test_facts_ten"));
}
END_TEST

START_TEST (test_write_facts_escapes)
{
        FILE *fp = fopen("test_write_facts_escapes", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(facts_add_spo(g_f, "\\", "\"", "\n"));
        ck_assert(facts_add_spo(g_f, "a\\", "a\\a", "a\\\\a"));
        ck_assert(facts_add_spo(g_f, "a\"", "a\"a", "a\"\"a"));
        ck_assert(facts_add_spo(g_f, "a\n", "a\na", "a\n\na"));
        ck_assert(facts_add_spo(g_f, "\\\"\n", "\\\"\n\\\"\n",
                                "\\\"\n\\\"\n\\\"\n"));
        ck_assert(facts_add_spo(g_f, "\\a", "\\b", "\\c"));
        ck_assert(facts_add_spo(g_f, "a\\a", "a\\aa", "a\\a\\aa"));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(!write_facts(g_f, fp));
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_escapes"
                          " test_facts_escapes"));
}
END_TEST

void setup_read ()
{
        g_f = new_facts(NULL, 10);
}

void teardown_read ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_read_facts_empty)
{
        FILE *fp = fopen("test_facts_empty", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

START_TEST (test_read_facts_one)
{
        FILE *fp = fopen("test_facts_one", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 1);
        ck_assert(facts_get_spo(g_f, "a", "b", "c"));
}
END_TEST

START_TEST (test_read_facts_two)
{
        FILE *fp = fopen("test_facts_two", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_get_spo(g_f, "a", "b", "c"));
        ck_assert(facts_get_spo(g_f, "b", "c", "d"));
}
END_TEST

START_TEST (test_read_facts_ten)
{
        FILE *fp = fopen("test_facts_ten", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_get_spo(g_f, "a", "b", "c"));
        ck_assert(facts_get_spo(g_f, "b", "c", "d"));
        ck_assert(facts_get_spo(g_f, "c", "d", "e"));
        ck_assert(facts_get_spo(g_f, "d", "e", "f"));
        ck_assert(facts_get_spo(g_f, "e", "f", "g"));
        ck_assert(facts_get_spo(g_f, "f", "g", "h"));
        ck_assert(facts_get_spo(g_f, "g", "h", "i"));
        ck_assert(facts_get_spo(g_f, "h", "i", "j"));
        ck_assert(facts_get_spo(g_f, "i", "j", "k"));
        ck_assert(facts_get_spo(g_f, "j", "k", "l"));
}
END_TEST

START_TEST (test_read_facts_escapes)
{
        FILE *fp = fopen("test_facts_escapes", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 7);
        ck_assert(facts_get_spo(g_f, "\\", "\"", "\n"));
        ck_assert(facts_get_spo(g_f, "a\\", "a\\a", "a\\\\a"));
        ck_assert(facts_get_spo(g_f, "a\"", "a\"a", "a\"\"a"));
        ck_assert(facts_get_spo(g_f, "a\n", "a\na", "a\n\na"));
        ck_assert(facts_get_spo(g_f, "\\\"\n", "\\\"\n\\\"\n",
                                "\\\"\n\\\"\n\\\"\n"));
        ck_assert(facts_get_spo(g_f, "\\a", "\\b", "\\c"));
        ck_assert(facts_get_spo(g_f, "a\\a", "a\\aa", "a\\a\\aa"));
}
END_TEST

void setup_write_facts_log ()
{
        g_f = new_facts(NULL, 10);
}

void teardown_write_facts_log ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_write_facts_log_one)
{
        FILE *fp = fopen("test_write_facts_log_one", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        g_f->log = fp;
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(!facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_count(g_f) == 0);
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_log_one"
                          " test_facts_log_one"));
}
END_TEST

START_TEST (test_write_facts_log_two)
{
        FILE *fp = fopen("test_write_facts_log_two", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        g_f->log = fp;
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(!facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(!facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(facts_count(g_f) == 0);
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_log_two"
                          " test_facts_log_two"));
}
END_TEST

START_TEST (test_write_facts_log_ten)
{
        FILE *fp = fopen("test_write_facts_log_ten", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        g_f->log = fp;
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(facts_add_spo(g_f, "c", "d", "e"));
        ck_assert(facts_add_spo(g_f, "d", "e", "f"));
        ck_assert(facts_add_spo(g_f, "e", "f", "g"));
        ck_assert(facts_add_spo(g_f, "f", "g", "h"));
        ck_assert(facts_add_spo(g_f, "g", "h", "i"));
        ck_assert(facts_add_spo(g_f, "h", "i", "j"));
        ck_assert(facts_add_spo(g_f, "i", "j", "k"));
        ck_assert(facts_add_spo(g_f, "j", "k", "l"));
        ck_assert(facts_add_spo(g_f, "a", "b", "c"));
        ck_assert(facts_add_spo(g_f, "b", "c", "d"));
        ck_assert(facts_add_spo(g_f, "c", "d", "e"));
        ck_assert(facts_add_spo(g_f, "d", "e", "f"));
        ck_assert(facts_add_spo(g_f, "e", "f", "g"));
        ck_assert(facts_add_spo(g_f, "f", "g", "h"));
        ck_assert(facts_add_spo(g_f, "g", "h", "i"));
        ck_assert(facts_add_spo(g_f, "h", "i", "j"));
        ck_assert(facts_add_spo(g_f, "i", "j", "k"));
        ck_assert(facts_add_spo(g_f, "j", "k", "l"));
        ck_assert(facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(facts_remove_spo(g_f, "c", "d", "e"));
        ck_assert(facts_remove_spo(g_f, "d", "e", "f"));
        ck_assert(facts_remove_spo(g_f, "e", "f", "g"));
        ck_assert(facts_remove_spo(g_f, "f", "g", "h"));
        ck_assert(facts_remove_spo(g_f, "g", "h", "i"));
        ck_assert(facts_remove_spo(g_f, "h", "i", "j"));
        ck_assert(facts_remove_spo(g_f, "i", "j", "k"));
        ck_assert(facts_remove_spo(g_f, "j", "k", "l"));
        ck_assert(!facts_remove_spo(g_f, "a", "b", "c"));
        ck_assert(!facts_remove_spo(g_f, "b", "c", "d"));
        ck_assert(!facts_remove_spo(g_f, "c", "d", "e"));
        ck_assert(!facts_remove_spo(g_f, "d", "e", "f"));
        ck_assert(!facts_remove_spo(g_f, "e", "f", "g"));
        ck_assert(!facts_remove_spo(g_f, "f", "g", "h"));
        ck_assert(!facts_remove_spo(g_f, "g", "h", "i"));
        ck_assert(!facts_remove_spo(g_f, "h", "i", "j"));
        ck_assert(!facts_remove_spo(g_f, "i", "j", "k"));
        ck_assert(!facts_remove_spo(g_f, "j", "k", "l"));
        ck_assert(facts_count(g_f) == 0);
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_log_ten"
                          " test_facts_log_ten"));
}
END_TEST

START_TEST (test_write_facts_log_escapes)
{
        FILE *fp = fopen("test_write_facts_log_escapes", "w");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        g_f->log = fp;
        ck_assert(facts_add_spo(g_f, "\\", "\"", "\n"));
        ck_assert(facts_add_spo(g_f, "a\\", "a\\a", "a\\\\a"));
        ck_assert(facts_add_spo(g_f, "a\"", "a\"a", "a\"\"a"));
        ck_assert(facts_add_spo(g_f, "a\n", "a\na", "a\n\na"));
        ck_assert(facts_add_spo(g_f, "\\\"\n", "\\\"\n\\\"\n",
                                "\\\"\n\\\"\n\\\"\n"));
        ck_assert(facts_add_spo(g_f, "\\a", "\\b", "\\c"));
        ck_assert(facts_add_spo(g_f, "a\\a", "a\\aa", "a\\a\\aa"));
        ck_assert(facts_add_spo(g_f, "\\", "\"", "\n"));
        ck_assert(facts_add_spo(g_f, "a\\", "a\\a", "a\\\\a"));
        ck_assert(facts_add_spo(g_f, "a\"", "a\"a", "a\"\"a"));
        ck_assert(facts_add_spo(g_f, "a\n", "a\na", "a\n\na"));
        ck_assert(facts_add_spo(g_f, "\\\"\n", "\\\"\n\\\"\n",
                                "\\\"\n\\\"\n\\\"\n"));
        ck_assert(facts_add_spo(g_f, "\\a", "\\b", "\\c"));
        ck_assert(facts_add_spo(g_f, "a\\a", "a\\aa", "a\\a\\aa"));
        ck_assert(facts_remove_spo(g_f, "\\", "\"", "\n"));
        ck_assert(facts_remove_spo(g_f, "a\\", "a\\a", "a\\\\a"));
        ck_assert(facts_remove_spo(g_f, "a\"", "a\"a", "a\"\"a"));
        ck_assert(facts_remove_spo(g_f, "a\n", "a\na", "a\n\na"));
        ck_assert(facts_remove_spo(g_f, "\\\"\n", "\\\"\n\\\"\n",
                                   "\\\"\n\\\"\n\\\"\n"));
        ck_assert(facts_remove_spo(g_f, "\\a", "\\b", "\\c"));
        ck_assert(facts_remove_spo(g_f, "a\\a", "a\\aa", "a\\a\\aa"));
        ck_assert(!facts_remove_spo(g_f, "\\", "\"", "\n"));
        ck_assert(!facts_remove_spo(g_f, "a\\", "a\\a", "a\\\\a"));
        ck_assert(!facts_remove_spo(g_f, "a\"", "a\"a", "a\"\"a"));
        ck_assert(!facts_remove_spo(g_f, "a\n", "a\na", "a\n\na"));
        ck_assert(!facts_remove_spo(g_f, "\\\"\n", "\\\"\n\\\"\n",
                                   "\\\"\n\\\"\n\\\"\n"));
        ck_assert(!facts_remove_spo(g_f, "\\a", "\\b", "\\c"));
        ck_assert(!facts_remove_spo(g_f, "a\\a", "a\\aa", "a\\a\\aa"));
        ck_assert(facts_count(g_f) == 0);
        fclose(fp);
        ck_assert(!system("cmp test_write_facts_log_escapes"
                          " test_facts_log_escapes"));
}
END_TEST

void setup_read_facts_log ()
{
        g_f = new_facts(NULL, 10);
}

void teardown_read_facts_log ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_read_facts_log_empty)
{
        FILE *fp = fopen("test_facts_log_empty", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts_log(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

START_TEST (test_read_facts_log_one)
{
        FILE *fp = fopen("test_facts_log_one", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts_log(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

START_TEST (test_read_facts_log_two)
{
        FILE *fp = fopen("test_facts_log_two", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts_log(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

START_TEST (test_read_facts_log_ten)
{
        FILE *fp = fopen("test_facts_log_ten", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts_log(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

START_TEST (test_read_facts_log_escapes)
{
        FILE *fp = fopen("test_facts_log_escapes", "r");
        ck_assert(fp);
        ck_assert(facts_count(g_f) == 0);
        ck_assert(!read_facts_log(g_f, fp));
        fclose(fp);
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

void setup_anon ()
{
        g_f = new_facts(NULL, 10);
}

void teardown_anon ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_anon)
{
        const char *anon;
        ck_assert((anon = facts_anon(g_f, NULL)));
        ck_assert(!strncmp(anon, "anon-", 5));
        ck_assert(strlen(anon) == 15);
        ck_assert((anon = facts_anon(g_f, "")));
        ck_assert(!strncmp(anon, "anon-", 5));
        ck_assert(strlen(anon) == 15);
        ck_assert((anon = facts_anon(g_f, "?")));
        ck_assert(!strncmp(anon, "anon-", 5));
        ck_assert(strlen(anon) == 15);
        ck_assert((anon = facts_anon(g_f, "a")));
        ck_assert(!strncmp(anon, "a-", 2));
        ck_assert(strlen(anon) == 12);
        ck_assert((anon = facts_anon(g_f, "?a")));
        ck_assert(!strncmp(anon, "a-", 2));
        ck_assert(strlen(anon) == 12);
}
END_TEST

void setup_with ()
{
        g_f = new_facts(NULL, 10);
        facts_add_spo(g_f, "a", "b", "c");
        facts_add_spo(g_f, "a", "b", "d");
        facts_add_spo(g_f, "a", "e", "d");
        facts_add_spo(g_f, "g", "b", "c");
        facts_add_spo(g_f, "h", "i", "c");
}

void teardown_with ()
{
        delete_facts(g_f);
        g_f = NULL;
}

START_TEST (test_facts_with_empty)
{
        s_facts *facts = new_facts(NULL, 10);
        s_facts_with_cursor c;
        ck_assert(facts);
        facts_with(facts, NULL, &c, (const char *[]) {NULL, NULL});
        ck_assert(!facts_with_cursor_next(&c));
        facts_with_cursor_destroy(&c);
        facts_with(facts, NULL, &c, (const char *[]) {
                        "a", "a", "a", NULL, NULL});
        printf("a\n");
        ck_assert(!facts_with_cursor_next(&c));
        printf("b\n");
        facts_with_cursor_destroy(&c);
        printf("c\n");
        facts_with(facts, NULL, &c, (const char *[]) {
                        "a", "a", "a", "b", "c", NULL, NULL});
        printf("d\n");
        ck_assert(!facts_with_cursor_next(&c));
        printf("e\n");
        facts_with_cursor_destroy(&c);
        printf("f\n");
        facts_with(facts, NULL, &c, (const char *[]) {
                        "a", "a", "a", NULL,
                        "a", "b", "c", NULL, NULL});
        ck_assert(!facts_with_cursor_next(&c));
        facts_with_cursor_destroy(&c);
        delete_facts(facts);
        facts_with(g_f, NULL, &c, (const char *[]) {NULL, NULL});
        ck_assert(!facts_with_cursor_next(&c));
        facts_with_cursor_destroy(&c);
        facts_with(g_f, NULL, &c, (const char *[]) {
                        "a", "a", "a", NULL, NULL});
        ck_assert(!facts_with_cursor_next(&c));
        facts_with_cursor_destroy(&c);
        facts_with(g_f, NULL, &c, (const char *[]) {
                        "a", "a", "a", "b", "c", NULL, NULL});
        ck_assert(!facts_with_cursor_next(&c));
        facts_with_cursor_destroy(&c);
        facts_with(g_f, NULL, &c, (const char *[]) {
                        "a", "a", "a", NULL,
                        "a", "b", "c", NULL, NULL});
        ck_assert(!facts_with_cursor_next(&c));
        facts_with_cursor_destroy(&c);
}
END_TEST

START_TEST (test_facts_with_one)
{
        const char *a;
        const char *b;
        const char *c;
        const char *d;
        s_binding bindings[] = {{"?a", &a},
                                {"?b", &b},
                                {"?c", &c},
                                {"?d", &d},
                                {NULL, NULL}};
        s_facts *facts = new_facts(NULL, 10);
        s_facts_with_cursor cur;
        ck_assert(facts);
        ck_assert(facts_count(facts) == 0);
        ck_assert(facts_add_spo(facts, "a", "b", "c"));
        ck_assert(facts_count(facts) == 1);
        facts_with(facts, NULL, &cur, (const char *[]) {
                        "a", "b", "c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(facts, bindings, &cur, (const char *[]) {
                        "?a", "?b", "?c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!strcmp(a, "a"));
        ck_assert(!strcmp(b, "b"));
        ck_assert(!strcmp(c, "c"));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(facts, bindings, &cur, (const char *[]) {
                        "?a", "b", "c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!strcmp(a, "a"));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(facts, bindings, &cur, (const char *[]) {
                        "a", "?b", "c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!strcmp(b, "b"));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(facts, bindings, &cur, (const char *[]) {
                        "a", "b", "?c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!strcmp(c, "c"));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(g_f, NULL, &cur, (const char *[]) {
                        "a", "b", "c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(g_f, NULL, &cur, (const char *[]) {
                        "a", "b", "c", "b", "d", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
        facts_with(g_f, bindings, &cur, (const char *[]) {
                        "a", "b", "c", NULL,
                        "g", "?b", "?c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!strcmp(b, "b"));
        ck_assert(!strcmp(c, "c"));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
}
END_TEST

START_TEST (test_facts_with_bindings)
{
        const char *a;
        const char *b;
        const char *c;
        const char *d;
        s_binding bindings[] = {{"?a", &a},
                                {"?b", &b},
                                {"?c", &c},
                                {"?d", &d},
                                {NULL, NULL}};
        s_facts_with_cursor cur;
        facts_with(g_f, bindings, &cur, (const char *[]) {
                        "a", "?b", "?c", NULL,
                        "g", "?b", "?c", NULL, NULL});
        ck_assert(facts_with_cursor_next(&cur));
        ck_assert(!strcmp(b, "b"));
        ck_assert(!strcmp(c, "c"));
        ck_assert(!facts_with_cursor_next(&cur));
        facts_with_cursor_destroy(&cur);
}
END_TEST

Suite * facts_suite(void)
{
    Suite *s;
    TCase *tc_init;
    TCase *tc_add_fact;
    TCase *tc_add_spo;
    TCase *tc_add;
    TCase *tc_remove_fact;
    TCase *tc_remove_spo;
    TCase *tc_with_spo;
    TCase *tc_write;
    TCase *tc_read;
    TCase *tc_write_log;
    TCase *tc_read_log;
    TCase *tc_anon;
    TCase *tc_with;
    s = suite_create("Facts");
    tc_init = tcase_create("Init");
    tcase_add_test(tc_init, test_facts_init_destroy);
    tcase_add_test(tc_init, test_facts_new_delete);
    suite_add_tcase(s, tc_init);
    tc_add_fact = tcase_create("Add fact");
    tcase_add_checked_fixture(tc_add_fact, setup_add_fact,
                              teardown_add_fact);
    tcase_add_test(tc_add_fact, test_facts_add_fact_one);
    tcase_add_test(tc_add_fact, test_facts_add_fact_two);
    tcase_add_test(tc_add_fact, test_facts_add_fact_ten);
    suite_add_tcase(s, tc_add_fact);
    tc_add_spo = tcase_create("Add SPO");
    tcase_add_checked_fixture(tc_add_spo, setup_add_spo,
                              teardown_add_spo);
    tcase_add_test(tc_add_spo, test_facts_add_spo_one);
    tcase_add_test(tc_add_spo, test_facts_add_spo_two);
    tcase_add_test(tc_add_spo, test_facts_add_spo_ten);
    suite_add_tcase(s, tc_add_spo);
    tc_add = tcase_create("Add");
    tcase_add_checked_fixture(tc_add, setup_add,
                              teardown_add);
    tcase_add_test(tc_add, test_facts_add_one);
    tcase_add_test(tc_add, test_facts_add_two);
    tcase_add_test(tc_add, test_facts_add_ten);
    tcase_add_test(tc_add, test_facts_add_anon);
    suite_add_tcase(s, tc_add);
    tc_remove_fact = tcase_create("Remove fact");
    tcase_add_checked_fixture(tc_remove_fact, setup_remove_fact,
                              teardown_remove_fact);
    tcase_add_test(tc_remove_fact, test_facts_remove_fact_one);
    tcase_add_test(tc_remove_fact, test_facts_remove_fact_two);
    tcase_add_test(tc_remove_fact, test_facts_remove_fact_ten);
    suite_add_tcase(s, tc_remove_fact);
    tc_remove_spo = tcase_create("Remove SPO");
    tcase_add_checked_fixture(tc_remove_spo, setup_remove_spo,
                              teardown_remove_spo);
    tcase_add_test(tc_remove_spo, test_facts_remove_spo_one);
    tcase_add_test(tc_remove_spo, test_facts_remove_spo_two);
    tcase_add_test(tc_remove_spo, test_facts_remove_spo_ten);
    suite_add_tcase(s, tc_remove_spo);
    tc_with_spo = tcase_create("With SPO");
    tcase_add_checked_fixture(tc_with_spo, setup_with_spo,
                              teardown_with_spo);
    tcase_add_test(tc_with_spo, test_facts_with_spo_0);
    tcase_add_test(tc_with_spo, test_facts_with_spo_3);
    tcase_add_test(tc_with_spo, test_facts_with_spo_s);
    tcase_add_test(tc_with_spo, test_facts_with_spo_p);
    tcase_add_test(tc_with_spo, test_facts_with_spo_o);
    tcase_add_test(tc_with_spo, test_facts_with_spo_sp);
    tcase_add_test(tc_with_spo, test_facts_with_spo_po);
    tcase_add_test(tc_with_spo, test_facts_with_spo_os);
    suite_add_tcase(s, tc_with_spo);
    tc_write = tcase_create("Write");
    tcase_add_checked_fixture(tc_write, setup_write, teardown_write);
    tcase_add_test(tc_write, test_write_facts_empty);
    tcase_add_test(tc_write, test_write_facts_one);
    tcase_add_test(tc_write, test_write_facts_two);
    tcase_add_test(tc_write, test_write_facts_ten);
    tcase_add_test(tc_write, test_write_facts_escapes);
    suite_add_tcase(s, tc_write);
    tc_read = tcase_create("Read");
    tcase_add_checked_fixture(tc_read, setup_read, teardown_read);
    tcase_add_test(tc_read, test_read_facts_empty);
    tcase_add_test(tc_read, test_read_facts_one);
    tcase_add_test(tc_read, test_read_facts_two);
    tcase_add_test(tc_read, test_read_facts_ten);
    tcase_add_test(tc_read, test_read_facts_escapes);
    suite_add_tcase(s, tc_read);
    tc_write_log = tcase_create("Write log");
    tcase_add_checked_fixture(tc_write_log, setup_write_facts_log,
                              teardown_write_facts_log);
    tcase_add_test(tc_write_log, test_write_facts_log_one);
    tcase_add_test(tc_write_log, test_write_facts_log_two);
    tcase_add_test(tc_write_log, test_write_facts_log_ten);
    tcase_add_test(tc_write_log, test_write_facts_log_escapes);
    suite_add_tcase(s, tc_write_log);
    tc_read_log = tcase_create("Read log");
    tcase_add_checked_fixture(tc_read_log, setup_read_facts_log,
                              teardown_read_facts_log);
    tcase_add_test(tc_read_log, test_read_facts_log_empty);
    tcase_add_test(tc_read_log, test_read_facts_log_one);
    tcase_add_test(tc_read_log, test_read_facts_log_two);
    tcase_add_test(tc_read_log, test_read_facts_log_ten);
    tcase_add_test(tc_read_log, test_read_facts_log_escapes);
    suite_add_tcase(s, tc_read_log);
    tc_anon = tcase_create("Anon");
    tcase_add_checked_fixture(tc_anon, setup_anon, teardown_anon);
    tcase_add_test(tc_anon, test_facts_anon);
    suite_add_tcase(s, tc_anon);
    tc_with = tcase_create("With");
    tcase_add_checked_fixture(tc_with, setup_with, teardown_with);
    tcase_add_test(tc_with, test_facts_with_empty);
    tcase_add_test(tc_with, test_facts_with_one);
    tcase_add_test(tc_with, test_facts_with_bindings);
    /*
    tcase_add_test(tc_with, test_facts_with_two);
    tcase_add_test(tc_with, test_facts_with_ten);
    */
    suite_add_tcase(s, tc_with);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = facts_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}

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

s_facts *g_f;

START_TEST (test_facts_init_destroy)
{
        s_facts f;
        facts_init(&f);
        ck_assert(!facts_count(&f));
        facts_destroy(&f);
}
END_TEST

START_TEST (test_facts_new_delete)
{
        s_facts *f;
        f = new_facts();
        ck_assert(f);
        ck_assert(!facts_count(f));
        delete_facts(f);
}
END_TEST

void setup_add_fact ()
{
        g_f = new_facts();
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
}
END_TEST

void setup_add_spo ()
{
        g_f = new_facts();
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
}
END_TEST

void setup_remove_fact ()
{
        g_f = new_facts();
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
        s_fact *a = new_fact("a", "b", "c");
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_fact(g_f, a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(!facts_remove_fact(g_f, a));
        ck_assert(facts_count(g_f) == 9);
}
END_TEST

START_TEST (test_facts_remove_fact_two)
{
        s_fact *a  = new_fact("a", "b", "c");
        s_fact *b  = new_fact("b", "c", "d");
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_fact(g_f, a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_remove_fact(g_f, b));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_remove_fact(g_f, a));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(!facts_remove_fact(g_f, b));
        ck_assert(facts_count(g_f) == 8);
}
END_TEST

START_TEST (test_facts_remove_fact_ten)
{
        s_fact *a = new_fact("a", "b", "c");
        s_fact *b = new_fact("b", "c", "d");
        s_fact *c = new_fact("c", "d", "e");
        s_fact *d = new_fact("d", "e", "f");
        s_fact *e = new_fact("e", "f", "g");
        s_fact *f = new_fact("f", "g", "h");
        s_fact *g = new_fact("g", "h", "i");
        s_fact *h = new_fact("h", "i", "j");
        s_fact *i = new_fact("i", "j", "k");
        s_fact *j = new_fact("j", "k", "l");
        ck_assert(facts_count(g_f) == 10);
        ck_assert(facts_remove_fact(g_f, a));
        ck_assert(facts_count(g_f) == 9);
        ck_assert(facts_remove_fact(g_f, b));
        ck_assert(facts_count(g_f) == 8);
        ck_assert(facts_remove_fact(g_f, c));
        ck_assert(facts_count(g_f) == 7);
        ck_assert(facts_remove_fact(g_f, d));
        ck_assert(facts_count(g_f) == 6);
        ck_assert(facts_remove_fact(g_f, e));
        ck_assert(facts_count(g_f) == 5);
        ck_assert(facts_remove_fact(g_f, f));
        ck_assert(facts_count(g_f) == 4);
        ck_assert(facts_remove_fact(g_f, g));
        ck_assert(facts_count(g_f) == 3);
        ck_assert(facts_remove_fact(g_f, h));
        ck_assert(facts_count(g_f) == 2);
        ck_assert(facts_remove_fact(g_f, i));
        ck_assert(facts_count(g_f) == 1);
        ck_assert(facts_remove_fact(g_f, j));
        ck_assert(facts_count(g_f) == 0);
}
END_TEST

void setup_remove_spo ()
{
        g_f = new_facts();
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
        g_f = new_facts();
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

Suite * facts_suite(void)
{
    Suite *s;
    TCase *tc_init;
    TCase *tc_add_fact;
    TCase *tc_add_spo;
    TCase *tc_remove_fact;
    TCase *tc_remove_spo;
    TCase *tc_with_spo;
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
    suite_add_tcase(s, tc_with_spo);
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

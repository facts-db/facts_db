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
#include "set.h"

s_set g_set;

START_TEST (test_set_init_destroy)
{
        size_t max = 10;
        set_init(&g_set, max);
        ck_assert(g_set.max == max);
        ck_assert(g_set.count == 0);
        ck_assert(g_set.collisions == 0);
        set_destroy(&g_set);
        max = 100;
        set_init(&g_set, max);
        ck_assert(g_set.max == max);
        ck_assert(g_set.count == 0);
        ck_assert(g_set.collisions == 0);
        set_destroy(&g_set);
        max = 1000;
        set_init(&g_set, max);
        ck_assert(g_set.max == max);
        ck_assert(g_set.count == 0);
        ck_assert(g_set.collisions == 0);
        set_destroy(&g_set);
        max = 10000;
        set_init(&g_set, max);
        ck_assert(g_set.max == max);
        ck_assert(g_set.count == 0);
        ck_assert(g_set.collisions == 0);
        set_destroy(&g_set);
        max = 100000;
        set_init(&g_set, max);
        ck_assert(g_set.max == max);
        ck_assert(g_set.count == 0);
        ck_assert(g_set.collisions == 0);
        set_destroy(&g_set);
        max = 1000000;
        set_init(&g_set, max);
        ck_assert(g_set.max == max);
        ck_assert(g_set.count == 0);
        ck_assert(g_set.collisions == 0);
        set_destroy(&g_set);
}
END_TEST

START_TEST (test_set_new_delete)
{
        size_t max;
        s_set *set;
        max = 10;
        set = new_set(max);
        ck_assert(set);
        ck_assert(set->max == max);
        ck_assert(set->count == 0);
        ck_assert(set->collisions == 0);
        delete_set(set);
        max = 100;
        set = new_set(max);
        ck_assert(set);
        ck_assert(set->max == max);
        ck_assert(set->count == 0);
        ck_assert(set->collisions == 0);
        delete_set(set);
        max = 1000;
        set = new_set(max);
        ck_assert(set);
        ck_assert(set->max == max);
        ck_assert(set->count == 0);
        ck_assert(set->collisions == 0);
        delete_set(set);
        max = 10000;
        set = new_set(max);
        ck_assert(set);
        ck_assert(set->max == max);
        ck_assert(set->count == 0);
        ck_assert(set->collisions == 0);
        delete_set(set);
        max = 100000;
        set = new_set(max);
        ck_assert(set);
        ck_assert(set->max == max);
        ck_assert(set->count == 0);
        ck_assert(set->collisions == 0);
        delete_set(set);
        max = 1000000;
        set = new_set(max);
        ck_assert(set);
        ck_assert(set->max == max);
        ck_assert(set->count == 0);
        ck_assert(set->collisions == 0);
        delete_set(set);
}
END_TEST

void setup_add ()
{
        set_init(&g_set, 10);
}

void teardown_add ()
{
        set_destroy(&g_set);
}

START_TEST (test_set_add_one)
{
        s_set_item *ia;
        ck_assert(g_set.count == 0);
        ck_assert((ia = set_add(&g_set, "a", 1)));
        ck_assert(g_set.count == 1);
        ck_assert(ia == set_add(&g_set, "a", 1));
        ck_assert(g_set.count == 1);
        ck_assert(ia == set_get(&g_set, "a", 1));
}
END_TEST

START_TEST (test_set_add_two)
{
        s_set_item *ia;
        s_set_item *ib;
        ck_assert(g_set.count == 0);
        ck_assert((ia = set_add(&g_set, "a", 1)));
        ck_assert(g_set.count == 1);
        ck_assert((ib = set_add(&g_set, "b", 1)));
        ck_assert(g_set.count == 2);
        ck_assert(ia == set_add(&g_set, "a", 1));
        ck_assert(g_set.count == 2);
        ck_assert(ib == set_add(&g_set, "b", 1));
        ck_assert(g_set.count == 2);
        ck_assert(ia == set_get(&g_set, "a", 1));
        ck_assert(ib == set_get(&g_set, "b", 1));
}
END_TEST

START_TEST (test_set_add_ten)
{
        ck_assert(g_set.count == 0);
        ck_assert(set_add(&g_set, "a", 1));
        ck_assert(g_set.count == 1);
        ck_assert(set_add(&g_set, "b", 1));
        ck_assert(g_set.count == 2);
        ck_assert(set_add(&g_set, "c", 1));
        ck_assert(g_set.count == 3);
        ck_assert(set_add(&g_set, "d", 1));
        ck_assert(g_set.count == 4);
        ck_assert(set_add(&g_set, "e", 1));
        ck_assert(g_set.count == 5);
        ck_assert(set_add(&g_set, "f", 1));
        ck_assert(g_set.count == 6);
        ck_assert(set_add(&g_set, "g", 1));
        ck_assert(g_set.count == 7);
        ck_assert(set_add(&g_set, "h", 1));
        ck_assert(g_set.count == 8);
        ck_assert(set_add(&g_set, "i", 1));
        ck_assert(g_set.count == 9);
        ck_assert(set_add(&g_set, "j", 1));
        ck_assert(g_set.count == 10);
}
END_TEST

Suite * set_suite(void)
{
    Suite *s;
    TCase *tc_init;
    TCase *tc_add;
    s = suite_create("Set");
    tc_init = tcase_create("Init");
    tcase_add_test(tc_init, test_set_init_destroy);
    tcase_add_test(tc_init, test_set_new_delete);
    suite_add_tcase(s, tc_init);
    tc_add = tcase_create("Add");
    tcase_add_checked_fixture(tc_add, setup_add, teardown_add);
    tcase_add_test(tc_add, test_set_add_one);
    tcase_add_test(tc_add, test_set_add_two);
    tcase_add_test(tc_add, test_set_add_ten);
    suite_add_tcase(s, tc_add);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = set_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}

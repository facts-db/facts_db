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
#include "fact.h"

START_TEST (test_fact_init)
{
  s_fact f;
  fact_init(&f, NULL, NULL, NULL);
  ck_assert(!f.s);
  ck_assert(!f.p);
  ck_assert(!f.o);
  fact_init(&f, "a", "b", "c");
  ck_assert(f.s);
  ck_assert(f.p);
  ck_assert(f.o);
}
END_TEST

START_TEST (test_new_fact)
{
  s_fact *f;
  f = new_fact(NULL, NULL, NULL);
  ck_assert(f);
  ck_assert(!f->s);
  ck_assert(!f->p);
  ck_assert(!f->o);
  delete_fact(f);
  f = new_fact("a", "b", "c");
  ck_assert(f);
  ck_assert(f->s);
  ck_assert(f->p);
  ck_assert(f->o);
  delete_fact(f);
}
END_TEST

START_TEST (test_fact_compare_spo)
{
  s_fact a;
  s_fact b;
  fact_init(&a, "a", "b", "c");
  ck_assert(fact_compare_spo(NULL, &a) <  0);
  ck_assert(fact_compare_spo(&a, &a)   == 0);
  ck_assert(fact_compare_spo(&a, NULL) >  0);
  fact_init(&b, "a", "b", "c");
  ck_assert(fact_compare_spo(&a, &b) == 0);
  ck_assert(fact_compare_spo(&b, &a) == 0);
  fact_init(&b, P_FIRST, P_FIRST, P_FIRST);
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, P_FIRST, P_FIRST, "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, P_FIRST, "b", "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, "a", P_FIRST, "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, "a", "b", P_FIRST);
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, P_LAST, P_LAST, P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, P_LAST, P_LAST, "c");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, P_LAST, "b", "c");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "a", P_LAST, "c");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "a", "b", P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "a", "b", "d");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "a", "a", "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, "a", "d", "c");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "b", "c", "d");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
}
END_TEST

START_TEST (test_fact_compare_pos)
{
  s_fact a;
  s_fact b;
  fact_init(&a, "c", "a", "b");
  ck_assert(fact_compare_pos(NULL, &a) <  0);
  ck_assert(fact_compare_pos(&a, &a)   == 0);
  ck_assert(fact_compare_pos(&a, NULL) >  0);
  fact_init(&b, "c", "a", "b");
  ck_assert(fact_compare_pos(&a, &b) == 0);
  ck_assert(fact_compare_pos(&b, &a) == 0);
  fact_init(&b, P_FIRST, P_FIRST, P_FIRST);
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", P_FIRST, P_FIRST);
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", P_FIRST, "b");
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", "a", P_FIRST);
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, P_FIRST, "a", "b");
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, P_LAST, P_LAST, P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "c", P_LAST, P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "c", P_LAST, "b");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "c", "a", P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, P_LAST, "a", "b");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "d", "a", "b");
  ck_assert(fact_compare_pos(&a, &b) < 0);
  ck_assert(fact_compare_pos(&b, &a) > 0);
  fact_init(&b, "c", "a", "a");
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", "a", "d");
  ck_assert(fact_compare_pos(&a, &b) < 0);
  ck_assert(fact_compare_pos(&b, &a) > 0);
  fact_init(&b, "d", "b", "c");
  ck_assert(fact_compare_pos(&a, &b) < 0);
  ck_assert(fact_compare_pos(&b, &a) > 0);
}
END_TEST

START_TEST (test_fact_compare_osp)
{
  s_fact a;
  s_fact b;
  fact_init(&a, "b", "c", "a");
  ck_assert(fact_compare_osp(NULL, &a) <  0);
  ck_assert(fact_compare_osp(&a, &a)   == 0);
  ck_assert(fact_compare_osp(&a, NULL) >  0);
  fact_init(&b, "b", "c", "a");
  ck_assert(fact_compare_osp(&a, &b) == 0);
  ck_assert(fact_compare_osp(&b, &a) == 0);
  fact_init(&b, P_FIRST, P_FIRST, P_FIRST);
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, P_FIRST, "c", P_FIRST);
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, "b", "c", P_FIRST);
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, P_FIRST, "c", "a");
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, "b", P_FIRST, "a");
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, P_LAST, P_LAST, P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, P_LAST, "c", P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "b", "c", P_LAST);
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, P_LAST, "c", "a");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "b", P_LAST, "a");
  ck_assert(fact_compare_spo(&a, &b) < 0);
  ck_assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "b", "d", "a");
  ck_assert(fact_compare_osp(&a, &b) < 0);
  ck_assert(fact_compare_osp(&b, &a) > 0);
  fact_init(&b, "a", "c", "a");
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, "d", "c", "a");
  ck_assert(fact_compare_osp(&a, &b) < 0);
  ck_assert(fact_compare_osp(&b, &a) > 0);
  fact_init(&b, "c", "d", "b");
  ck_assert(fact_compare_osp(&a, &b) < 0);
  ck_assert(fact_compare_osp(&b, &a) > 0);
}
END_TEST

Suite * fact_suite(void)
{
    Suite *s;
    TCase *tc_init;
    TCase *tc_compare;
    s = suite_create("Fact");
    tc_init = tcase_create("Init");
    tcase_add_test(tc_init, test_fact_init);
    tcase_add_test(tc_init, test_new_fact);
    suite_add_tcase(s, tc_init);
    tc_compare = tcase_create("Compare");
    tcase_add_test(tc_compare, test_fact_compare_spo);
    tcase_add_test(tc_compare, test_fact_compare_pos);
    tcase_add_test(tc_compare, test_fact_compare_osp);
    suite_add_tcase(s, tc_compare);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = fact_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}

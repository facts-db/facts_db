
#include <assert.h>
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
  fact_init(&b, NULL, NULL, NULL);
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, NULL, NULL, "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, NULL, "b", "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, "a", NULL, "c");
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
  fact_init(&b, "a", "b", NULL);
  ck_assert(fact_compare_spo(&a, &b) > 0);
  ck_assert(fact_compare_spo(&b, &a) < 0);
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
  fact_init(&b, NULL, NULL, NULL);
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", NULL, NULL);
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", NULL, "b");
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, "c", "a", NULL);
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
  fact_init(&b, NULL, "a", "b");
  ck_assert(fact_compare_pos(&a, &b) > 0);
  ck_assert(fact_compare_pos(&b, &a) < 0);
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
  fact_init(&b, NULL, NULL, NULL);
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, NULL, "c", NULL);
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, "b", "c", NULL);
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, NULL, "c", "a");
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
  fact_init(&b, "b", NULL, "a");
  ck_assert(fact_compare_osp(&a, &b) > 0);
  ck_assert(fact_compare_osp(&b, &a) < 0);
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

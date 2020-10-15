
#include <assert.h>
#include <check.h>
#include <stdlib.h>
#include "fact.h"

START_TEST (test_fact_init)
{
  s_fact f;
  fact_init(&f, NULL, NULL, NULL);
  assert(!f.s);
  assert(!f.p);
  assert(!f.o);
  fact_init(&f, "a", "b", "c");
  assert(f.s);
  assert(f.p);
  assert(f.o);
}
END_TEST

START_TEST (test_new_fact)
{
  s_fact *f;
  f = new_fact(NULL, NULL, NULL);
  assert(f);
  assert(!f->s);
  assert(!f->p);
  assert(!f->o);
  free(f);
  f = new_fact("a", "b", "c");
  assert(f);
  assert(f->s);
  assert(f->p);
  assert(f->o);
  free(f);
}
END_TEST

START_TEST (test_fact_compare_spo)
{
  s_fact a;
  s_fact b;
  fact_init(&a, "a", "b", "c");
  assert(fact_compare_spo(NULL, &a) <  0);
  assert(fact_compare_spo(&a, &a)   == 0);
  assert(fact_compare_spo(&a, NULL) >  0);
  fact_init(&b, "a", "d", "e");
  assert(fact_compare_spo(&a, &b) < 0);
  assert(fact_compare_spo(&b, &a) > 0);
  fact_init(&b, "a", "b", NULL);
  assert(fact_compare_spo(&a, &b) > 0);
  assert(fact_compare_spo(&b, &a) < 0);
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

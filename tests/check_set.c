#include <assert.h>
#include <check.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "set.h"

s_set g_s;

START_TEST (test_set_init)
{
  set_init(&g_s);
}
END_TEST

void setup_insert ()
{
  set_init(&g_s);
}

void teardown_insert ()
{
  set_clear(&g_s);
}

START_TEST (test_set_insert_one)
{
  s_item *a;
  a = set_insert(&g_s, "0123456789", 10);
  assert(a);
  assert(g_s.size == 1);
  assert(set_insert(&g_s, "0123456789", 10) == a);
  assert(g_s.size == 1);
}
END_TEST

START_TEST (test_set_insert_two)
{
  s_item *a;
  s_item *b;
  assert(a = set_insert(&g_s, "0123456789", 10));
  assert(g_s.size == 1);
  assert(b = set_insert(&g_s, "ABCDEFGHIJ", 10));
  assert(g_s.size == 2);
  assert(set_insert(&g_s, "0123456789", 10) == a);
  assert(g_s.size == 2);
  assert(set_insert(&g_s, "ABCDEFGHIJ", 10) == b);
  assert(g_s.size == 2);
}
END_TEST

/*
START_TEST (test_set_append_ten)
{
  struct stat s;
  assert(set_append(&g_s, "0123456789", 10) == 0);
  assert(g_s.size == 1);
  assert(set_append(&g_s, "1123456789", 10) == 1);
  assert(g_s.size == 2);
  assert(set_append(&g_s, "2123456789", 10) == 2);
  assert(g_s.size == 3);
  assert(set_append(&g_s, "3123456789", 10) == 3);
  assert(g_s.size == 4);
  assert(set_append(&g_s, "4123456789", 10) == 4);
  assert(g_s.size == 5);
  assert(set_append(&g_s, "5123456789", 10) == 5);
  assert(g_s.size == 6);
  assert(set_append(&g_s, "6123456789", 10) == 6);
  assert(g_s.size == 7);
  assert(set_append(&g_s, "7123456789", 10) == 7);
  assert(g_s.size == 8);
  assert(set_append(&g_s, "8123456789", 10) == 8);
  assert(g_s.size == 9);
  assert(set_append(&g_s, "9123456789", 10) == 9);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "0123456789", 10) == 0);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "1123456789", 10) == 1);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "2123456789", 10) == 2);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "3123456789", 10) == 3);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "4123456789", 10) == 4);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "5123456789", 10) == 5);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "6123456789", 10) == 6);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "7123456789", 10) == 7);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "8123456789", 10) == 8);
  assert(g_s.size == 10);
  assert(set_append(&g_s, "9123456789", 10) == 9);
  assert(g_s.size == 10);
  set_close(&g_s);
  assert(stat("fixtures/append.set", &s) == 0);
  assert(s.st_size == 100);
  assert(S_ISREG(s.st_mode));
  assert(stat("fixtures/append.set.index", &s) == 0);
  assert(s.st_size == 160);
  assert(S_ISREG(s.st_mode));
}
END_TEST
*/

Suite * skiplist_suite(void)
{
    Suite *s;
    TCase *tc_init;
    TCase *tc_insert;
    s = suite_create("Set");
    tc_init = tcase_create("Init");
    tcase_add_test(tc_init, test_set_init);
    suite_add_tcase(s, tc_init);
    tc_insert = tcase_create("Insert");
    tcase_add_checked_fixture(tc_insert, setup_insert, teardown_insert);
    tcase_add_test(tc_insert, test_set_insert_one);
    tcase_add_test(tc_insert, test_set_insert_two);
    /*tcase_add_test(tc_insert, test_set_insert_ten);*/
    suite_add_tcase(s, tc_insert);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = skiplist_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? 0 : 1;
}

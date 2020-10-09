
#include <assert.h>
#include <check.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "set.h"

s_set g_s;

void setup_create ()
{
  bzero(&g_s, sizeof(s_set));
  mkdir("fixtures", 511);
}

void teardown_create ()
{
  bzero(&g_s, sizeof(s_set));
}

START_TEST (test_set_create)
{
  struct stat s;
  unlink("fixtures/create.set");
  unlink("fixtures/create.set.index");
  unlink("fixtures/create.set.order");
  assert(set_open(&g_s, "fixtures/create.set") == 0);
  assert(g_s.size == 0);
  assert(g_s.max > g_s.size);
  set_close(&g_s);
  assert(stat("fixtures/create.set", &s) == 0);
  assert(s.st_size == 0);
  assert(S_ISREG(s.st_mode));
  assert(stat("fixtures/create.set.index", &s) == 0);
  assert(s.st_size == 0);
  assert(S_ISREG(s.st_mode));
}
END_TEST

void setup_append ()
{
  bzero(&g_s, sizeof(s_set));
  unlink("fixtures/append.set");
  unlink("fixtures/append.set.index");
  unlink("fixtures/append.set.order");
  assert(set_open(&g_s, "fixtures/append.set") == 0);
}

void teardown_append ()
{
  bzero(&g_s, sizeof(s_set));
}

START_TEST (test_set_append_one)
{
  struct stat s;
  assert(set_append(&g_s, "0123456789", 10) == 0);
  assert(g_s.size == 1);
  printf("offset: %ld\n", g_s.index[0].d.offset);
  assert(g_s.index[0].d.offset == 0);
  printf("size: %ld\n", g_s.index[0].d.size);
  assert(g_s.index[0].d.size == 10);
  assert(set_append(&g_s, "0123456789", 10) == 0);
  assert(g_s.size == 1);
  set_close(&g_s);
  assert(stat("fixtures/append.set", &s) == 0);
  assert(s.st_size == 10);
  assert(S_ISREG(s.st_mode));
  assert(stat("fixtures/append.set.index", &s) == 0);
  assert(s.st_size == 16);
  assert(S_ISREG(s.st_mode));
}
END_TEST

START_TEST (test_set_append_two)
{
  long i;
  struct stat s;
  assert(set_append(&g_s, "0123456789", 10) == 0);
  assert(g_s.size == 1);
  assert(set_append(&g_s, "ABCDEFGHIJ", 10) == 1);
  assert(g_s.size == 2);
  assert(set_append(&g_s, "0123456789", 10) == 0);
  assert(g_s.size == 2);
  i = set_append(&g_s, "ABCDEFGHIJ", 10);
  printf("%ld\n", i);
  assert(i == 1);
  assert(g_s.size == 2);
  set_close(&g_s);
  assert(stat("fixtures/append.set", &s) == 0);
  assert(s.st_size == 20);
  assert(S_ISREG(s.st_mode));
  assert(stat("fixtures/append.set.index", &s) == 0);
  assert(s.st_size == 32);
  assert(S_ISREG(s.st_mode));
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
    TCase *tc_create;
    TCase *tc_append;
    s = suite_create("Set");
    tc_create = tcase_create("Create");
    tcase_add_checked_fixture(tc_create, setup_create, teardown_create);
    tcase_add_test(tc_create, test_set_create);
    suite_add_tcase(s, tc_create);
    tc_append = tcase_create("Append");
    tcase_add_checked_fixture(tc_append, setup_append, teardown_append);
    tcase_add_test(tc_append, test_set_append_one);
    tcase_add_test(tc_append, test_set_append_two);
    /*tcase_add_test(tc_append, test_set_append_ten);*/
    suite_add_tcase(s, tc_append);
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

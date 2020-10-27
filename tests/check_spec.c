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
#include "spec.h"

START_TEST (test_spec_cursor_empty)
{
        s_spec_cursor c;
        s_fact f;
        spec_cursor_init(&c, (const char *[]) {NULL, NULL});
        ck_assert(!spec_cursor_next(&c, &f));
}
END_TEST

START_TEST (test_spec_cursor_one)
{
        s_spec_cursor c;
        s_fact f;
        spec_cursor_init(&c, (const char *[]) {
                        "a", "b", "c", NULL, NULL});
        ck_assert(spec_cursor_next(&c, &f));
        ck_assert(!strcmp(f.s, "a"));
        ck_assert(!strcmp(f.p, "b"));
        ck_assert(!strcmp(f.o, "c"));
        ck_assert(!spec_cursor_next(&c, &f));
}
END_TEST

START_TEST (test_spec_cursor_two)
{
        s_spec_cursor c;
        s_fact f;
        spec_cursor_init(&c, (const char *[]) {
                        "a", "b", "c", "d", "e", NULL, NULL});
        ck_assert(spec_cursor_next(&c, &f));
        ck_assert(!strcmp(f.s, "a"));
        ck_assert(!strcmp(f.p, "b"));
        ck_assert(!strcmp(f.o, "c"));
        ck_assert(spec_cursor_next(&c, &f));
        ck_assert(!strcmp(f.s, "a"));
        ck_assert(!strcmp(f.p, "d"));
        ck_assert(!strcmp(f.o, "e"));
        ck_assert(!spec_cursor_next(&c, &f));
        spec_cursor_init(&c, (const char *[]) {
                        "a", "b", "c", NULL,
                        "b", "d", "e", NULL, NULL});
        ck_assert(spec_cursor_next(&c, &f));
        ck_assert(!strcmp(f.s, "a"));
        ck_assert(!strcmp(f.p, "b"));
        ck_assert(!strcmp(f.o, "c"));
        ck_assert(spec_cursor_next(&c, &f));
        ck_assert(!strcmp(f.s, "b"));
        ck_assert(!strcmp(f.p, "d"));
        ck_assert(!strcmp(f.o, "e"));
        ck_assert(!spec_cursor_next(&c, &f));
}
END_TEST

Suite * spec_suite(void)
{
        Suite *s;
        TCase *tc_cursor;
        s = suite_create("Spec");
        tc_cursor = tcase_create("Cursor");
        tcase_add_test(tc_cursor, test_spec_cursor_empty);
        tcase_add_test(tc_cursor, test_spec_cursor_one);
        tcase_add_test(tc_cursor, test_spec_cursor_two);
        suite_add_tcase(s, tc_cursor);
        return s;
}

int main(void)
{
        int number_failed;
        Suite *s;
        SRunner *sr;

        s = spec_suite();
        sr = srunner_create(s);

        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        srunner_free(sr);
        return (number_failed == 0) ? 0 : 1;
}

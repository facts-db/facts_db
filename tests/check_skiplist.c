
#include <assert.h>
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include "skiplist.h"

s_skiplist *g_sl = NULL;

START_TEST (test_skiplist_init_destroy)
{
        unsigned long i;
        unsigned long max_height = 5;
        s_skiplist *sl = alloca(skiplist_size(max_height));
        skiplist_init(sl, max_height, 4);
        ck_assert(sl->length == 0);
        ck_assert(sl->head);
        for (i = 0; i < max_height; i++)
                ck_assert(skiplist_node_next(sl->head, i) == NULL);
        ck_assert(sl->max_height == max_height);
        skiplist_destroy(sl);
}
END_TEST

START_TEST (test_skiplist_new_delete)
{
        unsigned long i;
        unsigned long max_height = 5;
        s_skiplist *sl = new_skiplist(max_height, 4);
        ck_assert(sl && sl->length == 0);
        for (i = 0; i < max_height; i++)
                ck_assert(skiplist_node_next(sl->head, i) == NULL);
        delete_skiplist(sl);
}
END_TEST

void setup_inserts ()
{
        g_sl = new_skiplist(5, 4);
}

void teardown_inserts ()
{
        delete_skiplist(g_sl);
}

START_TEST (test_skiplist_insert_one)
{
        skiplist_insert(g_sl, (void*) 1);
        skiplist_insert(g_sl, (void*) 1);
        ck_assert(g_sl->length == 1);
        ck_assert(skiplist_find(g_sl, (void*) 1));
        ck_assert(skiplist_find(g_sl, (void*) 2) == 0);
}
END_TEST

START_TEST (test_skiplist_insert_two)
{
        skiplist_insert(g_sl, (void*) 1);
        skiplist_insert(g_sl, (void*) 2);
        skiplist_insert(g_sl, (void*) 1);
        skiplist_insert(g_sl, (void*) 2);
        ck_assert(g_sl->length == 2);
        ck_assert(skiplist_find(g_sl, (void*) 1));
        ck_assert(skiplist_find(g_sl, (void*) 2));
        ck_assert(skiplist_find(g_sl, (void*) 3) == 0);
}
END_TEST

START_TEST (test_skiplist_insert_ten)
{
        skiplist_insert(g_sl, (void*) 1);
        skiplist_insert(g_sl, (void*) 2);
        skiplist_insert(g_sl, (void*) 3);
        skiplist_insert(g_sl, (void*) 4);
        skiplist_insert(g_sl, (void*) 5);
        skiplist_insert(g_sl, (void*) 6);
        skiplist_insert(g_sl, (void*) 7);
        skiplist_insert(g_sl, (void*) 8);
        skiplist_insert(g_sl, (void*) 9);
        skiplist_insert(g_sl, (void*) 10);
        ck_assert(g_sl->length == 10);
        ck_assert(skiplist_find(g_sl, (void*) 1));
        ck_assert(skiplist_find(g_sl, (void*) 2));
        ck_assert(skiplist_find(g_sl, (void*) 3));
        ck_assert(skiplist_find(g_sl, (void*) 4));
        ck_assert(skiplist_find(g_sl, (void*) 5));
        ck_assert(skiplist_find(g_sl, (void*) 6));
        ck_assert(skiplist_find(g_sl, (void*) 7));
        ck_assert(skiplist_find(g_sl, (void*) 8));
        ck_assert(skiplist_find(g_sl, (void*) 9));
        ck_assert(skiplist_find(g_sl, (void*) 10));
        ck_assert(skiplist_find(g_sl, (void*) 11) == 0);
}
END_TEST

void setup_pred ()
{
        g_sl = new_skiplist(5, 4);
        skiplist_insert(g_sl, (void*) 2);
        skiplist_insert(g_sl, (void*) 3);
}

void teardown_pred ()
{
        delete_skiplist(g_sl);
}

START_TEST (test_skiplist_pred_empty)
{
        s_skiplist *sl = new_skiplist(5, 4);
        s_skiplist_node *pred;
        unsigned long level;
        ck_assert(sl);
        pred = skiplist_pred(sl, (void*) 1);
        for (level = 0; level < pred->height; level++) {
                ck_assert(skiplist_node_next(pred, level) == sl->head);
        }
        delete_skiplist_node(pred);
        delete_skiplist(sl);
}
END_TEST

START_TEST (test_skiplist_pred_before_first)
{
        s_skiplist_node *pred;
        unsigned long level;
        pred = skiplist_pred(g_sl, (void*) 1);
        for (level = 0; level < pred->height; level++) {
                ck_assert(skiplist_node_next(pred, level) == g_sl->head);
        }
        delete_skiplist_node(pred);
}
END_TEST

START_TEST (test_skiplist_pred_first)
{
        s_skiplist_node *pred;
        s_skiplist_node *p;
        unsigned long level;
        unsigned long height;
        pred = skiplist_pred(g_sl, (void*) 2);
        ck_assert(pred);
        p = skiplist_node_next(g_sl->head, 0);
        ck_assert(p);
        ck_assert(p->value == (void*) 2);
        height = p->height;
        for (level = 0; level < height; level++) {
                p = skiplist_node_next(pred, level);
                ck_assert(p == g_sl->head);
                ck_assert(skiplist_node_next(p, level));
                ck_assert(skiplist_node_next(p, level)->value == (void*) 2);
        }
        delete_skiplist_node(pred);
}
END_TEST

START_TEST (test_skiplist_pred_last)
{
        s_skiplist_node *pred;
        s_skiplist_node *p;
        unsigned long level;
        unsigned long height;
        pred = skiplist_pred(g_sl, (void*) 3);
        ck_assert(pred);
        p = skiplist_node_next(pred, 0);
        ck_assert(p);
        p = skiplist_node_next(p, 0);
        ck_assert(p);
        ck_assert(p->value == (void*) 3);
        height = p->height;
        for (level = 0; level < height; level++) {
                p = skiplist_node_next(pred, level);
                ck_assert(p);
                ck_assert(skiplist_node_next(p, level));
                ck_assert(skiplist_node_next(p, level)->value == (void*) 3);
        }
        delete_skiplist_node(pred);
}
END_TEST

START_TEST (test_skiplist_pred_after_last)
{
        s_skiplist_node *pred;
        s_skiplist_node *p;
        unsigned long level;
        unsigned long height;
        pred = skiplist_pred(g_sl, (void*) 4);
        ck_assert(pred);
        p = skiplist_node_next(pred, 0);
        ck_assert(p);
        ck_assert(p->value == (void*) 3);
        height = p->height;
        for (level = 0; level < height; level++) {
                p = skiplist_node_next(pred, level);
                ck_assert(p);
                ck_assert(p->value == (void*) 3);
                ck_assert(skiplist_node_next(p, level) == 0);
        }
        delete_skiplist_node(pred);
}
END_TEST

void setup_remove ()
{
        g_sl = new_skiplist(5, 4);
        skiplist_insert(g_sl, (void*) 1);
        skiplist_insert(g_sl, (void*) 2);
        skiplist_insert(g_sl, (void*) 3);
        skiplist_insert(g_sl, (void*) 4);
        skiplist_insert(g_sl, (void*) 5);
        skiplist_insert(g_sl, (void*) 6);
        skiplist_insert(g_sl, (void*) 7);
        skiplist_insert(g_sl, (void*) 8);
        skiplist_insert(g_sl, (void*) 9);
        skiplist_insert(g_sl, (void*) 10);
}

void teardown_remove ()
{
        delete_skiplist(g_sl);
}

START_TEST (test_skiplist_remove_first)
{
        ck_assert(g_sl->length == 10);
        ck_assert((void*) 1 == skiplist_remove(g_sl, (void*) 1));
        ck_assert(g_sl->length == 9);
}
END_TEST

START_TEST (test_skiplist_remove_nonexistent)
{
        ck_assert(g_sl->length == 10);
        ck_assert(NULL == skiplist_remove(g_sl, (void*) 1000));
        ck_assert(g_sl->length == 10);
}
END_TEST

START_TEST (test_skiplist_remove_last)
{
        ck_assert((void*) 10 == skiplist_remove(g_sl, (void*) 10));
        ck_assert(g_sl->length == 9);
}
END_TEST

START_TEST (test_skiplist_remove_middle)
{
        ck_assert((void*) 5 == skiplist_remove(g_sl, (void*) 5));
        ck_assert(g_sl->length == 9);
}
END_TEST

START_TEST (test_skiplist_remove_all)
{
        ck_assert((void*) 1 == skiplist_remove(g_sl, (void*) 1));
        ck_assert((void*) 2 == skiplist_remove(g_sl, (void*) 2));
        ck_assert((void*) 3 == skiplist_remove(g_sl, (void*) 3));
        ck_assert((void*) 4 == skiplist_remove(g_sl, (void*) 4));
        ck_assert((void*) 5 == skiplist_remove(g_sl, (void*) 5));
        ck_assert((void*) 6 == skiplist_remove(g_sl, (void*) 6));
        ck_assert((void*) 7 == skiplist_remove(g_sl, (void*) 7));
        ck_assert((void*) 8 == skiplist_remove(g_sl, (void*) 8));
        ck_assert((void*) 9 == skiplist_remove(g_sl, (void*) 9));
        ck_assert((void*) 10 == skiplist_remove(g_sl, (void*) 10));
        ck_assert(g_sl->length == 0);
}
END_TEST

void setup_iter ()
{
        g_sl = new_skiplist(5, 4);
        skiplist_insert(g_sl, (void*) 2);
        skiplist_insert(g_sl, (void*) 4);
        skiplist_insert(g_sl, (void*) 6);
        skiplist_insert(g_sl, (void*) 8);
        skiplist_insert(g_sl, (void*) 10);
}

void teardown_iter ()
{
        delete_skiplist(g_sl);
}

START_TEST (test_skiplist_iter_empty)
{
        s_skiplist *sl = new_skiplist(5, 4);
        ck_assert(sl);
        ck_assert(sl->length == 0);
        ck_assert(!skiplist_cursor(sl, (void*) 1));
        delete_skiplist(sl);
}
END_TEST

START_TEST (test_skiplist_iter_start)
{
        s_skiplist_node *n;
        n = skiplist_cursor(g_sl, (void*) 0);
        ck_assert(n);
        ck_assert(n->value == (void*) 2);
        n = skiplist_cursor(g_sl, (void*) 1);
        ck_assert(n);
        ck_assert(n->value == (void*) 2);
        n = skiplist_cursor(g_sl, (void*) 2);
        ck_assert(n);
        ck_assert(n->value == (void*) 2);
}
END_TEST

START_TEST (test_skiplist_iter_middle)
{
        s_skiplist_node *n;
        n = skiplist_cursor(g_sl, (void*) 2);
        ck_assert(n);
        ck_assert(n->value == (void*) 2);
        n = skiplist_cursor(g_sl, (void*) 3);
        ck_assert(n);
        ck_assert(n->value == (void*) 4);
        n = skiplist_cursor(g_sl, (void*) 4);
        ck_assert(n);
        ck_assert(n->value == (void*) 4);
        n = skiplist_cursor(g_sl, (void*) 5);
        ck_assert(n);
        ck_assert(n->value == (void*) 6);
        n = skiplist_cursor(g_sl, (void*) 6);
        ck_assert(n);
        ck_assert(n->value == (void*) 6);
}
END_TEST

START_TEST (test_skiplist_iter_end)
{
        s_skiplist_node *n;
        n = skiplist_cursor(g_sl, (void*) 9);
        ck_assert(n);
        ck_assert(n->value == (void*) 10);
        n = skiplist_cursor(g_sl, (void*) 10);
        ck_assert(n);
        ck_assert(n->value == (void*) 10);
        n = skiplist_cursor(g_sl, (void*) 11);
        ck_assert(!n);
}
END_TEST

Suite * skiplist_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_inserts;
    TCase *tc_pred;
    TCase *tc_remove;
    TCase *tc_iter;
    s = suite_create("Skiplist");
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_skiplist_new_delete);
    tcase_add_test(tc_core, test_skiplist_init_destroy);
    suite_add_tcase(s, tc_core);
    tc_inserts = tcase_create("Inserts");
    tcase_add_checked_fixture(tc_inserts, setup_inserts, teardown_inserts);
    tcase_add_test(tc_inserts, test_skiplist_insert_one);
    tcase_add_test(tc_inserts, test_skiplist_insert_two);
    tcase_add_test(tc_inserts, test_skiplist_insert_ten);
    suite_add_tcase(s, tc_inserts);
    tc_pred = tcase_create("Pred");
    tcase_add_checked_fixture(tc_pred, setup_pred, teardown_pred);
    tcase_add_test(tc_pred, test_skiplist_pred_empty);
    tcase_add_test(tc_pred, test_skiplist_pred_before_first);
    tcase_add_test(tc_pred, test_skiplist_pred_first);
    tcase_add_test(tc_pred, test_skiplist_pred_last);
    tcase_add_test(tc_pred, test_skiplist_pred_after_last);
    suite_add_tcase(s, tc_pred);
    tc_remove = tcase_create("Remove");
    tcase_add_checked_fixture(tc_remove, setup_remove, teardown_remove);
    tcase_add_test(tc_remove, test_skiplist_remove_nonexistent);
    tcase_add_test(tc_remove, test_skiplist_remove_first);
    tcase_add_test(tc_remove, test_skiplist_remove_last);
    tcase_add_test(tc_remove, test_skiplist_remove_middle);
    tcase_add_test(tc_remove, test_skiplist_remove_all);
    suite_add_tcase(s, tc_remove);
    tc_iter = tcase_create("Iter");
    tcase_add_checked_fixture(tc_iter, setup_iter, teardown_iter);
    tcase_add_test(tc_iter, test_skiplist_iter_empty);
    tcase_add_test(tc_iter, test_skiplist_iter_start);
    tcase_add_test(tc_iter, test_skiplist_iter_middle);
    tcase_add_test(tc_iter, test_skiplist_iter_end);
    suite_add_tcase(s, tc_iter);
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

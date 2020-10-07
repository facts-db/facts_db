#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <math.h>

typedef struct skiplist_node {
        void *value;
        unsigned long height;
} s_skiplist_node;

s_skiplist_node * new_skiplist_node (void *value, unsigned long height);
#define               skiplist_node_links(n) \
        ((s_skiplist_node**) (((s_skiplist_node*) n) + 1))
#define               skiplist_node_next(n, height) (skiplist_node_links(n)[height])
void                  skiplist_node_insert (s_skiplist_node *n,
                                            s_skiplist_node *pred);

typedef struct skiplist {
        s_skiplist_node *head;
        int (*compare) (void *value1, void *value2);
        unsigned long length;
        unsigned long max_height;
} s_skiplist;

#define skiplist_height_table(sl) ((long*) (((s_skiplist*) sl) + 1))
#define skiplistp(sl) ((sl) && (sl)->type == FORM_SKIPLIST)

void              skiplist_init (s_skiplist *sl, int max_height,
                                 double spacing);
s_skiplist *  new_skiplist (int max_height, double spacing);
int               skiplist_compare_ptr (void *a, void *b);
unsigned          skiplist_random_height (s_skiplist *sl);
s_skiplist_node * skiplist_pred (s_skiplist *sl, void *value);
s_skiplist_node * skiplist_insert (s_skiplist *sl, void *value);
void *            skiplist_delete (s_skiplist *sl, void *value);
s_skiplist_node * skiplist_find (s_skiplist *sl, void *value);

#endif

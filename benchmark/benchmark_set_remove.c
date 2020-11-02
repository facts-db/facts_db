
#include <stdio.h>
#include <stdlib.h>
#include "../set.h"

#define ITERATIONS (1000 * 1000)

int main (int argc, char **argv)
{
        long i;
        long *l = malloc((ITERATIONS + 10) * sizeof(long));
        s_set set;
        (void) argc;
        (void) argv;
        printf("set_init(%li)\n", (long) ITERATIONS);
        set_init(&set, ITERATIONS);
        printf("benchmarking %li times set_add(10 * sizeof(long))\n",
               (long) ITERATIONS);
        for (i = 0; i < 10; i++)
                l[i] = i;
        for (i = 0; i < ITERATIONS; i++) {
                l[i + 10] = i + 10;
                set_add(&set, l + i, 10 * sizeof(long));
        }
        printf("benchmarking %li times set_remove\n",
               (long) ITERATIONS);
        for (i = 0; i < ITERATIONS; i++)
                set_remove(&set, set_get(&set, l + i,
                                         10 * sizeof(long)));
        set_destroy(&set);
}

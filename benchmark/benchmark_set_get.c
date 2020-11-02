
#include <stdio.h>
#include <stdlib.h>
#include "../set.h"

#define ITERATIONS (1000 * 1000)

int main (int argc, char **argv)
{
        long i;
        long *l = malloc(ITERATIONS * sizeof(long));
        s_set set;
        (void) argc;
        (void) argv;
        printf("set_init(%li)\n", (long) ITERATIONS);
        set_init(&set, ITERATIONS);
        printf("benchmarking %li times set_add(sizeof(long))\n",
               (long) ITERATIONS);
        for (i = 0; i < ITERATIONS; i++) {
                l[i] = i;
                set_add(&set, l + i, sizeof(long));
        }
        printf("benchmarking %li times set_get(sizeof(long))\n",
               (long) ITERATIONS);
        for (i = 0; i < ITERATIONS; i++)
                set_get(&set, l + i, sizeof(long));
        set_destroy(&set);
}

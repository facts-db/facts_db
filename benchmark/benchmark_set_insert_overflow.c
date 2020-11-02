
#include <stdio.h>
#include <stdlib.h>
#include "../set.h"

#define ITERATIONS (1000 * 1000)

int main (int argc, char **argv)
{
        long i = 0;
        long *l = malloc(ITERATIONS * sizeof(long));
        s_set set;
        (void) argc;
        (void) argv;
        printf("set_init(%li)\n", (long) (ITERATIONS / 2));
        set_init(&set, ITERATIONS / 2);
        printf("benchmarking %li times set_add(sizeof(long))\n",
               (long) ITERATIONS);
        while (i < ITERATIONS) {
                l[i] = i;
                set_add(&set, l + i, sizeof(long));
                i++;
        }
        set_destroy(&set);
}

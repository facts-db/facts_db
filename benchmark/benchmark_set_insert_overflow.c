
#include <stdio.h>
#include <stdlib.h>
#include "../set.h"

#define ITERATIONS (1000 * 1000)

int main (int argc, char **argv)
{
        long i = 0;
        long *l = malloc((ITERATIONS + 10) * sizeof(long));
        s_set set;
        (void) argc;
        (void) argv;
        printf("set_init(%li)\n", (long) (ITERATIONS / 2));
        set_init(&set, ITERATIONS / 2);
        printf("benchmarking %li times set_add(10 * sizeof(long))\n",
               (long) ITERATIONS);
        for (i = 0; i < 10; i++)
                l[i] = i;
        while (i < ITERATIONS) {
                l[i + 10] = i + 10;
                set_add(&set, l + i, 10 * sizeof(long));
                i++;
        }
        set_destroy(&set);
}

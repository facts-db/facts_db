
#include <stdio.h>
#include <stdlib.h>
#include "../facts.h"

#define ITERATIONS (1000 * 2)

int main (int argc, char **argv)
{
        long i;
        s_facts facts;
        (void) argc;
        (void) argv;
        printf("facts_init(%li)\n", (long) ITERATIONS * 4);
        facts_init(&facts, NULL, ITERATIONS * 4);
        printf("benchmarking %li times facts_add({\n"
               "  \"?movie\", \"is a\", \"movie\",\n"
               "    \"actor\", \"?actor\", NULL,\n"
               "  \"?actor\", \"is a\", \"actor\",\n"
               "    \"value\", \"1000\", NULL, NULL})\n",
               (long) ITERATIONS);
        for (i = 0; i < ITERATIONS; i++) {
                facts_add(&facts, (const char *[]) {
                                "?movie", "is a", "movie",
                                "actor", "?actor", NULL,
                                "?actor", "is a", "actor",
                                "value", "1000", NULL, NULL});
        }
        facts_destroy(&facts);
}

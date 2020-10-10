
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "set.h"

s_set g_s;
long g_count = 1000 * 20;

void setup_insert ()
{
  set_init(&g_s);
  mkdir("fixtures", 511);
}

void teardown_insert ()
{
  set_clear(&g_s);
}

int benchmark_set_insert (void)
{
  long i = 0;
  long *l = malloc(sizeof(long) * g_count);
  setup_insert();
  while (i < g_count) {
    l[i] = i;
    if (!set_insert(&g_s, &l[i], sizeof(long)))
      return 1;
    if (g_s.size != i + 1)
      return 1;
    i++;
  }
  teardown_insert();
  free(l);
  return 0;
}

int benchmark_set_insert2 (void)
{
  long i = 0;
  long *l = malloc(sizeof(long) * g_count);
  setup_insert();
  while (i < g_count) {
    l[i] = i;
    if (!set_insert(&g_s, &l[i], sizeof(long)))
      return 1;
    if (g_s.size != i + 1)
      return 1;
    if (!set_insert(&g_s, &l[i], sizeof(long)))
      return 1;
    if (g_s.size != i + 1)
      return 1;
    i++;
  }
  teardown_insert();
  free(l);
  return 0;
}

int main (int argc, char *argv[])
{
  if (argc == 2) {
    if (!strcmp("insert", argv[1]))
      return benchmark_set_insert();
    else if (!strcmp("insert2", argv[1]))
      return benchmark_set_insert2();
    else
      printf("command not found\n");
  }
  else
    printf("usage: %s (insert|insert2)\n", argv[0]);
  return 1;
}

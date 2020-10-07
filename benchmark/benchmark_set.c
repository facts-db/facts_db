
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include "set.h"

s_set g_s;
long g_count = 1000;

void setup ()
{
  bzero(&g_s, sizeof(s_set));
  mkdir("fixtures", 511);
}

void teardown ()
{
  bzero(&g_s, sizeof(s_set));
}

int benchmark_set_create (void)
{
  long i = g_count;
  setup();
  while (i--) {
    unlink("fixtures/create.set");
    unlink("fixtures/create.set.index");
    if (set_open(&g_s, "fixtures/create.set"))
      return 1;
    set_close(&g_s);
  }
  teardown();
  return 0;
}

int benchmark_set_append (void)
{
  long i = 0;
  setup();
  unlink("fixtures/append.set");
  unlink("fixtures/append.set.index");
  if (set_open(&g_s, "fixtures/append.set") != 0)
    return 1;
  while (i < g_count) {
    if (set_append(&g_s, &i, sizeof(i)) != i)
      return 1;
    if (g_s.size != i + 1)
      return 1;
    i++;
  }
  set_close(&g_s);
  teardown();
  return 0;
}

int benchmark_set_append2 (void)
{
  long i = 0;
  setup();
  unlink("fixtures/append2.set");
  unlink("fixtures/append2.set.index");
  if (set_open(&g_s, "fixtures/append2.set") != 0)
    return 1;
  while (i < g_count) {
    if (set_append(&g_s, &i, sizeof(i)) != i)
      return 1;
    if (g_s.size != i + 1)
      return 1;
    if (set_append(&g_s, &i, sizeof(i)) != i)
      return 1;
    if (g_s.size != i + 1)
      return 1;
    i++;
  }
  set_close(&g_s);
  teardown();
  return 0;
}

int main (int argc, char *argv[])
{
  if (argc == 2) {
    if (!strcmp("create", argv[1]))
      return benchmark_set_create();
    else if (!strcmp("append", argv[1]))
      return benchmark_set_append();
    else if (!strcmp("append2", argv[1]))
      return benchmark_set_append2();
    else
      printf("command not found\n");
  }
  else
    printf("usage: %s (create|append|append2)\n", argv[0]);
  return 1;
}

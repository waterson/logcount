#include <stdio.h>
#include "logcount.h"

int
main(int argc, char *argv[])
{
  struct logcount lc;
  logcount_init(&lc, 63);
  logcount_add(&lc, "foo", 3);
  logcount_add(&lc, "bar", 3);
  printf("%d\n", logcount_value(&lc));
  logcount_finish(&lc);
  return 0;
}

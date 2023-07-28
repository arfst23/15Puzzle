//******************************************************************************

#include <stdio.h>
#include <assert.h>

#include "puzzle.h"

//******************************************************************************

void check(const char *str,
  Key k8h, Key k7h, Key k8v, Key k7v,
  Key b8h, Key b7h, Key b8v, Key b7v)
{
  Position positions[LENGTH];
  str2pos(str, positions);

//   trace(positions);
//   trace2(positions);

  Key key8hor = pos2key8hor(positions);
  assert(key8hor == k8h);

  Key key7hor = pos2key7hor(positions);
  assert(key7hor == k7h);

  Key key8ver = pos2key8ver(positions);
  assert(key8ver == k8v);

  Key key7ver = pos2key7ver(positions);
  assert(key7ver == k7v);

  Key blank8hor = pos2blank8hor(positions);
  assert(blank8hor == b8h);

  Key blank7hor = pos2blank7hor(positions);
  assert(blank7hor == b7h);

  Key blank8ver = pos2blank8ver(positions);
  assert(blank8ver == b8v);

  Key blank7ver = pos2blank7ver(positions);
  assert(blank7ver == b7v);
}

//******************************************************************************

int main(int ac, char *av[])
{
  // 01 02 03 04
  // 05 06 07 08
  // 09 10 11 12
  // 13 14 15 --
  {
    const char *str = "01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 --";
    check(str, 0, 0, 0, 0, 7, 8, 7, 8);
  }

  // -- 15 14 13
  // 12 11 10 09
  // 08 07 06 05
  // 04 03 02 01
  {
    const char *str = "-- 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01";
    check(str, SIZE8 - 1, SIZE7 - 1, SIZE8 - 1, SIZE7 - 1, 0, 0, 0, 0); 
  }

  // -- 11 09 13
  // 12 15 10 14
  // 03 07 06 02
  // 04 08 05 01
  {
    const char *str = "-- 11 09 13 12 15 10 14 03 07 06 02 04 08 05 01";
    check(str, 511635860, 39327859, 511635860, 39363609, 0, 0, 0, 0);
  }

  // -- 15 09 13
  // 11 12 10 14
  // 03 07 06 02
  // 04 08 05 01
  {
    const char *str = "-- 15 09 13 11 12 10 14 03 07 06 02 04 08 05 01";
    check(str, 511635860, 39363609, 511635860, 39327859, 0, 0, 0, 0);
  }

  // 07 06 04 02
  // 14 10 03 11
  // 15 -- 12 01
  // 13 08 05 09
  {
    const char *str = "07 06 04 02 14 10 03 11 15 -- 12 01 13 08 05 09";
    check(str, 364048837, 28334220, 479890918, 5363260, 4, 5, 2, 4);
  }

  // 10 08 12 04
  // 06 07 -- 14
  // 13 09 15 02
  // 05 11 01 03
  {
    const char *str = "10 08 12 04 06 07 -- 14 13 09 15 02 05 11 01 03";
    check(str, 479890918, 5363260, 364048837, 28334220, 2, 4, 4, 5);
  }

  printf("%s: ok\n", *av);
  return 0;
}

//******************************************************************************

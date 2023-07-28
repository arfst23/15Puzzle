//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "puzzle.h"

// moves: 0=right, 1=down 2=left, 3=up

const Position posmove2pos[LENGTH][MOVES] =
{
  { 1, 4, NIL, NIL },
  { 2, 5, 0, NIL },
  { 3, 6, 1, NIL },
  { NIL, 7, 2, NIL },
  { 5, 8, NIL, 0 },
  { 6, 9, 4, 1 },
  { 7, 10, 5, 2 },
  { NIL, 11, 6, 3 },
  { 9, 12, NIL, 4 },
  { 10, 13, 8, 5 },
  { 11, 14, 9, 6 },
  { NIL, 15, 10, 7 },
  { 13, NIL, NIL, 8 },
  { 14, NIL, 12, 9 },
  { 15, NIL, 13, 10 },
  { NIL, NIL, 14, 11 },
};

const Move move2reverse[MOVES] = { 2, 3, 0, 1 };

const char move2char[MOVES + 1] = "RDLU";

static const unsigned char perm[] =
{
  0,  4,  8, 12,
  1,  5,  9, 13,
  2,  6, 10, 14,
  3,  7, 11, 15
};

//******************************************************************************

void str2pos(const char *str, Position *positions)
{
  assert(str[STRLEN - 1] == '\0' || str[STRLEN - 1] == '\n');

  memset(positions, NIL, LENGTH);

  for (Position pos = 0; pos < LENGTH; pos++)
  {
    if (str[3 * pos] == '-' && str[3 * pos + 1] == '-')
    {
      assert(positions[LENGTH - 1] == NIL);
      positions[LENGTH - 1] = pos;
    }
    else if (isdigit(str[3 * pos]) && isdigit(str[3 * pos + 1]))
    {
      Value val = 10 * (str[3 * pos] - '0') + (str[3 * pos + 1] - '0');
      assert(val < LENGTH);
      assert(positions[val - 1] == NIL);
      positions[val - 1] = pos;
    }
    else
      assert(0);
  }
}

//******************************************************************************

#if 0
void trace(const Position *positions)
{
  Value vals[LENGTH];
  memset(vals, NIL, LENGTH);
  for (Value val = 0; val < LENGTH; val++)
  {
    assert(vals[positions[val]] == NIL);
    vals[positions[val]] = val + 1;
  }

  for (int row = 0, pos = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++, pos++)
      if (vals[pos] < LENGTH)
	printf("%02d ", vals[pos]);
      else
	printf("-- ");
    printf("\n");
  }
  printf("\n");
}

void tracePerm(const Position *positions)
{
  Value vals[LENGTH];
  memset(vals, NIL, LENGTH);
  for (Value val = 0; val < LENGTH; val++)
  {
    Position pos = perm[positions[perm[val]]];
    assert(vals[pos] == 0);
    vals[pos] = val + 1;
  }

  for (int row = 0, pos = 0; row < 4; row++)
  {
    for (int col = 0; col < 4; col++, pos++)
      if (vals[pos] < LENGTH)
	printf("%02d ", vals[pos]);
      else
	printf("-- ");
    printf("\n");
  }
  printf("\n");
}
#endif

//******************************************************************************

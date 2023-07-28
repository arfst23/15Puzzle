//******************************************************************************

#include <string.h>
#include <assert.h>

#include "puzzle.h"

static const unsigned char perm[] =
{
  0,  4,  8, 12,
  1,  5,  9, 13,
  2,  6, 10, 14,
  3,  7, 11, 15
};

//******************************************************************************

Key pos2key8hor(const Position *positions)
{
  Key key = 0;
  for (Value val = 0; val < 8; val++)
  {
    Position cnt = positions[val];
    for (Value v = 0; v < val; v++)
      if (positions[v] < positions[val])
	cnt--;

    key *= LENGTH - val;
    key += cnt;
  }
  assert(key >= 0);
  assert(key < SIZE8);
  return key;
}

Key pos2key7hor(const Position *positions)
{
  Key key = 0;
  for (Value val = 8; val < 8 + 7; val++)
  {
    Position pos = positions[val] < 8
      ? positions[val] + 8 : positions[val] - 8;
    Position cnt = pos;
    for (Value v = 8; v < val; v++)
    {
      Position p = positions[v] < 8
	? positions[v] + 8 : positions[v] - 8;
      if (p < pos)
	cnt--;
    }

    key *= LENGTH - (val - 8);
    key += cnt;
  }
  assert(key >= 0);
  assert(key < SIZE7);
  return key;
}

Key pos2key8ver(const Position *positions)
{
  Key key = 0;
  for (Value val = 0; val < 8; val++)
  {
    Position cnt = perm[positions[perm[val]]];
    for (Value v = 0; v < val; v++)
      if (perm[positions[perm[v]]] < perm[positions[perm[val]]])
	cnt--;

    key *= LENGTH - val;
    key += cnt;
  }
  assert(key >= 0);
  assert(key < SIZE8);
  return key;  
}

Key pos2key7ver(const Position *positions)
{
  Key key = 0;
  for (Value val = 8; val < 8 + 7; val++)
  {
    Position pos = perm[positions[perm[val]]] < 8
      ? perm[positions[perm[val]]] + 8 : perm[positions[perm[val]]] - 8;
    Position cnt = pos;
    for (Value v = 8; v < val; v++)
    {
      Position p = perm[positions[perm[v]]] < 8
	? perm[positions[perm[v]]] + 8 : perm[positions[perm[v]]] - 8;
      if (p < pos)
	cnt--;
    }

    key *= LENGTH - (val - 8);
    key += cnt;
  }
  assert(key >= 0);
  assert(key < SIZE7);
  return key;
 
}

//******************************************************************************

Key pos2blank8hor(const Position *positions)
{
  Position blank = positions[LENGTH - 1];
  Key cnt = 0;
  for (Value val = 8; val < 8 + 7; val++)
    if (positions[val] < blank)
      cnt++;
  return cnt;
}

Key pos2blank7hor(const Position *positions)
{
  Position blank = positions[LENGTH - 1];
  Key cnt = 0;
  for (Value val = 0; val < 8; val++)
    if (positions[val] < blank)
      cnt++;
  return cnt;
}

Key pos2blank8ver(const Position *positions)
{
  Position blank = perm[positions[perm[LENGTH - 1]]];
  Key cnt = 0;
  for (Value val = 8; val < 8 + 7; val++)
    if (perm[positions[perm[val]]] < blank)
      cnt++;
  return cnt;
}

Key pos2blank7ver(const Position *positions)
{
  Position blank = perm[positions[perm[LENGTH - 1]]];
  Key cnt = 0;
  for (Value val = 0; val < 8; val++)
    if (perm[positions[perm[val]]] < blank)
      cnt++;
  return cnt;
}

//******************************************************************************

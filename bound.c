//******************************************************************************

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "puzzle.h"

extern const Count bound8[SIZE8];
extern const Reference refer8[SIZE8];
extern const Count diff8[DIFF8][8];

extern const Count bound7[SIZE7];
extern const Reference refer7[SIZE7];
extern const Count diff7[DIFF7][9];

//******************************************************************************

Count bound(const Position *positions, Count max)
{
  // trace(positions);

  Key key8hor = pos2key8hor(positions);
  Key key7hor = pos2key7hor(positions);

  Count lim8hor = bound8[key8hor];
  Count lim7hor = bound7[key7hor];
  Count limhor = lim8hor + lim7hor;
  if (limhor >= max)
    return NIL;

  Reference ref8hor = refer8[key8hor];
  if (ref8hor)
  {
    Count blank8hor = pos2blank8hor(positions);
    limhor += diff8[ref8hor][blank8hor];
  }
  Reference ref7hor = refer7[key7hor];
  if (ref7hor)
  {
    Count blank7hor = pos2blank7hor(positions);
    limhor += diff7[ref7hor][blank7hor];
  }
  if (limhor >= max)
    return NIL;

  // trace2(positions);

  Key key8ver = pos2key8ver(positions);
  Key key7ver = pos2key7ver(positions);

  Count lim8ver = bound8[key8ver];
  Count lim7ver = bound7[key7ver];
  Count limver = lim8ver + lim7ver;
  if (limver >= max)
    return NIL;

  Reference ref8ver = refer8[key8ver];
  if (ref8ver)
  {
    Count blank8ver = pos2blank8ver(positions);
    limver += diff8[ref8ver][blank8ver];
  }
  Reference ref7ver = refer7[key7ver];
  if (ref7ver)
  {
    Count blank7ver = pos2blank7ver(positions);
    limver += diff7[ref7ver][blank7ver];
  }
  if (limver >= max)
    return NIL;

  return limhor > limver ? limhor : limver;
}

//******************************************************************************

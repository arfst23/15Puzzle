//******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "puzzle.h"

//******************************************************************************

typedef struct
{
  Position positions[LENGTH];
  Count cnt;
  Count bound;
  Move move;
  void *next, *prev;
} Node;

#define NODES 84931641

static Node *nodes = NULL;

Node* get()
{
  assert(nodes);
  
  Node *node = nodes;
  nodes = node->next;
  memset(node, 0, sizeof(Node));

  return node;
}

void put(Node *node)
{
  node->next = nodes;
  nodes = node;
}

//******************************************************************************

//          total         prev
Node *queue[MAXMOVES + 1][MAXMOVES + 1];
Count minbound = NIL;
Count mincount = NIL;

void push(Node *node)
{
  Count bound = node->bound + node->cnt;
  node->next = queue[bound][node->cnt];
  queue[bound][node->cnt] = node;
  if (bound < minbound)
    minbound = bound;
  if (bound == minbound && node->cnt < mincount)
    mincount = node->cnt;
}

Node* pop()
{
  for (;;)
  {
    if (queue[minbound][mincount])
    {
      Node *node = queue[minbound][mincount];
      queue[minbound][mincount] = node->next;
      return node;
    }

    mincount++;
    if (mincount > MAXMOVES)
    {
      minbound += 2;
      assert(minbound <= MAXMOVES);
      mincount = 0;
    }
  }
}

//******************************************************************************

const char* solve(const char *str)
{
  {
    static Node n[NODES];
    nodes = n;

    for (Index i = 0; i < NODES - 1; i++)
      nodes[i].next = nodes + i + 1; 
  }

  memset(queue, 0, sizeof(queue));
  minbound = mincount = NIL;

  char *moves;
  {
    static char str[MAXMOVES + 1];
    moves = str + MAXMOVES + 1;
    *moves = '\0';
  }

  {
    Node *root = get();
    str2pos(str, root->positions);
    root->bound = bound(root->positions, MAXMOVES);
    if (root->bound == 0)
      return moves;
    push(root);
  }
  
  Node *next;
  for (;;)
  {
    Node *node = pop();

    // printf("bound=%d count=%d %d\n", minbound - mincount, mincount, minbound);
    // trace(node->positions);
    
    Position blank = node->positions[15];
    for (Move move = 0; move < MOVES; move++)
    {
      if (node->prev && move == move2reverse[node->move])
	continue;
      Position pos = posmove2pos[blank][move];
      if (pos == NIL)
	continue;

      next = get();

      for (Value val = 0; val < LENGTH - 1; val++)
	if (node->positions[val] == pos)
	  next->positions[val] = blank;
	else
	  next->positions[val] = node->positions[val];
      next->positions[LENGTH - 1] = pos;

      // trace(next->positions);

      next->cnt = node->cnt + 1;
      next->move = move;
      next->prev = node;

      Count bnd = bound(next->positions, MAXMOVES - node->cnt);
      if (bnd == NIL)
      {
	put(next);
	continue;
      }
      if (bnd == 0)
	goto DONE;

      next->bound = bnd;
      push(next);
    }
  }

DONE:
  while (next->prev)
  {
    moves--;
    *moves = move2char[next->move];
    next = next->prev;
  }
  return moves;
}

//******************************************************************************

int main(int ac, char *av[])
{
  assert(ac <= 2);

  if (ac == 2)
  {
    assert(strlen(av[1]) == 3 * LENGTH - 1);
    const char *moves = solve(av[1]);
    printf("%s %s\n", av[1], moves);
  }
  else
  {
    char str[3 * LENGTH];
    while (fread(str, 1, 3 * LENGTH, stdin) == 3 * LENGTH)
    {
      str[3 * LENGTH - 1] = '\0';
      const char *moves = solve(str);
      printf("%s %s\n", str, moves);
    }
  }

  return 0;
}

//******************************************************************************

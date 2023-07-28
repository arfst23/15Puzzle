//******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "puzzle.h"

extern const Count diff7[DIFF7][9];
typedef uint16_t Flags;

#define VERBOSE 0

//******************************************************************************

typedef struct
{
  Position positions[15];
  Position blank;
  Count cnt;
  void *next;
} Node;

#define NODES 18970094L

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

static Node *head = NULL;
static Node *tail = NULL;

void enqueue(Node *node)
{
  assert(node);
  node->next = NULL;

  if (head == NULL)
  {
    assert(tail == NULL);
    head = tail = node;
  }
  else
  {
    assert(tail != NULL);
    tail->next = node;
    tail = node;
  }
}

Node* dequeue()
{
  assert(head);
  assert(tail);
  if (head == tail)
  {
    assert(head->next == NULL);
    Node *node = head;
    head = tail = NULL;
    return node;
  }
  else
  {
    assert(head->next != NULL);
    Node *node = head;
    head = head->next;
    return node;
  }
}

//******************************************************************************

void positions2values(const Position *positions, Position blank, Value *values)
{
  memset(values, 0, LENGTH);
  for (Value val = 8; val < 15; val++)
    values[positions[val]] = val + 1;
  assert(values[blank] == 0);

  Count len = 1;
  values[blank] = NIL;

  Position queue[LENGTH];
  memset(queue, 0, LENGTH);
  queue[blank] = 1;

  while (len)
    for (Position src = 0; src < LENGTH; src++)
      if (queue[src])
      {
	for (Move move = 0; move < MOVES; move++)
	{
	  Position dst = posmove2pos[src][move];
	  if (dst == NIL || values[dst])
	    continue;

	  values[dst] = NIL;
	  queue[dst] = 1;
	  len++;
	}

	queue[src] = 0;
	len--;
      }
  assert(values[blank] == NIL);
}

#if VERBOSE
void board2print(Value *values)
{
  for (int r = 0, i = 0; r < 4; r++)
  {
    for (int c = 0; c < 4; c++, i++)
      if (values[i] == 0)
	printf("-- ");
      else if (values[i] == NIL)
	printf("== ");
      else
	printf("%02d ", values[i]);
    printf("\n");
  }
  printf("\n");
}
#endif

//******************************************************************************

int main()
{
  {
    static Node n[NODES];
    nodes = n;

    for (Index i = 0; i < NODES - 1; i++)
      nodes[i].next = nodes + i + 1;
  }

  static Count table[SIZE7][9];
  memset(table, NIL, (size_t)SIZE7 * (size_t)9);
  table[0][9 - 1] = 0;

  {
    Node *node = get();
    for (Position pos = 8; pos < 15; pos++)
      node->positions[pos] = pos;
    node->blank = LENGTH - 1;
    enqueue(node);
  }

  static Flags done[SIZE7];
  memset(done, 0, SIZE7 * sizeof(Flags));
  done[0] = 1 << (LENGTH - 1);

  int cnt = SIZE7 - 1;
  while (head)
  {
    fprintf(stderr, "> %d     \r", cnt);

    Node *node = dequeue();

    Value values[LENGTH];
    positions2values(node->positions, node->blank, values);

#if VERBOSE
    printf("=====================\n\n");
    printf("source cnt=%d\n", node->cnt);
    board2print(values);
#endif

    for (Value val = 8; val < 15; val++)
    {
      Position src = node->positions[val];
      for (Move move = 0; move < MOVES; move++)
      {
	Position dst = posmove2pos[src][move];
	if (dst == NIL || values[dst] != NIL)
	  continue;

#if VERBOSE
	static char d[] = "rdlu";
	printf("move %d %c\n", val + 1, d[move]);
#endif

	Node *next = get();
	memcpy(next, node, sizeof(Node));
	next->positions[val] = dst;
	next->cnt++;
	next->blank = src;

	Key key = pos2key7hor(next->positions);

	if (done[key] & (1 << next->blank))
	{
#if VERBOSE
	  printf("XXX\n\n");
#endif
	  put(next);
	  continue;
	}

	if (!done[key])
	  cnt--;

	Value values[LENGTH];
	positions2values(next->positions, next->blank, values);

#if VERBOSE
	printf("target cnt=%d\n", next->cnt);
	board2print(values);
#endif

	enqueue(next);

#if VERBOSE
	if (done[key])
	{
	  printf("already seen");
	  for (int j = 0; j < 9; j++)
	    if (table[key][j] != NIL)
	      printf(" %d", j);
	  printf("\n");
	}
#endif
	Count cnt = 0;
	for (Position pos = 0; pos < LENGTH; pos++)
	{
	  if (values[pos] == NIL)
	  {
	    done[key] |= 1 << pos;
	    assert(table[key][cnt] == NIL);
#if VERBOSE
	    printf("%d ", cnt);
#endif
	    table[key][cnt] = next->cnt;
	    cnt++;
	  }
	  else if (values[pos] == 0)
	    cnt++;
	}
	assert(cnt == 9);

#if VERBOSE
 	printf("\n\n");
#endif
      }
    }

    put(node);
  }

  printf("#include \"puzzle.h\"\n\n");

  printf("const Count bound7[%d] =\n", SIZE7);
  printf("{\n");
  for (Index i = 0; i < SIZE7; i++)
  {
    Count min = NIL;
    for (Count cnt = 0; cnt < 9; cnt++)
      if (table[i][cnt] < min)
	min = table[i][cnt];
    printf("  %2d, // %d\n", min, i);
  }
  printf("};\n\n");

  printf("const Reference refer7[%d] =\n", SIZE7);
  printf("{\n");
  for (Index i = 0; i < SIZE7; i++)
  {
    Count min = NIL;
    for (Count cnt = 0; cnt < 9; cnt++)
      if (table[i][cnt] < min)
	min = table[i][cnt];

    Count diff[9];
    for (Count cnt = 0; cnt < 9; cnt++)
      diff[cnt] = table[i][cnt] - min;

    Reference ref;
    for (ref = 0; ref < DIFF7; ref++)
      if (diff[0] == diff7[ref][0]
	&& diff[1] == diff7[ref][1]
	&& diff[2] == diff7[ref][2]
	&& diff[3] == diff7[ref][3]
	&& diff[4] == diff7[ref][4]
	&& diff[5] == diff7[ref][5]
	&& diff[6] == diff7[ref][6]
	&& diff[7] == diff7[ref][7]
	&& diff[8] == diff7[ref][8])
	break;
    assert(ref < DIFF7);

    printf("  %4d, // %d\n", ref, i);
  }
  printf("};\n");

  fprintf(stderr, "generated\n");
  return 0;
}

//******************************************************************************

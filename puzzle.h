//******************************************************************************

#include <stdint.h>

#define LENGTH 16
#define STRLEN (3 * LENGTH)
#define MOVES 4
#define NIL 255
#define MAXMOVES 80

#define DEPTH 25
#define TREES 79070945

#define SIZE8 (16 * 15 * 14 * 13 * 12 * 11 * 10 * 9)
#define SIZE7 (16 * 15 * 14 * 13 * 12 * 11 * 10)

#define DIFF7 4444
#define DIFF8 7842

typedef uint8_t Position;
typedef uint8_t Value;
typedef uint8_t Count;
typedef uint8_t Move;
typedef uint16_t Reference;
typedef uint32_t Key;
typedef uint32_t Index;
typedef uint64_t Hash;

extern const Position posmove2pos[LENGTH][MOVES];
extern const Move move2reverse[MOVES];
extern const char move2char[MOVES + 1];

//******************************************************************************

void trace(const Position *positions);
void tracePerm(const Position *positions);

void str2pos(const char *str, Position *positions);

Key pos2key8hor(const Position *positions);
Key pos2key7hor(const Position *positions);
Key pos2key8ver(const Position *positions);
Key pos2key7ver(const Position *positions);

Key pos2blank8hor(const Position *position);
Key pos2blank7hor(const Position *position);
Key pos2blank8ver(const Position *position);
Key pos2blank7ver(const Position *position);

Count bound(const Position *positions, Count max);

Index find(int key8, int key7);
void reverse(Index idx, char *str);

//******************************************************************************

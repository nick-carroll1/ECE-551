#include <stdlib.h>

#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)

struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};
typedef struct _board_t board_t;

void addRandomMine(board_t * b);

// functions you will write later
board_t * makeBoard(int w, int h, int numMines);
int countMines(board_t * b, int x, int y);
void freeBoard(board_t * b);

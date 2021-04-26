#include <stdlib.h>
#include <stdio.h>
#include <queue>

#define HASH_MAX 4782969					// 3 ^ 14 = 4782969

enum Coin {EMPTY, WHITE, BLACK};

class Board;
class Square;

int make_hash(Coin* array);
void args2array(Coin* array, const char* masu, char* white, char* black);
int c2i(char name);
char i2c(int num);
int checkVisit(Board* focus_tmp, Square sq, char neighbor, int sq_num, \
    int* visit, std::queue<Board> &board_queue);
void printBoard(Board *board);
int bitcheck(Coin* state1, Coin* state2);

typedef struct Board {
  int hash;
  Coin state[14];
  char route[512] = {'\0'};
} Board;

class Square {
	public:
		char name;
		char neighbor_up;
		char neighbor_down;
		char neighbor_left;
		char neighbor_right;

		Square(char name, char n_u, char n_d, char n_l, char n_r) {
			this->name					 = name;
			this->neighbor_up 	 = n_u;
			this->neighbor_down  = n_d;
			this->neighbor_left  = n_l;
			this->neighbor_right = n_r;
		}

		Square() {}
};

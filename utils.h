#include <stdlib.h>
#include <stdio.h>

#define HASH_MAX 4782969					// 3 ^ 14 = 4782969

enum Coin {EMPTY, WHITE, BLACK};

class Board;
class Square;

int make_hash(Coin* array);
void args2array(Coin* array, const char* masu, char* white, char* black);
int c2i(char name);
char i2c(int num);
int checkVisit(Board* focus, Board* focus_tmp, Square sq, char neighbor, int sq_num, int* visit);

class Board {
	public:
		int hash;				// 盤面を一意に表すハッシュ値
		Coin *state;	// 各マスの状態を表す配列
		char move[2];		// 親盤面からどう移動したかを表す文字列
		Board* parent;		// 親盤面

		Board() {
      this->hash   = 0;
      this->state  = (Coin*)malloc(14 * sizeof(Coin));
      // this->move   = (char*)malloc(2 * sizeof(char));
      this->parent = NULL;
    }
		 	 
		Board(int hash, Coin* state, char* move, Board* parent) {
			this->hash	 = hash;
			this->state  = state;
			// this->move   = move;
			this->parent = parent;
		}

		void setHash() {
			this->hash = make_hash(this->state);
		}
};

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

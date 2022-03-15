//===============================================================================
// (C) Copyright 2021 Masatomo Matsuda. All rights reserved.
//===============================================================================

/*
run-cmd : ./main CDEF IJKL IJKL CDEF
				  ./main (初期 白位置) (初期 黒位置) (最終 白位置) (最終 黒位置)
*/

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include "utils.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
  clock_t start, end;

	/* 引数処理 */
	char* white_init  = argv[1];
	char* black_init  = argv[2];
	char* white_final = argv[3];
	char* black_final = argv[4];

	/* 変数宣言 */
	Board focus;			// 処理中の盤面
  Board focus_tmp;
	Coin state_tmp[14];

	int hash_tmp;
	char MASU[14] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
	 							   'H', 'I', 'J', 'K', 'L', 'M', 'N'};
	std::queue<Board> board_queue;
	int* visit;				// 訪れたことのある盤面を表す(1 : visited)
  visit = (int*)calloc(HASH_MAX, sizeof(int));

	/* 各マスのデータ */
	Square sq[14];
  //             name   up   down  left  right
	sq[0]  = Square('A', '\0', '\0', '\0',  'B');
	sq[1]  = Square('B', '\0', '\0',  'A',  'C');
	sq[2]  = Square('C', '\0',  'D',  'B',  'L');
	sq[3]  = Square('D',  'C',	'E', '\0', '\0');
	sq[4]  = Square('E',  'D',	'F', '\0', '\0');
	sq[5]  = Square('F',  'E',	'G', '\0', '\0');
	sq[6]  = Square('G',  'F', '\0', '\0', '\0');
	sq[7]  = Square('H', '\0',  'I', '\0', '\0');
	sq[8]  = Square('I',  'H',  'J', '\0', '\0');
	sq[9]  = Square('J',  'I',  'K', '\0', '\0');
	sq[10] = Square('K',  'J',  'L', '\0', '\0');
	sq[11] = Square('L',  'K', '\0',  'C',  'M');
	sq[12] = Square('M', '\0', '\0',  'L',  'N');
	sq[13] = Square('N', '\0', '\0',  'M', '\0');

	Board init, fin;
	/* FINALの盤面のハッシュ値を計算し, 記憶 */
	args2array(state_tmp, MASU, white_final, black_final);
  memcpy(fin.state, state_tmp, sizeof(Coin) * 14);
	fin.hash = make_hash(state_tmp);

	/* INITの盤面をfocusにセット */
	args2array(state_tmp, MASU, white_init, black_init);
  memcpy(init.state, state_tmp, sizeof(Coin) * 14);
	init.hash = make_hash(state_tmp);
	visit[init.hash] = 1;

	focus = init;

  int queue_size = 0;
  start = clock();
	/* FINALの盤面を探索するループ */
	while(1) {
    /* FINAL盤面にたどり着いたらループを抜ける */
    // ここで, finの move と parent が決まる
    if (focus.hash == fin.hash) {
      std::cout << "found!!" << std::endl;
      break;
    }

		/* 14マス全てに対し, コインがあるかチェックするループ */
    // queue_size = board_queue.size();
    // printf("route : %s\n", focus.route);
		for (int i = 0; i < 14; i++) {

			/* コインがあるマスにおいて, ４方向に対してスペースが有るかチェック */
			if (focus.state[i] != EMPTY) {
				// 隣接マスが存在し, かつそのマスが空いている場合
				if (sq[i].neighbor_up		 != '\0' && focus.state[c2i(sq[i].neighbor_up)] == EMPTY) {
					// 遷移先盤面のハッシュ値をindexとする visit[] が 0であるかチェック
          memcpy(&focus_tmp, &focus, sizeof(Board));
          checkVisit(&focus_tmp, sq[i], sq[i].neighbor_up, i, visit, board_queue);
        }
        if (sq[i].neighbor_down  != '\0' && focus.state[c2i(sq[i].neighbor_down)] == EMPTY) {
          memcpy(&focus_tmp, &focus, sizeof(Board));
          checkVisit(&focus_tmp, sq[i], sq[i].neighbor_down, i, visit, board_queue);
        }
        if (sq[i].neighbor_left  != '\0' && focus.state[c2i(sq[i].neighbor_left)] == EMPTY) {
          memcpy(&focus_tmp, &focus, sizeof(Board));
          checkVisit(&focus_tmp, sq[i], sq[i].neighbor_left, i, visit, board_queue);
        }
        if (sq[i].neighbor_right != '\0' && focus.state[c2i(sq[i].neighbor_right)] == EMPTY) {
          memcpy(&focus_tmp, &focus, sizeof(Board));
          checkVisit(&focus_tmp, sq[i], sq[i].neighbor_right, i, visit, board_queue);
        }
      }
    }

    if (board_queue.size() == 0) {
      printf("not found\n");
      return 1;
    }

    /* queue から盤面を取り出し, focusにセット */
    focus = board_queue.front();
    board_queue.pop();

  // } while(!board_queue.empty());
  }
  end = clock();

  /* FINALの盤面までの遷移を出力するループ */
  int j = 0;
  while(1) {
  	if (focus.route[j] != '\0') {
      printf("%02d : %c%c\n", j/2+(j%2)+1, focus.route[j], focus.route[j+1]);
      j += 2;
  	}
  	else { 
  		break;
  	}
  }

  printf("elapsed time : %.3f [sec]\n", (double)(end - start)/CLOCKS_PER_SEC);

  return 0;
}

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

int main(int argc, char* argv[]) {
	/* 引数処理 */
	char* white_init  = argv[1];
	char* black_init  = argv[2];
	char* white_final = argv[3];
	char* black_final = argv[4];

  std::cout << black_final << std::endl;

	Board* focus;			// 処理中の盤面
	Coin state_tmp[14];
	Board focus_tmp = Board(0, state_tmp, (char*)malloc(2 * sizeof(char)), NULL);	// 遷移した盤面

	/* 変数宣言 */
	int hash_tmp;
	char MASU[14] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
	 							   'H', 'I', 'J', 'K', 'L', 'M', 'N'};
  std::cout << "MASU[0] : " << MASU[0] << std::endl;
	std::queue<Board> board_queue;
	int* visit;				// 訪れたことのある盤面を表す(1 : visited)
  visit = (int*)calloc(HASH_MAX, sizeof(int));

	/* 各マスのデータ */
	Square sq[14];
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
	sq[12] = Square('M', '\0', '\0',  'M',  'N');
	sq[13] = Square('N', '\0', '\0',  'N', '\0');

	/* FINALの盤面のハッシュ値を計算し, 記憶 */
  // for (int i = 0; i < 14; i++) {
  //   std::cout << "state_tmp[" << i << "] : " << state_tmp[i] << std::endl;
  // }
	// args2array(state_tmp, MASU, white_final, black_final);
  // for (int i = 0; i < 14; i++) {
  //   std::cout << "state_tmp[" << i << "] : " << state_tmp[i] << std::endl;
  // }
	hash_tmp   = make_hash(state_tmp);
	Board fin  = Board(hash_tmp, state_tmp, NULL, NULL);
	visit[fin.hash] = 1;

	/* INITの盤面をfocusにセット */
	args2array(state_tmp, MASU, white_init, black_init);
	hash_tmp   = make_hash(state_tmp);
  std::cout << "init hash : " << hash_tmp << std::endl;
	Board init = Board(hash_tmp, state_tmp, NULL, NULL);

	focus = &init;

	/* FINALの盤面を探索するループ */
	while(1) {

		/* 14マス全てに対し, コインがあるかチェックするループ */
		for (int i = 0; i < 14; i++) {
      // std::cout << "test " << i << std::endl;
      // std::cout << "init.state[" << i << "] :" << init.state[i] << std::endl;
      // std::cout << "focus.state[" << i << "] :" << focus->state[i] << std::endl;

			/* コインがあるマスにおいて, ４方向に対してスペースが有るかチェック */
			if (focus->state[i] != EMPTY) {
        // std::cout << "hit!!" << std::endl;
				// 隣接マスが存在し, かつそのマスが空いている場合
				if (sq[i].neighbor_up		 != '\0' && focus->state[c2i(sq[i].neighbor_up)] == EMPTY) {
					// 遷移先盤面のハッシュ値をindexとする visit[] が 0であるかチェック
					if (checkVisit(focus, &focus_tmp, sq[i], sq[i].neighbor_up, i, visit) == 0) {
						// visit[] が0である盤面を, queueにプッシュ
						board_queue.push(focus_tmp);
            visit[focus_tmp.hash] = 1;
            printf("hash : %d\n", focus_tmp.hash);
            printf("Board : %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", focus_tmp.state[0], focus_tmp.state[1], focus_tmp.state[2], focus_tmp.state[3],
                                                                             focus_tmp.state[4], focus_tmp.state[5], focus_tmp.state[6], focus_tmp.state[7],
                                                                             focus_tmp.state[8], focus_tmp.state[9], focus_tmp.state[10], focus_tmp.state[11],
                                                                             focus_tmp.state[12], focus_tmp.state[13]);
					}
				}
				if (sq[i].neighbor_down  != '\0' && focus->state[c2i(sq[i].neighbor_down)] == EMPTY) {
					if (checkVisit(focus, &focus_tmp, sq[i], sq[i].neighbor_down, i, visit) == 0) {
						board_queue.push(focus_tmp);
            visit[focus_tmp.hash] = 1;
            printf("hash : %d\n", focus_tmp.hash);
            printf("Board : %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", focus_tmp.state[0], focus_tmp.state[1], focus_tmp.state[2], focus_tmp.state[3],
                                                                             focus_tmp.state[4], focus_tmp.state[5], focus_tmp.state[6], focus_tmp.state[7],
                                                                             focus_tmp.state[8], focus_tmp.state[9], focus_tmp.state[10], focus_tmp.state[11],
                                                                             focus_tmp.state[12], focus_tmp.state[13]);
					}
				}
				if (sq[i].neighbor_left  != '\0' && focus->state[c2i(sq[i].neighbor_left)] == EMPTY) {
					if (checkVisit(focus, &focus_tmp, sq[i], sq[i].neighbor_left, i, visit) == 0) {
						board_queue.push(focus_tmp);
            visit[focus_tmp.hash] = 1;
            printf("hash : %d\n", focus_tmp.hash);
            printf("Board : %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", focus_tmp.state[0], focus_tmp.state[1], focus_tmp.state[2], focus_tmp.state[3],
                                                                             focus_tmp.state[4], focus_tmp.state[5], focus_tmp.state[6], focus_tmp.state[7],
                                                                             focus_tmp.state[8], focus_tmp.state[9], focus_tmp.state[10], focus_tmp.state[11],
                                                                             focus_tmp.state[12], focus_tmp.state[13]);
					}
				}
				if (sq[i].neighbor_right != '\0' && focus->state[c2i(sq[i].neighbor_right)] == EMPTY) {
					if (checkVisit(focus, &focus_tmp, sq[i], sq[i].neighbor_right, i, visit) == 0) {
						board_queue.push(focus_tmp);
            visit[focus_tmp.hash] = 1;
            printf("hash : %d\n", focus_tmp.hash);
            printf("Board : %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", focus_tmp.state[0], focus_tmp.state[1], focus_tmp.state[2], focus_tmp.state[3],
                                                                             focus_tmp.state[4], focus_tmp.state[5], focus_tmp.state[6], focus_tmp.state[7],
                                                                             focus_tmp.state[8], focus_tmp.state[9], focus_tmp.state[10], focus_tmp.state[11],
                                                                             focus_tmp.state[12], focus_tmp.state[13]);
					}
				}
			}
		}
		/* queue から盤面を取り出し, focusにセット */
    // std::cout << "set focus" << std::endl;
		*focus = board_queue.front();
    // std::cout << "seted" << std::endl;
		board_queue.pop();
    // std::cout << "poped" << std::endl;

		/* FINAL盤面にたどり着いたらループを抜ける */
		// ここで, finの move と parent が決まる
		if (focus->hash == fin.hash) {
      std::cout << "found!!" << std::endl;
			fin.parent  = focus;
			fin.move[0] = focus->move[0];
			fin.move[1] = focus->move[1];
			break;
		}
	}

	// /* FINALの盤面を focus にセット */
	// *focus = fin;

	/* FINALの盤面までの遷移を出力するループ */
	// while(1) {

	// 	/* focusノードが親盤面を持つなら親盤面からの遷移を出力. 親盤面がないなら終了 */ 
	// 	if (focus->parent != NULL) {
	// 		std::cout << focus->move << std::endl;

	// 	/* focus に, 親盤面をセット */
	// 		focus = focus->parent;
	// 	}
	// 	else { 
	// 		break;
	// 	}
	// }

	return 0;
}

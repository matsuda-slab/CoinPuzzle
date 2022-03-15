//===============================================================================
// (C) Copyright 2021 Masatomo Matsuda. All rights reserved.
//===============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include "utils.h"
#include <queue>

/* array[14] から ハッシュ値を算出する */
int make_hash(Coin* array) {
  int hash = 0;
  for (int i = 0; i < 14; i++) {
    hash += std::pow(3, i) * array[i];
  }

  return hash;
}

/* 引数の文字列から array[14] を生成する */
void args2array(Coin *array, const char* masu, char* white, char* black) {
  for (int i = 0; i < 14; i++) {
    if      (strchr(white, (int)masu[i]) != NULL)	array[i] = WHITE;
    else if (strchr(black, (int)masu[i]) != NULL) array[i] = BLACK;
    else																			    array[i] = EMPTY;
  }
}

int c2i(char name) {
  switch(name) {
    case 'A': return  0;
    case 'B': return  1;
    case 'C': return  2;
    case 'D': return  3;
    case 'E': return  4;
    case 'F': return  5;
    case 'G': return  6;
    case 'H': return  7;
    case 'I': return  8;
    case 'J': return  9;
    case 'K': return 10;
    case 'L': return 11;
    case 'M': return 12;
    case 'N': return 13;
  }

  return -1;
}

char i2c(int num) {
  switch(num) {
    case  0: return 'A';
    case  1: return 'B';
    case  2: return 'C';
    case  3: return 'D';
    case  4: return 'E';
    case  5: return 'F';
    case  6: return 'G';
    case  7: return 'H';
    case  8: return 'I';
    case  9: return 'J';
    case 10: return 'K';
    case 11: return 'L';
    case 12: return 'M';
    case 13: return 'N';
  }

  return 'Z';
}

int checkVisit(Board* focus_tmp, Square sq, char neighbor, int sq_num, int* visit, std::queue<Board> &board_queue) {
  // 遷移
  int idx;
  char move[3];
  if      (neighbor == sq.neighbor_up)    idx = c2i(sq.neighbor_up);
  else if (neighbor == sq.neighbor_down)  idx = c2i(sq.neighbor_down);
  else if (neighbor == sq.neighbor_left)  idx = c2i(sq.neighbor_left);
  else if (neighbor == sq.neighbor_right) idx = c2i(sq.neighbor_right);

  focus_tmp->state[idx]    = focus_tmp->state[sq_num];
  focus_tmp->state[sq_num] = EMPTY;

  // 遷移先の盤面のハッシュ値を計算 & セット
  focus_tmp->hash = make_hash(focus_tmp->state);

  // 遷移の仕方を記憶
  move[0] = i2c(sq_num);
  move[1] = neighbor;
  move[2] = '\0';

  // 今までのルートに新しい遷移を結合
  strcat(focus_tmp->route, move);
  
  // そのハッシュ値をindexとする visit[] が 0であるかチェック
  if (visit[focus_tmp->hash] == 0) {
    // 現在のfocus_tmpの要素値をqueueにpushする
    board_queue.push(*focus_tmp);
    visit[focus_tmp->hash] = 1;
    return 0;
  }

  return 1;
}

void printBoard(Board *board) {
  printf("Board : %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
      board->state[0], board->state[1], board->state[2], board->state[3],
      board->state[4], board->state[5], board->state[6], board->state[7],
      board->state[8], board->state[9], board->state[10], board->state[11],
      board->state[12], board->state[13]);
}

int bitcheck(Coin* state1, Coin* state2) {
  int cnt = 0;
  for (int i = 0; i < 14; i++) {
    if (state1[i] != state2[i]) cnt++;
  }

  return cnt;
}

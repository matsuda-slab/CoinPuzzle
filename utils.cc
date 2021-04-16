#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include "utils.h"

/* array[14] から ハッシュ値を算出する */
int make_hash(Coin* array) {
  int hash = 0;
  for (int i = 0; i < 14; i++) {
    hash += std::pow(3, i) * array[i];
  }

  return hash;
}

/* マスの状態を array[14] に変換する */
// void masu2array() {
// }

/* 引数の文字列から array[14] を生成する */
void args2array(Coin *array, const char* masu, char* white, char* black) {
  for (int i = 0; i < 14; i++) {
    if (strchr(white, (int)masu[i]) != NULL)			 array[i] = WHITE;
    else if (strchr(black, (int)masu[i]) != NULL)  array[i] = BLACK;
    else																			     array[i] = EMPTY;
  }
}

int c2i(char name) {
  switch(name) {
    case 'A': return 0;
    case 'B': return 1;
    case 'C': return 2;
    case 'D': return 3;
    case 'E': return 4;
    case 'F': return 5;
    case 'G': return 6;
    case 'H': return 7;
    case 'I': return 8;
    case 'J': return 9;
    case 'K': return 10;
    case 'L': return 11;
    case 'M': return 12;
    case 'N': return 13;
  }

  return -1;
}

char i2c(int num) {
  switch(num) {
    case 0:  return 'A';
    case 1:  return 'B';
    case 2:  return 'C';
    case 3:  return 'D';
    case 4:  return 'E';
    case 5:  return 'F';
    case 6:  return 'G';
    case 7:  return 'H';
    case 8:  return 'I';
    case 9:  return 'J';
    case 10: return 'K';
    case 11: return 'L';
    case 12: return 'M';
    case 13: return 'N';
  }

  return 'Z';
}

int checkVisit(Board* focus, Board* focus_tmp, Square sq, char neighbor, int sq_num, int* visit) {
  // 遷移
  focus_tmp = focus;
  int idx;
  if (neighbor == sq.neighbor_up) idx = c2i(sq.neighbor_up);
  else if (neighbor == sq.neighbor_down) idx = c2i(sq.neighbor_down);
  else if (neighbor == sq.neighbor_left) idx = c2i(sq.neighbor_left);
  else if (neighbor == sq.neighbor_right) idx = c2i(sq.neighbor_right);

  focus_tmp->state[idx] = focus_tmp->state[sq_num];
  focus_tmp->state[sq_num] = EMPTY;

  // 遷移先の盤面のハッシュ値を計算 & セット
  focus_tmp->setHash();
  printf("focus_tmp->hash : %d\n", focus_tmp->hash);

  // 親盤面に現在の盤面をセット
  focus_tmp->parent = focus;

  // 遷移の仕方を記憶
  // std::cout << i2c(sq_num) << std::endl;
  focus_tmp->move[0] = i2c(sq_num);
  focus_tmp->move[1] = neighbor;

  // そのハッシュ値をindexとする visit[] が 0であるかチェック
  if (visit[focus_tmp->hash] == 0) return 0;

  return 1;
}


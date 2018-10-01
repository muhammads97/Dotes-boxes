#ifndef COMPUTER_H_INCLUDED
#define COMPUTER_H_INCLUDED
#include "game_play.h"
#include "undo_redo.h"

int filled_check_computer(int n, int m, int p);
int v_filled_boxes_computer(int n, int m, int p);
int h_filled_boxes_computer(int n,int m,int p);
int check_for_winner();
int v_move(int n, int m, int p);
void undo_v_move(int n, int m);
int h_move(int n, int m, int p);
void undo_h_move(int n, int m);
int minimax(int player, int depth, int alpha, int beta);
void computer();
void v_computer_move(int n, int m);
void h_computer_move(int n, int m);


#endif // COMPUTER_H_INCLUDED

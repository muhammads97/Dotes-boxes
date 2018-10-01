#ifndef GAME_OVER_H_INCLUDED
#define GAME_OVER_H_INCLUDED
#include "game_play.h"
#include "main_menu.h"
#define Font_desc "Showcard Gothic Bold 25"


extern GtkWidget *main_menu_button, *exit_button, *label4, *game_over_win, *vbox8;

void g_over_win_init();
void game_over_signals();
void show_main_menu();
void g_over_win_show(const char *name);
void game_over();
int winner_name();

#endif // GAME_OVER_H_INCLUDED

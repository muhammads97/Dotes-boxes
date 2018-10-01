#ifndef MAIN_MENU_H_INCLUDED
#define MAIN_MENU_H_INCLUDED
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include "game_play.h"
#include "load_game.h"

extern char *n1, *n2;
extern int g;
extern int num_of_players;
extern GtkWidget *main_menu;
extern GtkWidget *vbox1,*vbox2,*vbox3,*lala;
extern GtkWidget *label1;
extern GtkWidget *start_game;
extern GtkWidget *load_game;
extern GtkWidget *top_ten,*top_ten_win;
extern GtkWidget *close;
extern GtkWidget *text1,*text2;
extern GtkWidget *hbox1,*hbox2,*hbox3,*hbox4,*start,*back,*label,*label2,*label3;
extern GtkWidget *r1, *r2, *r3, *r4;


void g_size2(GtkWidget *widget, GdkEvent * event);
void g_size5(GtkWidget *widget, GdkEvent * event);
void nplayers2(GtkWidget *widget, GdkEvent * event);
void nplayers1(GtkWidget *widget, GdkEvent * event);
void startg();
void single_player();
void two_player();
void player_name();
void main_menu_win(GtkWidget *window);
void open_start_game();
void open_main_menu();
void close_start_game();
void close_main_menu();
void start_menu();
void load1_event(GtkWidget *widget,GdkEvent* event);
void load2_event(GtkWidget *widget,GdkEvent* event);
void load3_event(GtkWidget *widget,GdkEvent* event);
void back_load_event(GtkWidget *widget,GdkEvent* event);
void load_signals();
void open_game();
void open_top10();
void menu_signals();
void main_m();


#endif // MAIN_MENU_H_INCLUDED

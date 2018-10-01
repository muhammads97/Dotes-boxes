#ifndef SAVE_GAME_H_INCLUDED
#define SAVE_GAME_H_INCLUDED
#include <gtk/gtk.h>
#include <string.h>
#include "game_play.h"
#include "game_options.h"

struct box_data{
    int hl,vl;
    int n;
    int m;
    int semif;
    int f;
};

struct save{
    struct box_data b[7][7];
    struct player p1;
    struct player p2;
    int n, turn;
    int s;
    int l1,l2;
    int r_dots;
    int available;
};

extern GtkWidget *save_win,*slot1,*slot2,*slot3,*back_save,*vbox5,*saved_label;
void save_game(const char *file);
void save_window();
void save_signal(GtkWidget *widget,GdkEvent *event);
void back_save_signal(GtkWidget *widget,GdkEvent *event);
void slot1_signal(GtkWidget *widget,GdkEvent *event);
void slot2_signal(GtkWidget *widget,GdkEvent *event);
void slot3_signal(GtkWidget *widget,GdkEvent *event);
void saved_label_change();
void save_win_signals();



#endif // SAVE_GAME_H_INCLUDED

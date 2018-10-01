#ifndef UNDO_REDO_H_INCLUDED
#define UNDO_REDO_H_INCLUDED
#include "game_play.h"

struct move_details {
    int n;
    int m;
    int vl;
    int hl;
    int f;
    int p1score;
    int p2score;
    int turn;
    int semif;
    int r_dots;
};

extern struct move_details moves[100];
extern struct move_details mredo[100];

extern int hl;
extern int vl;
extern int i;
extern int k;

void set_move_zero();
void store (int n,int m);
void undo_v ();
void moves_mredo ();
void undo_h();
void undo_game ();
void undo_event(GtkWidget *widget, GdkEvent *event);
void moves_init ();
void init_redo();
void redo_event(GtkWidget *widget,GdkEvent *event);
void redo_game ();
void redo_v();
void redo_h ();


#endif // UNDO_REDO_H_INCLUDED

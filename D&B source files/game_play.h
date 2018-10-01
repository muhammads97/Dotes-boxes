#ifndef GAME_PLAY_H_INCLUDED
#define GAME_PLAY_H_INCLUDED
#include <gtk/gtk.h>
#include <string.h>
#define Font_desc "Showcard Gothic Bold 25"


struct boxes{
    GtkWidget *eb1;
    GtkWidget *eb2;
    GtkWidget *h;
    GtkWidget *v;
    GtkWidget *b;
    int hl,vl;
    int n;
    int m;
    int semif;
    int f;
};

struct player{
    char *name;
    int score;
    int len;
};




extern struct player p1;
extern struct player p2;

extern struct boxes box[7][7];

extern int g_size;
extern int num_filled_boxes;
extern int player_turn;
extern int remaining_dots;
extern int n;
extern int hr,min,sec;
extern int num_of_players;

extern PangoFontDescription *font;

extern GdkColor color;


extern GtkWidget *frame, *vbox10;
extern GtkWidget *gam_over_photo5,*gam_over_photo2;
extern GtkWidget *g_over;
extern GtkWidget *game;
extern GtkWidget *image;
extern GtkWidget *p1_hline, *p2_hline;
extern GtkWidget *p1_vline, *p2_vline;
extern GtkWidget *box_blanck, *p1_box, *p2_box;
extern GtkWidget *pos,*hblanck,*vblanck;
extern GtkWidget *p_turn, *p1_score, *p2_score, *num_of_r_dots, *time_elapsed, * winner;

void show_main_menu();

void moves_mredo ();
void update_labels();
void set_move_zero();
void store (int n,int m);
void undo_v ();
void undo_h();
void undo_game ();
void undo_event(GtkWidget *widget, GdkEvent *event);
void moves_init ();
void redo_h ();
void redo_event(GtkWidget *widget,GdkEvent *event);
void redo_game ();
void name_alloc();
void set_game_data(int s, char *name1, char *name2);
gint timeout_callback ();
void nm_init(int g_size);
void h_line_change(GtkWidget *w,GdkEvent *e,gpointer u);
void hide_for_game_over();
void v_line_change(GtkWidget *w,GdkEvent *e,gpointer u);
void v_boxes_update(int n,int m,gpointer u);
void game_over();
int winner_name();
void h_boxes_update(int n,int m,gpointer u);
void score_update(int n);
void player_turn_change();
void semi_filled_check(int n, int m);
int filled_check(int n, int m);
int h_filled_boxes (int n,int m);
int v_filled_boxes (int n,int m);
void init_grid(int g_size);
void init_boxes(int g_size);
void init_eb(int g_size);
void labels_init();
void fix_labels();
void start_game_window(int s, char *name1, char *name2);


#endif // GAME_PLAY_H_INCLUDED

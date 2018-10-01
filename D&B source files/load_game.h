#ifndef LOAD_GAME_H_INCLUDED
#define LOAD_GAME_H_INCLUDED
#include "save_game.h"

extern GtkWidget *load_win,*load1,*load2,*load3,*back_load;

struct save load_from_file(const char *file);
void set_game(const char *file);
void set_boxes(struct box_data b[7][7]);
void load_game_window();
void load_event(GtkWidget *widget,GdkEvent* event);


#endif // LOAD_GAME_H_INCLUDED

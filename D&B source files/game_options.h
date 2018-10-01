#ifndef GAME_OPTIONS_H_INCLUDED
#define GAME_OPTIONS_H_INCLUDED
#include <gtk/gtk.h>
#include <string.h>
#include "game_play.h"
#include "save_game.h"
extern GtkWidget *pos,*frame2,*hbox5,*save_button,*undo,*redo;

void game_options();
void game_options_signals();

#endif // GAME_OPTIONS_H_INCLUDED

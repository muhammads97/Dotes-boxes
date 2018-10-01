#include "game_options.h"

GtkWidget *pos,*frame2,*hbox5,*save_button,*undo,*redo;

void game_options(){
    save_button=gtk_button_new_with_label("Save Game");
    undo=gtk_button_new_with_label("Undo");
    redo=gtk_button_new_with_label("Redo");
    gtk_widget_set_size_request(save_button,182,50);
    hbox5=gtk_hbox_new(TRUE,4);
    gtk_box_pack_start(GTK_BOX(hbox5),save_button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox5),undo,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox5),redo,TRUE,TRUE,0);
    frame2=gtk_frame_new("Game Options");
    gtk_container_add(GTK_FRAME(frame2),hbox5);
    int x;
    if(g_size==5)x=620;
    else x=320;
    gtk_fixed_put(GTK_FIXED(pos),frame2,x,400);
}


void game_options_signals(){
    g_signal_connect(G_OBJECT(undo), "clicked",G_CALLBACK(undo_event),NULL);
    g_signal_connect(G_OBJECT(redo), "clicked",G_CALLBACK(redo_event),NULL);
    save_win_signals();
}


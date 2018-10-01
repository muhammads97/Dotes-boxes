#include "game_over.h"
#include "sound_threads.h"

GtkWidget *main_menu_button, *exit_button, *label4, *game_over_win, *vbox8;

void g_over_win_init(){
    game_over_win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(game_over_win),GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request(GTK_WINDOW(game_over_win),500,300);
    exit_button=gtk_button_new_with_label("Exit");
    main_menu_button=gtk_button_new_with_label("Main Menu");
    label4=gtk_label_new("");
    vbox8=gtk_vbox_new(TRUE,3);
    gtk_box_pack_start(GTK_BOX(vbox8),label4,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox8),main_menu_button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox8),exit_button,TRUE,TRUE,0);
    gtk_container_add(GTK_WINDOW(game_over_win),vbox8);

    font =pango_font_description_from_string(Font_desc);
    gdk_color_parse("#73125d", &color);

    gtk_widget_modify_fg(GTK_WIDGET(label4), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(label4),font);
}

void game_over_signals(){
    g_signal_connect(G_OBJECT(exit_button), "clicked",G_CALLBACK(gtk_main_quit),NULL);
    g_signal_connect(G_OBJECT(main_menu_button), "clicked",G_CALLBACK(show_main_menu),NULL);
    g_signal_connect(G_OBJECT(game_over_win), "destroy",G_CALLBACK(show_main_menu),NULL);
}

void show_main_menu(){
    bg_loop=0;
    remaining_dots=0;
    n=0;
    gtk_widget_hide(game);
    gtk_widget_hide(game_over_win);
    gtk_widget_show_all(main_menu);
    gtk_widget_hide(vbox2);
}

void g_over_win_show(const char *name){
    gchar *dis = g_strdup_printf("%s Wins!",name);
    gtk_label_set_text(GTK_LABEL(label4),dis);
    gtk_widget_show_all(game_over_win);
}

void game_over(){
    if(remaining_dots == 0){
        hide_for_game_over();
        g_over = gtk_image_new();
        if(g_size==5){
            gtk_image_set_from_pixbuf(GTK_IMAGE(g_over),gam_over_photo5);
            gtk_fixed_put(GTK_FIXED(pos),g_over,0,160);
        }
        else {
            gtk_image_set_from_pixbuf(GTK_IMAGE(g_over),gam_over_photo2);
            gtk_fixed_put(GTK_FIXED(pos),g_over,0,80);
        }
        if(winner_name()==1){
            gchar *display=g_strdup_printf("WE HAVE A WINNER! %s",p1.name);
            gtk_label_set_text(GTK_LABEL(winner),display);
            g_over_win_show(p1.name);
        }
        else if(winner_name()==2){
            gchar *display=g_strdup_printf("WE HAVE A WINNER! %s",p2.name);
            gtk_label_set_text(GTK_LABEL(winner),display);
            g_over_win_show(p2.name);
        }
        else{
            gchar *display=g_strdup_printf("DRAW!!!");
            gtk_label_set_text(GTK_LABEL(winner),display);
            g_over_win_show("No One");
        }

        gtk_widget_show(g_over);
        save_score(p1,p2);
    }
}
int winner_name(){
    if(p1.score>p2.score){
        return 1;
    }
    else if(p2.score>p1.score){
        return 2;
    }
    else return 0;
}

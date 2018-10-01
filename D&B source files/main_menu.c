#include "main_menu.h"
#include "user_manual.h"
#include "sound_threads.h"

char *n1, *n2;
int g=2;

GtkWidget *main_menu,*img;
GtkWidget *vbox1,*vbox2,*vbox3,*lala;
GtkWidget *label1;
GtkWidget *start_game;
GtkWidget *load_game;
GtkWidget *top_ten,*top_ten_win,*back_top_ten,*top_ten_label[10],*vbox7;
GtkWidget *close;
GtkWidget *text1,*text2;
GtkWidget *hbox1,*hbox2,*hbox3,*hbox4,*start,*back,*label,*label2,*label3;
GtkWidget *r1, *r2, *r3, *r4;
GtkWidget *user_manual_win, *user_manual_button, *back_user_manual, * user_manual_label, *vbox9;

GdkPixbuf *logo;

void user_manual_init(){
    user_manual_win=gtk_window_new(GTK_WINDOW_POPUP);
    gtk_window_set_position(GTK_WINDOW(user_manual_win),GTK_WIN_POS_CENTER);
    font =pango_font_description_from_string("Arial bold 14");
    gdk_color_parse("#fffffff", &color);
    user_manual_label=gtk_label_new(U_M);
    gtk_widget_modify_fg(GTK_WIDGET(user_manual_label), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(user_manual_label),font);

    vbox9=gtk_vbox_new(FALSE,10);
    back_user_manual=gtk_button_new_with_label("Back");
    gtk_widget_set_size_request(GTK_BUTTON(back_user_manual),300,80);
    gtk_box_pack_start(GTK_BOX(vbox9),user_manual_label,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox9),back_user_manual,FALSE,FALSE,0);
    gtk_container_add(GTK_WINDOW(user_manual_win),vbox9);
}

void show_user_manual(){
    gtk_widget_show_all(user_manual_win);
    gtk_widget_hide(main_menu);
}

void hide_user_manual(){
    gtk_widget_hide(user_manual_win);
    gtk_widget_show_all(main_menu);
    gtk_widget_hide(vbox2);
}

void g_size2(GtkWidget *widget, GdkEvent * event){
    g_size=2;
}

void g_size5(GtkWidget *widget, GdkEvent * event){
    g_size=5;
}
void nplayers2(GtkWidget *widget, GdkEvent * event){
    num_of_players=2;
}
void nplayers1(GtkWidget *widget, GdkEvent * event){
    num_of_players=1;
}

void startg(){
    p1.name=gtk_entry_get_text(GTK_ENTRY(text1));
    if(num_of_players==1){
        p2.name="computer";
    }
    else{
        p2.name=gtk_entry_get_text(GTK_ENTRY(text2));
    }
}
void single_player(){
    gtk_widget_hide(hbox4);
}
void two_player(){
    gtk_widget_show(hbox4);
}
void player_name(){
    label2=gtk_label_new("player 1:");
    label3=gtk_label_new("player 2:");
    text1=gtk_entry_new();
    text2=gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(text1),"player1");
    gtk_entry_set_text(GTK_ENTRY(text2),"player2");
    gtk_entry_set_max_length(GTK_ENTRY(text2),20);
    gtk_entry_set_max_length(GTK_ENTRY(text1),20);
    hbox3=gtk_hbox_new(FALSE,3);
    hbox4=gtk_hbox_new(FALSE,3);
    gtk_box_pack_start(GTK_BOX(hbox3),label2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox3),text1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox4),label3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox4),text2,TRUE,TRUE,0);
    vbox3=gtk_vbox_new(TRUE,2);
    gtk_box_pack_start(GTK_BOX(vbox3),hbox3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox3),hbox4,TRUE,TRUE,0);
}
void main_menu_win(GtkWidget *window) {
    logo = gdk_pixbuf_new_from_file("logo.png",NULL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"Dots and Boxes v2.0");
    gtk_window_set_default_size(GTK_WINDOW(window),300,300);
    gtk_container_set_border_width(GTK_WINDOW(window),2);
    gtk_window_set_icon(GTK_WINDOW(window),logo);
    img = gtk_image_new_from_pixbuf(logo);
    lala=gtk_vbox_new(FALSE,1);

    vbox1=gtk_vbox_new(FALSE,1);
    vbox2=gtk_vbox_new(FALSE,1);
    gtk_container_add(GTK_WINDOW(window),lala);

    gtk_box_pack_start(GTK_BOX(lala),vbox1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(lala),vbox2,TRUE,TRUE,0);

    start_menu();

    label1=gtk_label_new("Dots&Boxes v2.0");

    start_game=gtk_button_new_with_label("Start Game");
    user_manual_button=gtk_button_new_with_label("User Manual");
    load_game=gtk_button_new_with_label("Load Game");
    top_ten=gtk_button_new_with_label("Top 10 Players");
    close=gtk_button_new_with_label("Exit");

    gtk_box_pack_start(GTK_BOX(vbox1),img,FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox1),start_game,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox1),user_manual_button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox1),load_game,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox1),top_ten,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox1),close,TRUE,TRUE,0);

}
void open_start_game(){
    gtk_widget_show_all(vbox2);
}
void open_main_menu(){
    gtk_widget_show_all(vbox1);
}
void close_start_game(){
    gtk_widget_hide(vbox2);
}
void close_main_menu(){
    gtk_widget_hide(vbox1);
}

void start_menu(){


    hbox1=gtk_hbox_new(TRUE,5);
    hbox2=gtk_hbox_new(TRUE,5);

    player_name();
    r1=gtk_radio_button_new_with_label(NULL,"Beginer");
    r2=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(r1),"Expert");
    r3=gtk_radio_button_new_with_label(NULL,"Two Players");
    r4=gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(r3),"Single Player");

    gtk_box_pack_start(GTK_BOX(hbox1),r1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox1),r2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),r3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),r4,TRUE,TRUE,0);
    gchar *display=g_strdup_printf("Start Game");
    label=gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(label),display);
    font =pango_font_description_from_string("Arial bold italic 14");
    gdk_color_parse("#fffffff", &color);
    gtk_widget_modify_fg(GTK_WIDGET(label), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_font(GTK_WIDGET(label),font);

    start=gtk_button_new_with_label("Start!");
    back=gtk_button_new_with_label("Back");

    gtk_box_pack_start(GTK_BOX(vbox2),label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox2),hbox1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox2),hbox2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox2),vbox3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox2),start,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox2),back,TRUE,TRUE,0);

}

void load1_event(GtkWidget *widget,GdkEvent* event){
    set_game("slot1.bin");
    gtk_widget_hide(load_win);
    gtk_widget_hide(main_menu);
}

void load2_event(GtkWidget *widget,GdkEvent* event){
    set_game("slot2.bin");
    gtk_widget_hide(load_win);
    gtk_widget_hide(main_menu);
}

void load3_event(GtkWidget *widget,GdkEvent* event){
    set_game("slot3.bin");
    gtk_widget_hide(load_win);
    gtk_widget_hide(main_menu);
}
void back_load_event(GtkWidget *widget,GdkEvent* event){
    gtk_widget_hide(load_win);
    gtk_widget_show_all(main_menu);
    gtk_widget_hide(vbox2);
}
void load_signals(){
    g_signal_connect(G_OBJECT(load1), "clicked",G_CALLBACK(load1_event), NULL);
    g_signal_connect(G_OBJECT(load2), "clicked",G_CALLBACK(load2_event), NULL);
    g_signal_connect(G_OBJECT(load3), "clicked",G_CALLBACK(load3_event), NULL);
    g_signal_connect(G_OBJECT(back_load), "clicked",G_CALLBACK(back_load_event), NULL);
}

void open_game(){
    bg_loop=1;
    startg();
    start_game_window(g_size, p1.name, p2.name);
    gtk_widget_hide(main_menu);
}

void open_top10(){
    gtk_widget_hide(main_menu);
    gtk_widget_show_all(top_ten_win);
    FILE *ptr;
    ptr=fopen("top.txt","r");
    if(!ptr){
        g_printf("oops!");
        return;
    }
    struct player p;
    int d,u=0;
    p.name=(char*)malloc(sizeof(char)*100);
    for(d=0;d<10;d++){
        fread(&p.len,sizeof(int),1,ptr);
        fread(p.name,sizeof(char),p.len,ptr);
        fread(&p.score,sizeof(int),1,ptr);
        if(p.score==-1){
            u++;
        }
        else{
            gchar *dis = g_strdup_printf("%d. %s .................. %d",d+1-u,p.name,p.score);
            gtk_label_set_text(GTK_LABEL(top_ten_label[d-u]),dis);
            font =pango_font_description_from_string("Arial bold italic 14");
            gdk_color_parse("#fffffff", &color);
            gtk_widget_modify_fg(GTK_WIDGET(top_ten_label[d-u]), GTK_STATE_NORMAL, &color);
            gtk_widget_modify_font(GTK_WIDGET(top_ten_label[d-u]),font);
        }

    }
    fclose(ptr);

}

void hide_top_ten(){
    gtk_widget_hide(top_ten_win);
    gtk_widget_show_all(main_menu);
    gtk_widget_hide(vbox2);
}

void menu_signals(){
    g_signal_connect(G_OBJECT(main_menu), "destroy",G_CALLBACK(gtk_main_quit), G_OBJECT(main_menu));
    g_signal_connect(G_OBJECT(start_game), "clicked", G_CALLBACK(open_start_game), NULL);
    g_signal_connect(G_OBJECT(start_game), "clicked", G_CALLBACK(close_main_menu), NULL);
    g_signal_connect(G_OBJECT(close), "clicked",G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(back), "clicked",G_CALLBACK(close_start_game), NULL);
    g_signal_connect(G_OBJECT(back), "clicked",G_CALLBACK(open_main_menu), NULL);
    g_signal_connect(G_OBJECT(start), "clicked",G_CALLBACK(open_game), NULL);
    g_signal_connect(G_OBJECT(r1), "clicked",G_CALLBACK(g_size2), NULL);
    g_signal_connect(G_OBJECT(r2), "clicked",G_CALLBACK(g_size5), NULL);
    g_signal_connect(G_OBJECT(r3), "clicked",G_CALLBACK(nplayers2), NULL);
    g_signal_connect(G_OBJECT(r4), "clicked",G_CALLBACK(nplayers1), NULL);
    //g_signal_connect(G_OBJECT(start), "clicked",G_CALLBACK(startg), NULL);
    g_signal_connect(G_OBJECT(r3), "clicked",G_CALLBACK(two_player), NULL);
    g_signal_connect(G_OBJECT(r4), "clicked",G_CALLBACK(single_player), NULL);
    g_signal_connect(G_OBJECT(top_ten), "clicked",G_CALLBACK(open_top10), NULL);
    g_signal_connect(G_OBJECT(back_top_ten), "clicked",G_CALLBACK(hide_top_ten), NULL);
    g_signal_connect(G_OBJECT(load_game), "clicked",G_CALLBACK(load_event), NULL);
    g_signal_connect(G_OBJECT(user_manual_button), "clicked",G_CALLBACK(show_user_manual), NULL);
    g_signal_connect(G_OBJECT(back_user_manual), "clicked",G_CALLBACK(hide_user_manual), NULL);
    load_signals();
    gtk_widget_show_all(main_menu);
    gtk_widget_hide(vbox2);
}

void init_top_ten(){
    top_ten_win=gtk_window_new(GTK_WINDOW_POPUP);
    gtk_window_set_position(GTK_WINDOW(top_ten_win),GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(top_ten_win),500,300);
    back_top_ten=gtk_button_new_with_label("Back");
    int d;
    for(d=0;d<10;d++){
        top_ten_label[d]=gtk_label_new("");
    }
    top_ten_label[0]=gtk_label_new("..No records..");
    vbox7=gtk_vbox_new(FALSE,5);
    for(d=0;d<10;d++){
        gtk_box_pack_start(GTK_BOX(vbox7),top_ten_label[d],TRUE,TRUE,0);
    }

    gtk_box_pack_start(GTK_BOX(vbox7),back_top_ten,TRUE,TRUE,0);

    gtk_container_add(GTK_WINDOW(top_ten_win),vbox7);
}

void main_m(){
    line_change_threads();
    name_alloc();
    main_menu=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    main_menu_win(main_menu);
    load_game_window();
    init_top_ten();
    user_manual_init();
    menu_signals();
}

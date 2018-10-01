#include <gtk/gtk.h>
#include <string.h>
#include "game_play.h"
#include "save_game.h"
#include "game_options.h"
#include "load_game.h"
#include "undo_redo.h"
#include "sound_threads.h"
#include "computer.h"
#include "top_ten.h"
#include "main_menu.h"
#include "game_over.h"

#define Font_desc "Showcard Gothic Bold 25"


struct player p1;
struct player p2;

struct boxes box[7][7];

int num_of_players=2;
int g_size=2;
int player_turn=1;
int remaining_dots;
int n=0;
int hr,min,sec;
int c=0;

PangoFontDescription *font;

GdkColor color;

GtkWidget *frame, *vbox10;
GtkWidget *gam_over_photo5,*gam_over_photo2;
GtkWidget *g_over;
GtkWidget *game;
GtkWidget *image;
GtkWidget *p1_hline, *p2_hline;
GtkWidget *p1_vline, *p2_vline;
GtkWidget *box_blanck, *p1_box, *p2_box;
GtkWidget *pos,*hblanck,*vblanck;
GtkWidget *p_turn, *p1_score, *p2_score, *num_of_r_dots, *time_elapsed, * winner;


void update_labels(){ //lma bnady 3liha btghyr el labels
    gchar *display;
    display=g_strdup_printf(" number of remaining lines : %d   ",remaining_dots);
    gtk_label_set_text(GTK_LABEL(num_of_r_dots),display);
    display=g_strdup_printf("%s's score = %d",p1.name,p1.score);
    gtk_label_set_text(GTK_LABEL(p1_score),display);
    display=g_strdup_printf("%s's score = %d",p2.name,p2.score);
    gtk_label_set_text(GTK_LABEL(p2_score),display);
    if(player_turn==1){
        gchar *display=g_strdup_printf("%s's turn     ",p1.name);
        gtk_label_set_text(GTK_LABEL(p_turn),display);
    }
    else if(player_turn==2){
        gchar *display=g_strdup_printf("%s's turn     ",p2.name);
        gtk_label_set_text(GTK_LABEL(p_turn),display);
    }
}

void name_alloc(){
    p1.name=(char*)malloc(sizeof(char)*100);
    p2.name=(char*)malloc(sizeof(char)*100);
}
void set_game_data(int s, char *name1, char *name2){
    g_size=s;
    remaining_dots=(g_size+1)*g_size*2;
    p1.name=name1;
    p2.name=name2;
    p1.score=0;
    p2.score=0;
}

gint callback_computer_move(){
    w=0;
    if(num_of_players==2)return;
    if(player_turn==2){
        computer();
    }
}

gint timeout_callback (){
    n++;
    int t;
    hr = n/3600;
    t= n%3600;
    min = t/60;
    sec = t%60;
    gchar *display;
    display=g_strdup_printf("time elapsed : %d:%d:%d",hr,min,sec);
    gtk_label_set_text(GTK_LABEL(time_elapsed),display);
    if (remaining_dots==0){
        return 0;
    }
}

void nm_init(int g_size){
    int i,j;
    for(i=1;i<g_size+2;i++){
        for(j=1;j<g_size+2;j++){
            box[i][j].n=i;
            box[i][j].m=j;
            box[i][j].f=0;
            box[i][j].vl=0;
            box[i][j].hl=0;
            box[i][j].semif=0;
        }

    }
    moves_init();
}

void h_line_change(GtkWidget *w,GdkEvent *e,gpointer u){
    struct boxes *b=u;
    if(num_of_players==1 && player_turn==2)return;
    if(b->hl==0){
        q=1;
        hl=1;
        GtkWidget *fbox;
        GtkWidget *h_line;
        remaining_dots--;
        gchar *display;
        display=g_strdup_printf(" number of remaining lines : %d   ",remaining_dots);
        gtk_label_set_text(GTK_LABEL(num_of_r_dots),display);
        if(player_turn==1){
            h_line=p1_hline;
            fbox=p1_box;
            b->hl=1;
        }
        else if(player_turn==2){
            h_line=p2_hline;
            fbox=p2_box;
            b->hl=2;
        }

        gtk_image_set_from_pixbuf(GTK_IMAGE(b->h),h_line);

        semi_filled_check(b->n,b->m);

        h_boxes_update(b->n,b->m,fbox);
        store(b->n,b->m);
        hl=0;
        init_redo();

        game_over();
        q=0;
        w=0;
    }
}
void hide_for_game_over(){
    int i,j;
    if(g_size==5){
        for(i=2;i<=4;i++){
            for(j=0;j<g_size+2;j++){
                gtk_widget_hide(box[i][j].v);
                gtk_widget_hide(box[i][j].h);
            }
        }
    }
    else{
        for(i=1;i<=g_size+1;i++){
            for(j=1;j<=g_size+1;j++){
                gtk_widget_hide(box[i][j].v);
                gtk_widget_hide(box[i][j].h);
            }
        }
    }

}
void v_line_change(GtkWidget *w,GdkEvent *e,gpointer u){
    struct boxes *b=u;
    if(num_of_players==1 && player_turn==2)return;
    if(b->vl==0){
        q=1;
        vl=1;
        GtkWidget *fbox;
        GtkWidget *v_line;
        remaining_dots--;
        gchar *display;
        display=g_strdup_printf(" number of remaining lines : %d   ",remaining_dots);
        gtk_label_set_text(GTK_LABEL(num_of_r_dots),display);
        if(player_turn==1){
            v_line=p1_vline;
            fbox=p1_box;
            b->vl=1;
        }
        else if(player_turn==2){
            v_line=p2_vline;
            fbox=p2_box;
            b->vl=2;
        }
        gtk_image_set_from_pixbuf(GTK_IMAGE(b->v),v_line);

        semi_filled_check(b->n,b->m);

        v_boxes_update(b->n,b->m,fbox);
        store(b->n,b->m);
        vl=0;


        init_redo();
        q=0;
        game_over();
        w=0;
    }
}

void v_boxes_update(int n,int m,gpointer u){
    GtkWidget *fbox=u;
    if(v_filled_boxes(n,m)==1){
            gtk_image_set_from_pixbuf(GTK_IMAGE(box[n][m].b),fbox);
            gtk_image_set_from_pixbuf(GTK_IMAGE(box[n][m-1].b),fbox);
            score_update(2);
    }
    else if(v_filled_boxes(n,m)==3){
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[n][m-1].b),fbox);
        score_update(1);
    }
    else if(v_filled_boxes(n,m)==2){
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[n][m].b),fbox);
        score_update(1);
    }
    else if(v_filled_boxes(n,m)==0){
        player_turn_change();
    }
}

void h_boxes_update(int n,int m,gpointer u){
    GtkWidget *fbox=u;
    if(h_filled_boxes(n,m)==1){
            gtk_image_set_from_pixbuf(GTK_IMAGE(box[n][m].b),fbox);
            gtk_image_set_from_pixbuf(GTK_IMAGE(box[n-1][m].b),fbox);
            score_update(2);
    }
    else if(h_filled_boxes(n,m)==3){
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[n-1][m].b),fbox);
        score_update(1);
    }
    else if(h_filled_boxes(n,m)==2){
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[n][m].b),fbox);
        score_update(1);
    }
    else if(h_filled_boxes(n,m)==0){
        player_turn_change();
    }
}

void score_update(int n){
    gchar *display;

    if(player_turn==1){
        p1.score+=n;
        display=g_strdup_printf("%s's score = %d",p1.name,p1.score);
        gtk_label_set_text(GTK_LABEL(p1_score),display);

    }
    else {
        p2.score+=n;
        display=g_strdup_printf("%s's score = %d",p2.name,p2.score);
        gtk_label_set_text(GTK_LABEL(p2_score),display);
        //if(num_of_players==1)computer();
    }
}

void player_turn_change(){
    gchar *display;
    if(player_turn==1){
        player_turn=2;
        /*if(num_of_players==1){
            computer();
        }*/
        //remaining_dots--;
        gchar *display=g_strdup_printf("%s's turn     ",p2.name);
        gtk_label_set_text(GTK_LABEL(p_turn),display);
    }
    else if(player_turn==2){
        player_turn=1;
        //remaining_dots--;
        gchar *display=g_strdup_printf("%s's turn     ",p1.name);
        gtk_label_set_text(GTK_LABEL(p_turn),display);
    }
}

void semi_filled_check(int n, int m){
    if((box[n][m].hl == 1 || box[n][m].hl == 2) && (box[n][m].vl == 1 || box[n][m].vl == 2)){
        box[n][m].semif=1;
    }
}

int filled_check(int n, int m){
    if(box[n][m].semif==1){
        if((box[n][m+1].vl==1 || box[n][m+1].vl==2) && (box[n+1][m].hl==1 || box[n+1][m].hl==2)){
            w=2;
            box[n][m].f=player_turn;
            return 1;
        }
    }
    return 0;
}

int h_filled_boxes (int n,int m){
    int f1,f2;
    f1=filled_check(box[n][m].n,box[n][m].m);
    f2=filled_check((box[n][m].n)-1,box[n][m].m);
    if(f1==1 && f2==1){
        return 1;
    }
    else if(f1==1){
        return 2;
    }
    else if(f2==1){
        return 3;
    }
    else return 0;
}

int v_filled_boxes (int n,int m){
    int f1,f2;
    f1=filled_check(box[n][m].n,box[n][m].m);
    f2=filled_check((box[n][m].n),(box[n][m].m)-1);
    if(f1==1 && f2==1){
        return 1;
    }
    else if(f1==1){
        return 2;
    }
    else if(f2==1){
        return 3;
    }
    else return 0;
}

void init_grid(int g_size){
    game=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_WINDOW(game),20);
    hblanck=gdk_pixbuf_new_from_file("blanck1.png",NULL);
    vblanck=gdk_pixbuf_new_from_file("blanck2.png",NULL);
    box_blanck=gdk_pixbuf_new_from_file("box_blanck.png",NULL);

    if(g_size==2){
        image=gtk_image_new_from_file("1.png");
    }
    else if(g_size==5){
        image=gtk_image_new_from_file("5x5.png");
    }
    gam_over_photo5=gdk_pixbuf_new_from_file("game over.png",NULL);
    gam_over_photo2=gdk_pixbuf_new_from_file("game over2.png",NULL);
    p1_hline=gdk_pixbuf_new_from_file("player_one_hline.png",NULL);
    p2_hline=gdk_pixbuf_new_from_file("player_two_hline.png",NULL);

    p1_vline=gdk_pixbuf_new_from_file("player_one_vline.png",NULL);
    p2_vline=gdk_pixbuf_new_from_file("player_two_vline.png",NULL);

    p1_box=gdk_pixbuf_new_from_file("player_one_box.png",NULL);
    p2_box=gdk_pixbuf_new_from_file("player_two_box.png",NULL);
    //g_over=gtk_image_new_from_file("game over.png");

    pos=gtk_fixed_new();
    gtk_container_add(GTK_WINDOW(game),pos);
    gtk_fixed_put(GTK_FIXED(pos),image,0,0);

    //gtk_widget_hide(g_over);
}

void init_boxes(int g_size){
    int i,j,x,y;
    for(i=1;i<g_size+1;i++){
        for(j=1;j<g_size+1;j++){
            x=((j-1)*100)+40;
            y=((i-1)*100)+40;
            box[i][j].eb1=gtk_event_box_new();
            box[i][j].eb2=gtk_event_box_new();

            box[i][j].h=gtk_image_new();
            box[i][j].v=gtk_image_new();
            box[i][j].b=gtk_image_new();

            gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].h),hblanck);
            gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].v),vblanck);
            gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].b),box_blanck);

            gtk_container_add(GTK_CONTAINER(box[i][j].eb1),box[i][j].h);
            gtk_container_add(GTK_CONTAINER(box[i][j].eb2),box[i][j].v);

            gtk_fixed_put(GTK_FIXED(pos),box[i][j].eb1,x+20,y);
            gtk_fixed_put(GTK_FIXED(pos),box[i][j].eb2,x,y+20);
            gtk_fixed_put(GTK_FIXED(pos),box[i][j].b,x+20,y+20);
        }
    }
    for(i=1;i<g_size+1;i++){
        y=((i-1)*100)+40;
        x=(g_size*100)+40;
        box[i][g_size+1].eb2=gtk_event_box_new();
        box[i][g_size+1].v=gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE( box[i][g_size+1].v),vblanck);
        gtk_container_add(GTK_CONTAINER(box[i][g_size+1].eb2),box[i][g_size+1].v);
        gtk_fixed_put(GTK_FIXED(pos),box[i][g_size+1].eb2,x,y+20);
    }
    for(i=1;i<g_size+1;i++){
        x=((i-1)*100)+40;
        y=(g_size*100)+40;
        box[g_size+1][i].eb1=gtk_event_box_new();
        box[g_size+1][i].h=gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE( box[g_size+1][i].h),hblanck);
        gtk_container_add(GTK_CONTAINER(box[g_size+1][i].eb1),box[g_size+1][i].h);
        gtk_fixed_put(GTK_FIXED(pos),box[g_size+1][i].eb1,x+20,y);
    }

}

void init_eb(int g_size){
    int i,j;
    g_signal_connect(G_OBJECT(game), "destroy",G_CALLBACK(show_main_menu), NULL);
    for(i=1;i<g_size+1;i++){
        for(j=1;j<g_size+1;j++){
            g_signal_connect(G_OBJECT(box[i][j].eb1), "button_press_event",G_CALLBACK(h_line_change),&box[i][j]);
            g_signal_connect(G_OBJECT(box[i][j].eb2), "button_press_event",G_CALLBACK(v_line_change),&box[i][j]);
        }
    }
    for(i=1;i<g_size+1;i++){
        g_signal_connect(G_OBJECT(box[g_size+1][i].eb1), "button_press_event",G_CALLBACK(h_line_change),&box[g_size+1][i]);
    }
    for(i=1;i<g_size+1;i++){
        g_signal_connect(G_OBJECT(box[i][g_size+1].eb2), "button_press_event",G_CALLBACK(v_line_change),&box[i][g_size+1]);
    }
}

void labels_init(){


    p_turn=gtk_label_new("");
    p1_score=gtk_label_new("");
    p2_score=gtk_label_new("");
    num_of_r_dots=gtk_label_new("");
    time_elapsed=gtk_label_new("");
    winner = gtk_label_new("");

    gchar *display=g_strdup_printf("%s's turn     ",p1.name);
    gtk_label_set_text(GTK_LABEL(p_turn),display);
    display=g_strdup_printf("%s's score = %d",p1.name,p1.score);
    gtk_label_set_text(GTK_LABEL(p1_score),display);
    display=g_strdup_printf("%s's score = %d",p2.name,p2.score);
    gtk_label_set_text(GTK_LABEL(p2_score),display);
    display=g_strdup_printf(" number of remaining lines : %d   ",remaining_dots);
    gtk_label_set_text(GTK_LABEL(num_of_r_dots),display);
    display=g_strdup_printf("time elapsed : ");
    gtk_label_set_text(GTK_LABEL(time_elapsed),display);

    font =pango_font_description_from_string(Font_desc);
    gdk_color_parse("#73125d", &color);

    gtk_widget_modify_fg(GTK_WIDGET(p_turn), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(p1_score), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(p2_score), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(num_of_r_dots), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(time_elapsed), GTK_STATE_NORMAL, &color);
    gtk_widget_modify_fg(GTK_WIDGET(winner), GTK_STATE_NORMAL, &color);

    gtk_widget_modify_font(GTK_WIDGET(p_turn),font);
    gtk_widget_modify_font(GTK_WIDGET(p1_score),font);
    gtk_widget_modify_font(GTK_WIDGET(p2_score),font);
    gtk_widget_modify_font(GTK_WIDGET(num_of_r_dots),font);
    gtk_widget_modify_font(GTK_WIDGET(time_elapsed),font);
    gtk_widget_modify_font(GTK_WIDGET(winner),font);

    frame = gtk_frame_new("game details");
    vbox10=gtk_vbox_new(FALSE, 20);
    gtk_box_pack_start(GTK_BOX(vbox10),p_turn, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox10),p1_score, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox10),p2_score, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox10),num_of_r_dots, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox10),time_elapsed, FALSE,FALSE,0);
    gtk_box_pack_start(GTK_BOX(vbox10),winner, FALSE,FALSE,0);
    gtk_container_add(GTK_FRAME(frame),vbox10);



}

void fix_labels(){
    int x;
    if(g_size==5)x=620;
    else x=320;
    /*gtk_fixed_put(GTK_FIXED(pos),p_turn,x,20);
    gtk_fixed_put(GTK_FIXED(pos),p1_score,x,80);
    gtk_fixed_put(GTK_FIXED(pos),p2_score,x,140);
    gtk_fixed_put(GTK_FIXED(pos),num_of_r_dots,x,200);
    gtk_fixed_put(GTK_FIXED(pos),time_elapsed,x,260);*/
    gtk_fixed_put(GTK_FIXED(pos),frame,x,20);
}

void start_game_window(int s, char *name1, char *name2){
    set_game_data(s,name1,name2);
    init_grid(s);
    nm_init(s);
    init_boxes(s);
    init_eb(s);
    labels_init();
    fix_labels();
    game_options();
    save_window();
    game_options_signals();
    g_timeout_add(1000,timeout_callback,NULL);
    g_timeout_add(300,callback_computer_move,NULL);
    gtk_widget_show_all(game);
    g_over_win_init();
    game_over_signals();
}

#include "load_game.h"
#include "main_menu.h"
#include "sound_threads.h"

GtkWidget *load_win,*load1,*load2,*load3,*back_load,*vbox6,*load_label;

struct save load_from_file(const char *file){
    FILE *ptr;
    ptr=fopen(file,"r");
    if(!ptr){
        g_printf("no file");
        return ;
    }
    int i,j;
    struct save s;
    s.p1.name=(char*)malloc(sizeof(char)*100);
    s.p2.name=(char*)malloc(sizeof(char)*100);
    fread(&s.available,sizeof(int),1,ptr);
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            fread(&s.b[i][j],sizeof(struct box_data),1,ptr);
        }
    }
    fread(&s.turn,sizeof(int),1,ptr);
    fread(&s.r_dots,sizeof(int),1,ptr);
    fread(&s.s,sizeof(int),1,ptr);
    fread(&s.l1,sizeof(int),1,ptr);
    fread(&s.l2,sizeof(int),1,ptr);
    fread(&s.n,sizeof(int),1,ptr);
    fread(&s.p1.score,sizeof(int),1,ptr);
    fread(&s.p2.score,sizeof(int),1,ptr);
    fread(s.p1.name,sizeof(char),s.l1,ptr);
    fread(s.p2.name,sizeof(char),s.l2,ptr);
    fclose(ptr);
    return s;
}

void set_game(const char *file){
    struct save s;
    s=load_from_file(file);
    bg_loop=1;
    init_grid(s.s);
    nm_init(s.s);
    init_boxes(s.s);
    init_eb(s.s);
    p1.name=s.p1.name;
    p1.score=s.p1.score;
    p2.name=s.p2.name;
    p2.score=s.p2.score;

    n=s.n;
    player_turn=s.turn;
    g_size=s.s;
    remaining_dots=s.r_dots;
    labels_init();
    fix_labels();
    game_options();
    save_window();
    game_options_signals();
    g_timeout_add(1000,timeout_callback,NULL);
    set_boxes(s.b);
    gtk_widget_show_all(game);
}

void set_boxes(struct box_data b[7][7]){
    int i,j;
    for(i=1;i<7;i++){
        for(j=1;j<7;j++){
            if(b[i][j].hl==1){
                box[i][j].hl=1;
                gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].h),p1_hline);
            }
            if(b[i][j].vl==1){
                box[i][j].vl=1;
                gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].v),p1_vline);
            }
            if(b[i][j].hl==2){
                box[i][j].hl=2;
                gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].h),p2_hline);
            }
            if(b[i][j].vl==2){
                box[i][j].vl=2;
                gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].v),p2_vline);
            }
            if(b[i][j].f==1){
                box[i][j].f=1;
                gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].b),p1_box);
            }
            if(b[i][j].f==2){
                box[i][j].f=2;
                gtk_image_set_from_pixbuf(GTK_IMAGE(box[i][j].b),p2_box);
            }
            box[i][j].semif=b[i][j].semif;

        }
    }
}


void load_game_window(){
    load_win=gtk_window_new(GTK_WINDOW_POPUP);
    gtk_window_set_position(GTK_WINDOW(load_win),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(load_win),"Load game");
    load1=gtk_button_new_with_label("Slot 1");
    load2=gtk_button_new_with_label("Slot 2");
    load3=gtk_button_new_with_label("Slot 3");
    back_load=gtk_button_new_with_label("Back");
    load_label=gtk_label_new("Load Game");
    vbox6=gtk_vbox_new(TRUE,2);
    gtk_widget_set_size_request(load1,300,100);

    gtk_box_pack_start(GTK_BOX(vbox6),load_label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox6),load1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox6),load2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox6),load3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox6),back_load,TRUE,TRUE,0);
    gtk_container_add(GTK_WINDOW(load_win),vbox6);

}
void load_event(GtkWidget *widget,GdkEvent* event){
    gtk_widget_show_all(load_win);
    gtk_widget_hide(main_menu);
    int s1,s2,s3;
    s1=load_from_file("slot1.bin").available;
    s2=load_from_file("slot2.bin").available;
    s3=load_from_file("slot3.bin").available;
    if(s1 != 1){
        gtk_widget_hide(load1);
    }
    if(s2 != 1){
        gtk_widget_hide(load2);
    }
    if(s3 != 1){
        gtk_widget_hide(load3);
    }
    if( s1 != 1 && s2 != 1 && s3 != 1){
        gtk_label_set_text(GTK_LABEL(load_label),"No Saved Games!");
    }
}


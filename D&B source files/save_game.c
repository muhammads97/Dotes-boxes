#include "save_game.h"
GtkWidget *save_win,*slot1,*slot2,*slot3,*back_save,*vbox5,*saved_label;

void save_game(const char *file){
    FILE *ptr;
    ptr=fopen(file,"wb");
    if(!ptr){
        g_printf("no file");
        return ;
    }
    int i,j;
    struct save s;
    s.p1.name=(char*)malloc(sizeof(char)*100);
    s.p2.name=(char*)malloc(sizeof(char)*100);
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            s.b[i][j].f=box[i][j].f;
            s.b[i][j].hl=box[i][j].hl;
            s.b[i][j].vl=box[i][j].vl;
            s.b[i][j].n=box[i][j].n;
            s.b[i][j].m=box[i][j].m;
            s.b[i][j].semif=box[i][j].semif;
        }
    }
    s.turn=player_turn;
    s.r_dots=remaining_dots;
    s.s=g_size;
    s.p1.name=p1.name;
    s.p2.name=p2.name;
    s.l1=strlen(p1.name)+1;
    s.l2=strlen(p2.name)+1;
    s.n=n;
    s.p1.score=p1.score;
    s.p2.score=p2.score;
    s.available=1;
    fwrite(&s.available,sizeof(int),1,ptr);
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            fwrite(&s.b[i][j],sizeof(struct box_data),1,ptr);
        }
    }
    fwrite(&s.turn,sizeof(int),1,ptr);
    fwrite(&s.r_dots,sizeof(int),1,ptr);
    fwrite(&s.s,sizeof(int),1,ptr);
    fwrite(&s.l1,sizeof(int),1,ptr);
    fwrite(&s.l2,sizeof(int),1,ptr);
    fwrite(&s.n,sizeof(int),1,ptr);
    fwrite(&s.p1.score,sizeof(int),1,ptr);
    fwrite(&s.p2.score,sizeof(int),1,ptr);
    fwrite(s.p1.name,sizeof(char),s.l1,ptr);
    fwrite(s.p2.name,sizeof(char),s.l2,ptr);
    fclose(ptr);
}

void save_window(){
    save_win=gtk_window_new(GTK_WINDOW_POPUP);
    gtk_window_set_position(GTK_WINDOW(save_win),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(save_win),"Save game");
    vbox5=gtk_vbox_new(TRUE,2);
    slot1=gtk_button_new_with_label("Slot 1");
    slot2=gtk_button_new_with_label("Slot 2");
    slot3=gtk_button_new_with_label("Slot 3");
    back_save=gtk_button_new_with_label("Back");
    gtk_widget_set_size_request(slot1,300,100);
    saved_label=gtk_label_new("Save Game");
    gtk_box_pack_start(GTK_BOX(vbox5),saved_label,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox5),slot1,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox5),slot2,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox5),slot3,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox5),back_save,TRUE,TRUE,0);
    gtk_container_add(GTK_WINDOW(save_win),vbox5);

}

void save_signal(GtkWidget *widget,GdkEvent *event){
    gtk_widget_show_all(save_win);
}
void back_save_signal(GtkWidget *widget,GdkEvent *event){
    gtk_widget_hide(save_win);
}
void slot1_signal(GtkWidget *widget,GdkEvent *event){
    save_game("slot1.bin");
    saved_label_change();
}
void slot2_signal(GtkWidget *widget,GdkEvent *event){
    save_game("slot2.bin");
    saved_label_change();
}
void slot3_signal(GtkWidget *widget,GdkEvent *event){
    save_game("slot3.bin");
    saved_label_change();
}
void saved_label_change(){
    gtk_label_set_text(GTK_LABEL(saved_label),"Game Saved");
}
void save_win_signals(){
    g_signal_connect(G_OBJECT(save_button), "clicked", G_CALLBACK(save_signal), NULL);
    g_signal_connect(G_OBJECT(back_save), "clicked", G_CALLBACK(back_save_signal), NULL);
    g_signal_connect(G_OBJECT(slot1), "clicked", G_CALLBACK(slot1_signal), NULL);
    g_signal_connect(G_OBJECT(slot2), "clicked", G_CALLBACK(slot2_signal), NULL);
    g_signal_connect(G_OBJECT(slot3), "clicked", G_CALLBACK(slot3_signal), NULL);

}

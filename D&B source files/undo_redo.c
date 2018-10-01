#include "undo_redo.h"

struct move_details moves[100];
struct move_details mredo[100];

int hl=0;
int vl=0;
int i=0;
int k=0;


void set_move_zero(){ //lma bnady 3liha bt3ml set lil move of i b zero h7tag a3mlha b3d kul undo 3shan ams7 el
    moves[i].f=0;    //save el 3mltu w my7slsh conflect b3d kda
    moves[i].hl=0;
    moves[i].m=0;
    moves[i].n=0;
    moves[i].p1score=0;
    moves[i].p2score=0;
    moves[i].r_dots=(g_size+1)*g_size*2;
    moves[i].semif=0;
    moves[i].turn=1;
    moves[i].vl=0;
}
void store (int n,int m){
    i++;
    moves[i].r_dots=remaining_dots;
    moves[i].n=n;
    moves[i].m=m;
    moves[i].semif=box[n][m].semif;
    moves[i].turn=player_turn;
    if(vl==1){                      //msh m7tagen n3ml if l7aga gher dool (vl w hl)
        moves[i].vl=box[n][m].vl;   //b2et el 7agat mlhash lazma el if fa bdal mayb2a shaklha mklk3
    }
    else if(hl==1){
        moves[i].hl=box[n][m].hl;
    }
    moves[i].f=box[n][m].f;
    moves[i].p1score=p1.score;
    moves[i].p2score=p2.score;
}
void undo_v (){
    remaining_dots=moves[i-1].r_dots;
    moves_mredo();   //hna 7atet variable gdeed esmu k 3shan l redo gher el undo w lazm tbda2 mn zero
    k++;//bzwd el k lel redo
    box[moves[i].n][moves[i].m].vl=0;
    gtk_image_set_from_pixbuf(GTK_IMAGE(box[moves[i].n][moves[i].m].v),vblanck);
    if (moves[i].semif==1){
        box[moves[i].n][moves[i].m].semif=0;
    }
    if(box[moves[i].n][moves[i].m].f!=0){
        box[moves[i].n][moves[i].m].f=0;
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[moves[i].n][moves[i].m].b),box_blanck);
    }
    if(box[moves[i].n][(moves[i].m)-1].f!=0){
        box[moves[i].n][(moves[i].m)-1].f=0;
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[moves[i].n][(moves[i].m)-1].b),box_blanck);
    }

    p1.score=moves[i-1].p1score;
    p2.score=moves[i-1].p2score;
    player_turn=moves[i-1].turn;
    set_move_zero();//b3d ma 3mlt undo bms7 el move el kan m3molha save 3shan kant btbwz el dnya sa3at
    i--;
    //t2rebn mghyrtsh tany fl function de w el t7tha, mmkn akon ms7t if zyada aw 7aga bs
}
void moves_mredo (){
    mredo[k+1].n=moves[i].n;
    mredo[k+1].m=moves[i].m;
    mredo[k+1].vl=moves[i].vl;
    mredo[k+1].hl=moves[i].hl;
    mredo[k+1].f=moves[i].f;
    mredo[k+1].semif=moves[i].semif;
    mredo[k+1].p1score=moves[i].p1score;
    mredo[k+1].p2score=moves[i].p2score;
    mredo[k+1].turn=moves[i].turn;
    mredo[k+1].r_dots=moves[i].r_dots;
}
void undo_h(){

    remaining_dots=moves[i-1].r_dots;
    moves_mredo();

   // g_print("%dhl==%dvl===%dturn==%dn==%dm==%df==%dp1==%dp2==%dr==",mredo[k].hl,mredo[k].vl,mredo[k].turn,mredo[k].n,mredo[k].m,mredo[k].f,mredo[k].p1score,mredo[k].p2score,mredo[k].r_dots);
    k++;
    box[moves[i].n][moves[i].m].hl=0;
    gtk_image_set_from_pixbuf(GTK_IMAGE(box[moves[i].n][moves[i].m].h),hblanck);

    if (moves[i].semif==1){
        box[moves[i].n][moves[i].m].semif=0;
    }
    if(box[moves[i].n][moves[i].m].f!=0){
        box[moves[i].n][moves[i].m].f=0;
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[moves[i].n][moves[i].m].b),box_blanck);
    }
    if(box[(moves[i].n)-1][moves[i].m].f!=0){
        box[(moves[i].n)-1][moves[i].m].f=0;
        gtk_image_set_from_pixbuf(GTK_IMAGE(box[(moves[i].n)-1][moves[i].m].b),box_blanck);
    }

    p1.score=moves[i-1].p1score;
    p2.score=moves[i-1].p2score;
    player_turn=moves[i-1].turn;
    set_move_zero();
    i--;
}
void undo_game (){
    if(remaining_dots==0)return; //3shan my3mlsh undo b3d el game over l2n e7na bn3ml hide w 7agat fa hybwz el dnya
    if (moves[i].vl!=0){
        undo_v();
    }
    else if (moves[i].hl!=0){
        undo_h();
    }
    update_labels();//b3ml update lel labels b3d kul undo 3shan yghyr el player turn w yghyr el score w kda
 }
void undo_event(GtkWidget *widget, GdkEvent *event){
    if(remaining_dots==0)return;
    if(num_of_players==1){
        do{
            undo_game();
        }while(player_turn==2);
    }
    else {
        undo_game();
    }
}
void moves_init (){ // mghyrtsh 7aga bs 7aset kda shaklha altaf
    for (i=0;i<60;i++){
        set_move_zero();
    }
    i=0;
}

void init_redo(){
    for(k=0;k<100;k++){
        mredo[k].f=0;    //save el 3mltu w my7slsh conflect b3d kda
        mredo[k].hl=0;
        mredo[k].m=0;
        mredo[k].n=0;
        mredo[k].p1score=0;
        mredo[k].p2score=0;
        mredo[k].r_dots=(g_size+1)*g_size*2;
        mredo[k].semif=0;
        mredo[k].turn=1;
        mredo[k].vl=0;
    }
    k=0;
}
void redo_event(GtkWidget *widget,GdkEvent *event){
    if(remaining_dots==0)return;
    if(k==0)return;
    if(num_of_players==1){
        do{
            redo_game();
        }while(player_turn==2);

    }
    else{
        redo_game();
    }
}
void redo_game (){
    if (mredo[k].vl!=0){
        redo_v();
    }
    else if (mredo[k].hl!=0){
        redo_h();
    }
    // update_labels();
}

void redo_v(){
 vl=1;
    GtkWidget *fbox;
    remaining_dots--;
    gchar *display;
    display=g_strdup_printf(" number of remaining lines : %d   ",remaining_dots);
    gtk_label_set_text(GTK_LABEL(num_of_r_dots),display);
  if (mredo[k].vl==1){
    box[mredo[k].n][mredo[k].m].vl=1;
    gtk_image_set_from_pixbuf(GTK_IMAGE(box[mredo[k].n][mredo[k].m].v),p1_vline);
    fbox=p1_box;
  }
  else if (mredo[k].vl==2){
    box[mredo[k].n][mredo[k].m].vl=2;
    gtk_image_set_from_pixbuf(GTK_IMAGE(box[mredo[k].n][mredo[k].m].v),p2_vline);
    fbox=p2_box;
  }
  semi_filled_check(mredo[k].n,mredo[k].m);

    v_boxes_update(mredo[k].n,mredo[k].m,fbox);
    store(mredo[k].n,mredo[k].m);
    vl=0;

    p1.score=mredo[k].p1score;
    p2.score=mredo[k].p2score;
    //player_turn=mredo[k].turn;
    k--;
}
void redo_h (){
    hl=1;
    GtkWidget *fbox;
    remaining_dots--;
    gchar *display;
    display=g_strdup_printf(" number of remaining lines : %d   ",remaining_dots);
    gtk_label_set_text(GTK_LABEL(num_of_r_dots),display);
  if (mredo[k].hl==1){
    box[mredo[k].n][mredo[k].m].hl=1;
    gtk_image_set_from_pixbuf(GTK_IMAGE(box[mredo[k].n][mredo[k].m].h),p1_hline);
    fbox=p1_box;
  }
  else if (mredo[k].hl==2){
    box[mredo[k].n][mredo[k].m].hl=2;
    gtk_image_set_from_pixbuf(GTK_IMAGE(box[mredo[k].n][mredo[k].m].h),p2_hline);
    fbox=p2_box;
  }
  semi_filled_check(mredo[k].n,mredo[k].m);

    h_boxes_update(mredo[k].n,mredo[k].m,fbox);
    store(mredo[k].n,mredo[k].m);
    hl=0;

    p1.score=mredo[k].p1score;
    p2.score=mredo[k].p2score;
    //player_turn=mredo[k].turn;
    k--;
}


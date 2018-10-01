#include "top_ten.h"

void save_score(struct player p1,struct player p2){
    p1.len=strlen(p1.name)+1;
    p2.len=strlen(p2.name)+1;
    struct player a[10];
    struct player array[10];
    struct player first;
    struct player second;
    int flag=0,flag2=0;
    int d,u=10;
    //memory allocation
    for(d=0;d<10;d++){
        array[d].name=(char*)malloc(sizeof(char)*100);
        a[d].name=(char*)malloc(sizeof(char)*100);
    }
    first.name=(char*)malloc(sizeof(char)*100);
    second.name=(char*)malloc(sizeof(char)*100);
    //reading saved file
    FILE *ptr;
    ptr=fopen("top.txt","r");
    if(!ptr){
        g_printf("no file");
        return ;
    }
    for(d=0;d<u;d++){
        fread(&a[d].len,sizeof(int),1,ptr);
        fread(a[d].name,sizeof(char),a[d].len,ptr);
        fread(&a[d].score,sizeof(int),1,ptr);
        if(!strcmp(p1.name,a[d].name)){
            if(p1.score<a[d].score){
                p1.score=a[d].score;
            }
            a[d].score=-1;
            a[d].name=(char*)malloc(sizeof(char)*100);
            d--;
            u--;
        }
        if(!strcmp(p2.name,a[d].name)){
            if(p2.score<a[d].score){
                p2.score=a[d].score;
            }
            a[d].score=-1;
            a[d].name=(char*)malloc(sizeof(char)*100);
            d--;
            u--;
        }
    }
    fclose(ptr);
    for(d=9;d>u;d--){
        a[d].len=2;
        a[d].name="*";
        a[d].score=-1;
    }
    //setting winner score
    if(num_of_players==1){
        flag2=3;
        first=p1;
    }
    else{
        if(p1.score>p2.score){
            first=p1;
            second=p2;
        }
        else {
            first=p2;
            second=p1;
        }
    }
    //check if player was recorded before
    int x=0;
    //sorting players
    for(d=0;d<10;d++){
        if(first.score>a[x].score && flag ==0){
            array[d]=first;
            if(d<9){
                d++;
                array[d]=a[x];
            }
            flag=1;
        }
        if(second.score>a[x].score && flag ==1 && flag2!=3){
            array[d]=second;
            if(d<9){
                d++;
                array[d]=a[x];
            }
            flag=2;
        }
        else {
            array[d]=a[x];
        }
        x++;
    }
    //saving data to file again
    ptr=fopen("top.txt","w");
    if(!ptr){
        g_printf("no file");
        return ;
    }
    for(d=0;d<10;d++){
        fwrite(&array[d].len,sizeof(int),1,ptr);
        fwrite(array[d].name,sizeof(char),array[d].len,ptr);
        fwrite(&array[d].score,sizeof(int),1,ptr);
    }
    fclose(ptr);
}

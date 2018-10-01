#include "sound_threads.h"
#include "bass.h"
pthread_t bg_sound;
pthread_t s;
pthread_t box_s;
int q =0;
int w=0;
int bg_loop=0;
void *line_change_sound(){
    HSTREAM h;
    //BASS_Init (1, 44100, 0, 0, NULL);
    //BASS_SetDevice(1);
    h=BASS_StreamCreateFile(FALSE,"line2.wav",0,0,0);
    while(1){
        BASS_SetVolume(0.5);
        if(q==1){
            BASS_SetVolume(1);
            BASS_ChannelPlay(h,FALSE);
        }
    }
    pthread_exit(NULL);

}

void *box_fill_sound(){
    HSTREAM h;
    //BASS_Init (1, 44100, 0, 0, NULL);
    //BASS_SetDevice(1);
    h=BASS_StreamCreateFile(FALSE,"tweet.mp3",0,0,0);
    while(1){
        BASS_SetVolume(0.5);
        if(w==2){
            BASS_SetVolume(1);
            BASS_ChannelPlay(h,FALSE);
        }
    }
    pthread_exit(NULL);
}

void *background_music(){
    bg_loop=0;
    HSTREAM h;
    HSTREAM h2;
    //BASS_Init (1, 44100, 0, 0, NULL);
    //BASS_SetDevice(1);
    h=BASS_StreamCreateFile(FALSE,"n.mp3",0,0,BASS_SAMPLE_LOOP);
    h2=BASS_StreamCreateFile(FALSE,"n2.mp3",0,0,BASS_SAMPLE_LOOP);
    //g_printf("%d",BASS_ErrorGetCode());
    BASS_SetVolume(0.25);
    while(1){
        if(bg_loop==0){
            BASS_ChannelPause(h2);
            BASS_ChannelPlay(h,FALSE);
        }
        else if(bg_loop==1){
            BASS_ChannelPause(h);
            BASS_ChannelPlay(h2,FALSE);
        }
    }




    pthread_exit(NULL);
}

void line_change_threads(){
    BASS_Init (1, 44100, 0, 0, NULL);
    BASS_SetDevice(1);
    pthread_create(&s, NULL, line_change_sound, NULL);
    pthread_create(&bg_sound, NULL, background_music, NULL);
    pthread_create(&box_s, NULL, box_fill_sound, NULL);
}

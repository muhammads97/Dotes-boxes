#ifndef SOUND_THREADS_H_INCLUDED
#define SOUND_THREADS_H_INCLUDED
#include <windows.h>
#include <mmsystem.h>
#include <pthread.h>

extern pthread_t bg_sound;
extern pthread_t s;
extern int q;
extern int bg_loop;
extern int w;

void *background_music();
void line_change_threads();
void *line_change_sound();
void *box_fill_sound();

#endif // SOUND_THREADS_H_INCLUDED

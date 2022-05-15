/* Library for programming psychology experiments.
 * -*- mode:c; c-default-style: linux  -*- Time-stamp: <2021-07-01 14:57:41 christophe@pallier.org> 
 *
 * compile-command:  "cc -I/usr/include/SDL2  psychexp.c -lSDL2  -o psychexp.o
 * indent-command: "indent -linux -nut -l120 -pal -nbfda" *
 * Remark: to switch to nvidia mode on dual GPU systems using prime-select on-demand:
 *
 *     __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia ./check_audio_visual_asynchrony
 */

/* Copyright © Christophe Pallier

   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
   The Software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages or other liability, whether in an action of contract, tort or otherwise, arising from, out of or in connection with the software or the use or other dealings in the Software.
*/

#ifndef _PSYCHEXP_H_
#define _PSYCHEXP_H_

#include <stdio.h>
#include <stdlib.h>             // exit
#include <SDL2/SDL.h>


// ARGB codes for colors
extern Uint32 BLACK;
extern Uint32 WHITE;
extern Uint32 RED;
extern Uint32 GREEN;
extern Uint32 BLUE;


/*  Global variables for Video and Audio */
extern SDL_Window* sdlWindow;
extern SDL_Renderer* sdlRenderer;

extern SDL_AudioDeviceID dev;
extern Uint8* wav_buffer;
extern Uint32 wav_length;

/* Utility functions */
extern void create_window(char* title, int width, int height, Uint32 background_color);
extern void destroy_window();
extern void fill_window(Uint32 background_color);
extern void get_refresh_rate();
extern void update_window();
extern void wait(int millisec);
extern Uint64 get_time();              // in ms
extern void wait_for_key_press();
extern int quit_pressed();
extern void draw_black_rectangle(int x, int y, int side_len);
extern void init_audio_device();
extern void close_audio_device();
extern void load_wav_file_in_audio_buffer(char* filename);
extern void play_audio_buffer();
extern int get_remaining_audio();



#endif

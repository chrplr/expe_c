/*  Library for programming psychology experiments.
 * -*- mode:c; c-default-style: linux  -*- Time-stamp: <2021-07-01 14:57:41 christophe@pallier.org> 
 *
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

#include <stdio.h>
#include <stdlib.h>             

#include "psychexp.h"

Uint32 BLACK = 0xFF000000;
Uint32 WHITE = 0xFFFFFFFF;
Uint32 RED = 0xFFFF0000;
Uint32 GREEN = 0xFF00FF00;
Uint32 BLUE = 0xFF0000FF;

/*  Global variables for Video and Audio */
SDL_Window* sdlWindow = NULL;
SDL_Renderer* sdlRenderer = NULL;

SDL_AudioDeviceID dev;
Uint8* wav_buffer = NULL;
Uint32 wav_length = 0;


void create_window(char* title, int width, int height, Uint32 background_color)
{
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
                printf("SDL video initialization failed: %s", SDL_GetError());
                exit(EXIT_FAILURE);
        }

        sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

        if (sdlWindow == NULL) {
                printf("SDL_CreateWindow failed: %s", SDL_GetError());
                exit(EXIT_FAILURE);
        }

        sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (sdlRenderer == NULL) {
                printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
                exit(EXIT_FAILURE);
        }

        uint8_t byte3 = (uint8_t) (background_color >> 24);
        uint8_t byte2 = (uint8_t) (background_color >> 16);
        uint8_t byte1 = (uint8_t) (background_color >> 8);
        uint8_t byte0 = (uint8_t) background_color;

        SDL_SetRenderDrawColor(sdlRenderer, byte0, byte1, byte2, byte3);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderPresent(sdlRenderer);

        SDL_SetEventFilter(is_relevant_event, NULL);
}

void update_window()
{
        SDL_RenderPresent(sdlRenderer);
}

void fill_window(Uint32 background_color)
{
        uint8_t byte3 = (uint8_t) (background_color >> 24);
        uint8_t byte2 = (uint8_t) (background_color >> 16);
        uint8_t byte1 = (uint8_t) (background_color >> 8);
        uint8_t byte0 = (uint8_t) background_color;

        SDL_SetRenderDrawColor(sdlRenderer, byte0, byte1, byte2, byte3);
        SDL_RenderClear(sdlRenderer);
}

void destroy_window()
{
        SDL_DestroyRenderer(sdlRenderer);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
}

void close_audio_device()
{
        if (!dev) {
                SDL_CloseAudioDevice(dev);
        }
        if (!wav_buffer) {
                SDL_FreeWAV(wav_buffer);
        }
}

void wait(int millisec)
{
        SDL_Delay(millisec);
}

Uint64 get_time()
{
        static Uint64 start = 0;
        Uint64 now = (SDL_GetPerformanceCounter() * 1000) / SDL_GetPerformanceFrequency();
        if (start == 0) {
                start = now;
        }
        return now - start;
}

void draw_black_rectangle(int x, int y, int side_len)
{
        SDL_Rect r;
        r.x = x - side_len / 2;
        r.y = y - side_len / 2;
        r.w = side_len;
        r.h = side_len;

        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderFillRect(sdlRenderer, &r);
}

void init_audio_device()
{
        if (SDL_Init(SDL_INIT_AUDIO) != 0) {
                printf("SDL audio initialization failed: %s", SDL_GetError());
                exit(EXIT_FAILURE);
        }

        SDL_AudioSpec desired_specs;
        SDL_memset(&desired_specs, 0, sizeof(desired_specs));   /* or SDL_zero(want) */
        desired_specs.freq = 44100;
        desired_specs.format = AUDIO_S16LSB;
        desired_specs.channels = 1;
        desired_specs.samples = 256;

        if ((dev = SDL_OpenAudioDevice(NULL, 0, &desired_specs, 0, SDL_AUDIO_ALLOW_FORMAT_CHANGE)) == 0) {
                SDL_Log("Failed to initialize audio device: %s", SDL_GetError());
                exit(1);
        }
}

void load_wav_file_in_audio_buffer(char* filename)
{
        SDL_AudioSpec wav_spec;

        free(wav_buffer);       // deallocate previously allocated  buffer safe on NULL

        if (SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL) {
                SDL_Log("Failed to load wav file %s: %s", filename, SDL_GetError());
                exit(1);
        }

        if ((wav_spec.freq != 44100) || wav_spec.channels != 1) {
                SDL_Log("The sound file should have a single channel (mono) and a sampling freq of 44100 Hz");
                exit(1);
        }

        if (SDL_QueueAudio(dev, wav_buffer, wav_length) != 0) {
                SDL_Log("%s", SDL_GetError());
        }
}

void play_audio_buffer()
{
        SDL_PauseAudioDevice(dev, 0);   // unpause
        printf(".\n");
}

void free_audio_buffer()
{
        if (!wav_buffer)
                SDL_FreeWAV(wav_buffer);
}

int get_remaining_audio()
{
        return SDL_GetQueuedAudioSize(dev);
}

void wait_for_key_press()
{
        SDL_Event event;
        int running = 1;

        while (running) {
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                        case SDL_QUIT:
                                running = 0;
                                break;
                        case SDL_KEYDOWN:
                                running = 0;
                                break;
                        }

                }
                SDL_Delay(100);
        }
}

int quit_pressed()
{
        SDL_Event event;
        int quit_event = 0;

        while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                        quit_event = 1;
                        break;
                }
        }
        return quit_event;
}

/* import SDL renderer must have been initialized with SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC */
void get_refresh_rate()
{
        for (int i = 0; i < 100; i++)
        {
                Uint64 start = SDL_GetPerformanceCounter();
                draw_black_rectangle(100, 100, 50);
                update_window();
                Uint64 end = SDL_GetPerformanceCounter();
                float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
                printf("Time between succssive frames:  %.2fms\n", 1000*elapsed);
        }

}


int is_relevant_event(void* nada, SDL_Event * event)
/* we want to filter out any event which is not  Close window or keypress */
{
        if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
                return 1;
        return 0;
}

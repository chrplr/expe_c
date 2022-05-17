/* Displays a square and plays a sound in order to check for potential latency
 * -*- mode:c; c-default-style: linux  -*- Time-stamp: <2021-07-01 14:57:41 christophe@pallier.org> 
 *
 * compile-command:  "cc -I..  test_psychexp.c -lSDL2 -lpsychexp  -o test_psychexp"
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
#include <stdlib.h>             // exit
#include <argp.h>
#include <SDL2/SDL.h>

#include <psychexp.h>

static char doc[] = "A loop displaying a square followed by a sound, to test audio-visual asynchrony latencies";
const char* argp_program_version = "1.0";
const char* argp_program_bug_address = "<christophe@pallier.org>";

struct arguments {
        int period, soa, duration;
};

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;
int center_x = WINDOW_WIDTH / 2;
int center_y = WINDOW_HEIGHT / 2;

static struct argp_option options[] = {
        {"period", 'p', "DURATION", 0, "time between two successive squares (in ms)"},
        {"soa", 's', "DURATION", 0,
         "stimuli onset asynchrony: desired delay between beginning of display and sound (in ms)"},
        {"duration", 'd', "DURATION", 0, " duration of display of the square (in ms) "},
        {0}
};

static error_t parse_opt(int key, char* arg, struct argp_state* state)
{
        struct arguments* arguments = state->input;

        switch (key) {
        case 'p':
                arguments->period = atoi(arg);
                break;
        case 's':
                arguments->soa = atoi(arg);
                break;
        case 'd':
                arguments->duration = atoi(arg);
                break;
        default:
                return ARGP_ERR_UNKNOWN;
        }
        return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

int main(int argc, char* argv[])
{
        struct arguments arguments;
        arguments.period = 3000;
        arguments.duration = 200;
        arguments.soa = 0;
        argp_parse(&argp, argc, argv, 0, 0, &arguments);
        SDL_Log("#Target: period=%d, duration=%d, soa=%d\n", arguments.period, arguments.duration, arguments.soa);

        int rect_size = 600;
        int loop = 0;
        Uint64 t0 = 0, t1 = 0, t2 = 0, t3 = 0, t4 = 0;

        create_window("AV asynchrony check", WINDOW_WIDTH, WINDOW_HEIGHT, WHITE);
        init_audio_device();

        fill_window(WHITE);
        update_window();
        wait(1000);             // if not, the refresh rate is weird
        get_refresh_rate();
        get_time();

        SDL_Log("loop\tvideo_onset\tvideo_offset\taudio_onset\tdiff\n");
        while (!quit_pressed()) {
                loop++;
                wait(arguments.period - (get_time() - t0));
                t0 = get_time();

                load_wav_file_in_audio_buffer("pluck.wav");
                t1 = get_time();

                draw_black_rectangle(center_x, center_y, rect_size);
                update_window();
                t2 = get_time();

                if (arguments.soa < arguments.duration) {
                        wait(arguments.soa);
                        play_audio_buffer();
                        t3 = get_time();
                        wait(arguments.duration - arguments.soa);
                        fill_window(WHITE);
                        update_window();
                        t4 = get_time();
                } else {
                        wait(arguments.duration);
                        fill_window(WHITE);
                        update_window();
                        t4 = get_time();
                        wait(arguments.soa - arguments.duration);
                        play_audio_buffer();
                        t3 = get_time();
                }

                while (get_remaining_audio() > 0) {
                        SDL_Delay(10);
                }
                SDL_PauseAudioDevice(dev, 1);   // oddity: if you do not pause, the soa will be messed up

                SDL_Log("%4d\t%ld\t%ld\t%ld\t%ld\n", loop, t2, t4, t3, t3 - t2);
        }

        close_audio_device();
        destroy_window();

        return EXIT_SUCCESS;
}

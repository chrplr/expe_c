/* loop over SDL_Delay() to check granularity and potential latencies.
 *
 * Time-stamp: <2021-12-17 14:49:04 christophe@pallier.org>
 *
 * Compile with:
 *    gcc -Wall -g  -std=c99  -O3 -I/usr/include/SDL2 -o check_timing_latencies check_timing_latencies.c -lSDL2 -lpthread
 */


#include <stdio.h>
#include <argp.h>
#include <SDL.h>  // SDL2

const char *argp_program_version = "check_timing_latencies";
const char *argp_program_bug_address = "<christophe@pallier.org>";
static char doc[] = "Loops for a given amount of time around SDL_Delay to check granularity and potential latencies.\nOutputs the actual times spent in the loop.";


struct arguments
{
     int duration, delta, silent;
};

static struct argp_option options[] = {
     {"duration",  't', "TIME",      0,  "Time (wall clock) of running (in msec)" },
     {"delay",    'd', "DELAY",      0,  "Target delay within each loop (in msec)" },
     {"silent",   's', 0,      0,  "Suppress the full listing of delays. Only prints the summary stats" },
     { 0 }
};


static error_t
parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
  {
  case 'q': case 's':
       arguments->silent = 1;
       break;
  case 't':
       arguments->duration = atoi(arg);
       break;
  case 'd':
       arguments->delta = atoi(arg);
       break;
  default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

/* clock functions */

Uint64 start_time = 0;
Uint64 ticks_per_sec = 0;

void
reset_wall_clock()
{
     ticks_per_sec = SDL_GetPerformanceFrequency();
     start_time = SDL_GetPerformanceCounter();
}

double
wall_clock()
{
     return (double)((SDL_GetPerformanceCounter() - start_time) * 1000) / ticks_per_sec;
}



int
main(int argc, char *argv[])
{
     struct arguments arguments;

     /* Default values. */
     arguments.duration = 60000; // total duration of sampling (in milliseconds)
     arguments.delta = 1;  // target delay within each loop (in milliseconds)
     arguments.silent = 0;

     argp_parse (&argp, argc, argv, 0, 0, &arguments);

     fprintf(stderr, "Looping for %d msec with target waiting time of %d msec...\n", (int)(arguments.duration), arguments.delta);

     SDL_Init(SDL_INIT_TIMER);
     reset_wall_clock();

     int maxsamples = arguments.duration / arguments.delta;
     double times[maxsamples + 1];
     double delta[maxsamples];

     int i = 0;
     while ((times[i++] = wall_clock()) < arguments.duration) {
          SDL_Delay(arguments.delta);
     }

     int n_samples = i - 1;  // 'i - 1' because we count intervals

     double min = arguments.duration;
     double max = 0.0;
     double sum = 0.0;

     for (int i = 0; i < n_samples; i++) {
          delta[i] = times[i + 1] - times[i];
          if (delta[i] < min) min = delta[i];
          if (delta[i] > max) max = delta[i];
          sum += delta[i];
     }

     fprintf(stderr, "n = %d\nmin = %f\nmean=%f\nmax=%f\n", n_samples, min, sum / n_samples, max);

     if (! arguments.silent)
          for (int i = 0; i < n_samples - 1; i++) {
               printf("%f\n", delta[i]);
          }

     SDL_Quit();
     return 0;
}

/* Time-stamp: <2021-05-31 11:52:48 christophe@pallier.org> */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <search.h>
#include <assert.h>

#include <SDL.h>
#include <SDL_image.h>

#include "lizzie.xpm"

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

char * const pics[] =
  {
    "lizzie_1024x768.jpg",
    "rainbow_1024x768.jpg"
  };



typedef struct {
  int onset;
  int duration;
  enum { IMAGE, SOUND } type;
  char* name;
} Trial;

const Trial trials[] = {
  {1000, 200, IMAGE, "lizzie_1024x768.jpg"},
  {2000, 100, IMAGE, "lizzie_1024x768.jpg"},
  {3000, 500, IMAGE, "rainbow_1024x768.jpg"}
};



void display_splash(int delay_in_ms) {
     SDL_Surface* image = IMG_ReadXPMFromArray(lizzie_xpm);
     SDL_Texture* texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
     assert (texture != NULL);
     SDL_RenderCopy(sdlRenderer, texture, NULL, NULL);
     SDL_RenderPresent(sdlRenderer);
     SDL_Delay(delay_in_ms);
     SDL_FreeSurface(image);
     SDL_DestroyTexture(texture);
     SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
     SDL_RenderClear(sdlRenderer);
     SDL_RenderPresent(sdlRenderer);
}


void load_image_and_create_texture(char *filename)
/* load a graphic file, create a texture, and add an Entry in the global hashtable linking the file name to the texture */
{
  printf("adding %s to the hash\n", filename);
  SDL_Surface *image = IMG_Load(filename);
  assert (image != NULL);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
  assert (texture != NULL);

  ENTRY item;
  item.key = filename;
  item.data = texture;

  if (hsearch(item, ENTER) == NULL) {
       perror("Creating associaton image -> texture");
       exit(1);
  };

  SDL_FreeSurface(image);
}


SDL_Texture* get_texture(char *name)
{

     ENTRY item;
     item.key = name;

     ENTRY *res = hsearch(item, FIND);

     if (res == NULL) {
       perror("searching hash");
       return NULL;
     } else {
       return (SDL_Texture*)(res->data);
     }
}

Uint64 start_time = 0;

void reset_wall_clock()
{
  start_time = SDL_GetPerformanceCounter();
}

double wall_clock()
{
  return (double)((SDL_GetPerformanceCounter() - start_time) * 1000) / SDL_GetPerformanceFrequency();
}

int main()
{

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_JPG);


    sdlWindow = SDL_CreateWindow("Streaming",
                                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    display_splash(1000);
    SDL_Delay(1000);

    hcreate(50);
    int nstims = sizeof(pics)/sizeof(pics[0]);
    printf("%d images to load\n", nstims);


    /* Preload stimuli */
    for (int i=0; i < nstims; i++)
         load_image_and_create_texture(pics[i]);

    /* start stimulation */
    reset_wall_clock();

    int ntrials = sizeof(trials) / sizeof(Trial);

    for (int i=0, quit=0; (i < ntrials) & !quit; i++) {
      while (wall_clock() < trials[i].onset)
        SDL_Delay(10);

      SDL_Texture *tex = get_texture(trials[i].name);

      double time1, time2, time3;
      time1 = wall_clock();

          SDL_RenderCopy(sdlRenderer, tex, NULL, NULL);
          SDL_RenderPresent(sdlRenderer);
          time2 = wall_clock();

          SDL_Delay(trials[i].duration);

          SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
          SDL_RenderClear(sdlRenderer);
          SDL_RenderPresent(sdlRenderer);
          time3 = wall_clock();

          SDL_Event event;

          while (SDL_PollEvent(&event)) {

            switch (event.type)
              {
              case SDL_QUIT:
                quit = 1;
                break;
              case SDL_KEYDOWN:
                quit = 1;
                break;
              }
          }

          printf("%lf %lf %lf\n", time1, time2, time3);
        }

    SDL_Delay(500);
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);

    IMG_Quit();
    SDL_Quit();

    return 0;
}

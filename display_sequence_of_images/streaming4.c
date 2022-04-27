/* Time-stamp: <2021-12-12 18:21:04 christophe@pallier.org> */
/* gcc -Wall -g -O3 -I/usr/include/SDL2 -o streaming4 streaming4.c -lSDL2 -lSDL2_image -lpthread -lm */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <search.h>
#include <assert.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>

#include "lizzie.xpm"

SDL_Window *sdlWindow;
SDL_Renderer *sdlRenderer;

const int FULLSCREEN = 1;


const int MAX_DIFFERENT_IMAGES = 1024;
//const int SCREEN_WIDTH = PIC_WIDTH;
//const int SCREEN_HEIGHT = PIC_WIDTH;
const int SCREEN_WIDTH = 1900;
const int SCREEN_HEIGHT = 1080;
const int PIC_WIDTH = 572;

const char* PICS_FOLDER = "images";

char * const pics[] =
{
        "1_15.png",
        "1_30.png",
        "1_315.png",
        "1_330.png",
        "1_345.png",
        "1_45.png",
        "2_15.png",
        "2_30.png",
        "2_315.png",
        "2_330.png",
        "2_345.png",
        "2_45.png",
        "3_15.png",
        "3_30.png",
        "3_315.png",
        "3_330.png",
        "3_345.png",
        "3_45.png",
        "4_15.png",
        "4_30.png",
        "4_315.png",
        "4_330.png",
        "4_345.png",
        "4_45.png",
        "5_15.png",
        "5_30.png",
        "5_315.png",
        "5_330.png",
        "5_345.png",
        "5_45.png",
        "6_15.png",
        "6_30.png",
        "6_315.png",
        "6_330.png",
        "6_345.png",
        "6_45.png",
        "fixation_cross.png",
        "instructions_autre.png",
        "instructions_up.png"
};

typedef struct {
  int onset;
  int duration;
  char* name;
} Trial;



// Reads a file and returns the number of lines in it, ignoring empty lines
unsigned int count_lines(FILE *file)
{
    unsigned int  lines = 0;
    int           c = '\0';
    int           pc = '\n';

    while (c = fgetc(file), c != EOF)
    {
        if (c == '\n'  &&  pc != '\n')
            lines++;
        pc = c;
    }
    if (pc != '\n')
        lines++;

    return lines;
}

//int read_trials()

const Trial trials[] = {
 {0, 0, "instructions_up.png"},
 {3000, 0, "6_30.png"},
 {3200, 0, "fixation_cross.png"},
 {4500, 0, "1_330.png"},
 {4700, 0, "fixation_cross.png"},
 {6000, 0, "2_345.png"},
 {6200, 0, "fixation_cross.png"},
 {7500, 0, "4_45.png"},
 {7700, 0, "fixation_cross.png"},
 {9000, 0, "5_315.png"},
 {9200, 0, "fixation_cross.png"},
 {10500, 0, "2_330.png"},
 {10700, 0, "fixation_cross.png"},
 {12000, 0, "3_15.png"},
 {12200, 0, "fixation_cross.png"},
 {13500, 0, "1_15.png"},
 {13700, 0, "fixation_cross.png"},
 {15000, 0, "fixation_cross.png"},
 {23000, 0, "instructions_up.png"},
 {26000, 0, "4_45.png"},
 {26200, 0, "fixation_cross.png"},
 {27500, 0, "5_345.png"},
 {27700, 0, "fixation_cross.png"},
 {29000, 0, "1_330.png"},
 {29200, 0, "fixation_cross.png"},
 {30500, 0, "4_315.png"},
 {30700, 0, "fixation_cross.png"},
 {32000, 0, "5_30.png"},
 {32200, 0, "fixation_cross.png"},
 {33500, 0, "2_30.png"},
 {33700, 0, "fixation_cross.png"},
 {35000, 0, "3_15.png"},
 {35200, 0, "fixation_cross.png"},
 {36500, 0, "6_315.png"},
 {36700, 0, "fixation_cross.png"},
 {38000, 0, "fixation_cross.png"},
 {44000, 0, "instructions_autre.png"},
 {47000, 0, "6_330.png"},
 {47200, 0, "fixation_cross.png"},
 {48500, 0, "6_345.png"},
 {48700, 0, "fixation_cross.png"},
 {50000, 0, "1_15.png"},
 {50200, 0, "fixation_cross.png"},
 {51500, 0, "2_45.png"},
 {51700, 0, "fixation_cross.png"},
 {53000, 0, "5_30.png"},
 {53200, 0, "fixation_cross.png"},
 {54500, 0, "4_330.png"},
 {54700, 0, "fixation_cross.png"},
 {56000, 0, "1_315.png"},
 {56200, 0, "fixation_cross.png"},
 {57500, 0, "3_15.png"},
 {57700, 0, "fixation_cross.png"},
 {59000, 0, "fixation_cross.png"},
 {67000, 0, "instructions_autre.png"},
 {70000, 0, "2_15.png"},
 {70200, 0, "fixation_cross.png"},
 {71500, 0, "2_330.png"},
 {71700, 0, "fixation_cross.png"},
 {73000, 0, "6_345.png"},
 {73200, 0, "fixation_cross.png"},
 {74500, 0, "1_45.png"},
 {74700, 0, "fixation_cross.png"},
 {76000, 0, "5_15.png"},
 {76200, 0, "fixation_cross.png"},
 {77500, 0, "4_315.png"},
 {77700, 0, "fixation_cross.png"},
 {79000, 0, "3_345.png"},
 {79200, 0, "fixation_cross.png"},
 {80500, 0, "4_30.png"},
 {80700, 0, "fixation_cross.png"},
 {82000, 0, "fixation_cross.png"},
 {90000, 0, "instructions_up.png"},
 {93000, 0, "3_45.png"},
 {93200, 0, "fixation_cross.png"},
 {94500, 0, "1_315.png"},
 {94700, 0, "fixation_cross.png"},
 {96000, 0, "4_345.png"},
 {96200, 0, "fixation_cross.png"},
 {97500, 0, "5_30.png"},
 {97700, 0, "fixation_cross.png"},
 {99000, 0, "5_45.png"},
 {99200, 0, "fixation_cross.png"},
 {100500, 0, "4_330.png"},
 {100700, 0, "fixation_cross.png"},
 {102000, 0, "6_15.png"},
 {102200, 0, "fixation_cross.png"},
 {103500, 0, "2_315.png"},
 {103700, 0, "fixation_cross.png"},
 {105000, 0, "fixation_cross.png"},
 {113000, 0, "instructions_autre.png"},
 {116000, 0, "1_315.png"},
 {116200, 0, "fixation_cross.png"},
 {117500, 0, "2_30.png"},
 {117700, 0, "fixation_cross.png"},
 {119000, 0, "5_315.png"},
 {119200, 0, "fixation_cross.png"},
 {120500, 0, "2_45.png"},
 {120700, 0, "fixation_cross.png"},
 {122000, 0, "3_345.png"},
 {122200, 0, "fixation_cross.png"},
 {123500, 0, "1_30.png"},
 {123700, 0, "fixation_cross.png"},
 {125000, 0, "6_330.png"},
 {125200, 0, "fixation_cross.png"},
 {126500, 0, "4_15.png"},
 {126700, 0, "fixation_cross.png"},
 {128000, 0, "fixation_cross.png"},
 {134000, 0, "instructions_up.png"},
 {137000, 0, "3_30.png"},
 {137200, 0, "fixation_cross.png"},
 {138500, 0, "2_345.png"},
 {138700, 0, "fixation_cross.png"},
 {140000, 0, "6_315.png"},
 {140200, 0, "fixation_cross.png"},
 {141500, 0, "1_315.png"},
 {141700, 0, "fixation_cross.png"},
 {143000, 0, "3_15.png"},
 {143200, 0, "fixation_cross.png"},
 {144500, 0, "5_15.png"},
 {144700, 0, "fixation_cross.png"},
 {146000, 0, "4_330.png"},
 {146200, 0, "fixation_cross.png"},
 {147500, 0, "5_45.png"},
 {147700, 0, "fixation_cross.png"},
 {149000, 0, "fixation_cross.png"},
 {155000, 0, "instructions_up.png"},
 {158000, 0, "2_345.png"},
 {158200, 0, "fixation_cross.png"},
 {159500, 0, "1_330.png"},
 {159700, 0, "fixation_cross.png"},
 {161000, 0, "6_315.png"},
 {161200, 0, "fixation_cross.png"},
 {162500, 0, "2_45.png"},
 {162700, 0, "fixation_cross.png"},
 {164000, 0, "5_345.png"},
 {164200, 0, "fixation_cross.png"},
 {165500, 0, "4_30.png"},
 {165700, 0, "fixation_cross.png"},
 {167000, 0, "3_45.png"},
 {167200, 0, "fixation_cross.png"},
 {168500, 0, "4_15.png"},
 {168700, 0, "fixation_cross.png"},
 {170000, 0, "fixation_cross.png"},
 {176000, 0, "instructions_autre.png"},
 {179000, 0, "1_30.png"},
 {179200, 0, "fixation_cross.png"},
 {180500, 0, "3_315.png"},
 {180700, 0, "fixation_cross.png"},
 {182000, 0, "5_15.png"},
 {182200, 0, "fixation_cross.png"},
 {183500, 0, "2_330.png"},
 {183700, 0, "fixation_cross.png"},
 {185000, 0, "2_330.png"},
 {185200, 0, "fixation_cross.png"},
 {186500, 0, "4_30.png"},
 {186700, 0, "fixation_cross.png"},
 {188000, 0, "4_45.png"},
 {188200, 0, "fixation_cross.png"},
 {189500, 0, "6_345.png"},
 {189700, 0, "fixation_cross.png"},
 {191000, 0, "fixation_cross.png"},
 {195000, 0, "instructions_autre.png"},
 {198000, 0, "2_30.png"},
 {198200, 0, "fixation_cross.png"},
 {199500, 0, "3_315.png"},
 {199700, 0, "fixation_cross.png"},
 {201000, 0, "1_15.png"},
 {201200, 0, "fixation_cross.png"},
 {202500, 0, "6_315.png"},
 {202700, 0, "fixation_cross.png"},
 {204000, 0, "4_45.png"},
 {204200, 0, "fixation_cross.png"},
 {205500, 0, "5_330.png"},
 {205700, 0, "fixation_cross.png"},
 {207000, 0, "1_15.png"},
 {207200, 0, "fixation_cross.png"},
 {208500, 0, "6_345.png"},
 {208700, 0, "fixation_cross.png"},
 {210000, 0, "fixation_cross.png"},
 {218000, 0, "instructions_autre.png"},
 {221000, 0, "5_30.png"},
 {221200, 0, "fixation_cross.png"},
 {222500, 0, "1_345.png"},
 {222700, 0, "fixation_cross.png"},
 {224000, 0, "3_45.png"},
 {224200, 0, "fixation_cross.png"},
 {225500, 0, "5_330.png"},
 {225700, 0, "fixation_cross.png"},
 {227000, 0, "2_345.png"},
 {227200, 0, "fixation_cross.png"},
 {228500, 0, "6_15.png"},
 {228700, 0, "fixation_cross.png"},
 {230000, 0, "4_315.png"},
 {230200, 0, "fixation_cross.png"},
 {231500, 0, "3_15.png"},
 {231700, 0, "fixation_cross.png"},
 {233000, 0, "fixation_cross.png"},
 {241000, 0, "instructions_up.png"},
 {244000, 0, "4_30.png"},
 {244200, 0, "fixation_cross.png"},
 {245500, 0, "5_330.png"},
 {245700, 0, "fixation_cross.png"},
 {247000, 0, "3_30.png"},
 {247200, 0, "fixation_cross.png"},
 {248500, 0, "4_345.png"},
 {248700, 0, "fixation_cross.png"},
{250000, 0, "6_45.png"},
{250200, 0, "fixation_cross.png"},
 {251500, 0, "2_315.png"},
 {251700, 0, "fixation_cross.png"},
 {253000, 0, "5_345.png"},
 {253200, 0, "fixation_cross.png"},
 {254500, 0, "1_15.png"},
 {254700, 0, "fixation_cross.png"},
 {256000, 0, "fixation_cross.png"},
 {260000, 0, "instructions_up.png"},
 {263000, 0, "4_330.png"},
 {263200, 0, "fixation_cross.png"},
 {264500, 0, "2_30.png"},
 {264700, 0, "fixation_cross.png"},
 {266000, 0, "1_30.png"},
 {266200, 0, "fixation_cross.png"},
 {267500, 0, "5_45.png"},
 {267700, 0, "fixation_cross.png"},
 {269000, 0, "3_345.png"},
 {269200, 0, "fixation_cross.png"},
 {270500, 0, "6_330.png"},
 {270700, 0, "fixation_cross.png"},
 {272000, 0, "4_315.png"},
 {272200, 0, "fixation_cross.png"},
 {273500, 0, "2_15.png"},
 {273700, 0, "fixation_cross.png"},
 {275000, 0, "fixation_cross.png"},
 {283000, 0, "instructions_up.png"},
 {286000, 0, "6_15.png"},
 {286200, 0, "fixation_cross.png"},
 {287500, 0, "3_45.png"},
 {287700, 0, "fixation_cross.png"},
 {289000, 0, "4_15.png"},
 {289200, 0, "fixation_cross.png"},
 {290500, 0, "1_30.png"},
 {290700, 0, "fixation_cross.png"},
 {292000, 0, "2_315.png"},
 {292200, 0, "fixation_cross.png"},
 {293500, 0, "5_345.png"},
 {293700, 0, "fixation_cross.png"},
 {295000, 0, "5_330.png"},
 {295200, 0, "fixation_cross.png"},
 {296500, 0, "3_330.png"},
 {296700, 0, "fixation_cross.png"},
 {298000, 0, "fixation_cross.png"},
 {302000, 0, "instructions_autre.png"},
 {305000, 0, "4_15.png"},
 {305200, 0, "fixation_cross.png"},
 {306500, 0, "3_315.png"},
 {306700, 0, "fixation_cross.png"},
 {308000, 0, "1_330.png"},
 {308200, 0, "fixation_cross.png"},
 {309500, 0, "1_15.png"},
 {309700, 0, "fixation_cross.png"},
 {311000, 0, "6_315.png"},
 {311200, 0, "fixation_cross.png"},
 {312500, 0, "2_345.png"},
 {312700, 0, "fixation_cross.png"},
 {314000, 0, "5_30.png"},
 {314200, 0, "fixation_cross.png"},
 {315500, 0, "6_45.png"},
 {315700, 0, "fixation_cross.png"},
 {317000, 0, "fixation_cross.png"},
 {321000, 0, "instructions_autre.png"},
 {324000, 0, "1_45.png"},
 {324200, 0, "fixation_cross.png"},
 {325500, 0, "6_315.png"},
 {325700, 0, "fixation_cross.png"},
 {327000, 0, "6_345.png"},
 {327200, 0, "fixation_cross.png"},
 {328500, 0, "5_330.png"},
 {328700, 0, "fixation_cross.png"},
 {330000, 0, "3_315.png"},
 {330200, 0, "fixation_cross.png"},
 {331500, 0, "4_15.png"},
 {331700, 0, "fixation_cross.png"},
 {333000, 0, "2_30.png"},
 {333200, 0, "fixation_cross.png"},
 {334500, 0, "3_45.png"},
 {334700, 0, "fixation_cross.png"},
 {336000, 0, "fixation_cross.png"},
 {340000, 0, "instructions_autre.png"},
 {343000, 0, "4_30.png"},
 {343200, 0, "fixation_cross.png"},
 {344500, 0, "5_30.png"},
 {344700, 0, "fixation_cross.png"},
 {346000, 0, "6_315.png"},
 {346200, 0, "fixation_cross.png"},
 {347500, 0, "3_345.png"},
 {347700, 0, "fixation_cross.png"},
 {349000, 0, "2_45.png"},
 {349200, 0, "fixation_cross.png"},
 {350500, 0, "6_330.png"},
 {350700, 0, "fixation_cross.png"},
 {352000, 0, "4_330.png"},
 {352200, 0, "fixation_cross.png"},
 {353500, 0, "1_15.png"},
 {353700, 0, "fixation_cross.png"},
 {355000, 0, "fixation_cross.png"},
 {361000, 0, "instructions_up.png"},
 {364000, 0, "2_315.png"},
 {364200, 0, "fixation_cross.png"},
 {365500, 0, "3_15.png"},
 {365700, 0, "fixation_cross.png"},
 {367000, 0, "1_45.png"},
 {367200, 0, "fixation_cross.png"},
 {368500, 0, "6_345.png"},
 {368700, 0, "fixation_cross.png"},
 {370000, 0, "4_345.png"},
 {370200, 0, "fixation_cross.png"},
 {371500, 0, "1_330.png"},
 {371700, 0, "fixation_cross.png"},
 {373000, 0, "5_30.png"},
 {373200, 0, "fixation_cross.png"},
 {374500, 0, "6_15.png"},
 {374700, 0, "fixation_cross.png"},
 {376000, 0, "fixation_cross.png"},
 {382000, 0, "instructions_autre.png"},
 {385000, 0, "4_315.png"},
 {385200, 0, "fixation_cross.png"},
 {386500, 0, "5_15.png"},
 {386700, 0, "fixation_cross.png"},
 {388000, 0, "5_345.png"},
 {388200, 0, "fixation_cross.png"},
 {389500, 0, "4_30.png"},
 {389700, 0, "fixation_cross.png"},
 {391000, 0, "1_315.png"},
 {391200, 0, "fixation_cross.png"},
 {392500, 0, "2_45.png"},
 {392700, 0, "fixation_cross.png"},
 {394000, 0, "3_30.png"},
 {394200, 0, "fixation_cross.png"},
 {395500, 0, "6_330.png"},
 {395700, 0, "fixation_cross.png"},
 {397000, 0, "fixation_cross.png"},
 {401000, 0, "instructions_up.png"},
 {404000, 0, "1_45.png"},
 {404200, 0, "fixation_cross.png"},
 {405500, 0, "3_330.png"},
 {405700, 0, "fixation_cross.png"},
 {407000, 0, "5_330.png"},
 {407200, 0, "fixation_cross.png"},
 {408500, 0, "2_315.png"},
 {408700, 0, "fixation_cross.png"},
 {410000, 0, "4_15.png"},
 {410200, 0, "fixation_cross.png"},
 {411500, 0, "4_30.png"},
 {411700, 0, "fixation_cross.png"},
 {413000, 0, "6_345.png"},
 {413200, 0, "fixation_cross.png"},
 {414500, 0, "2_45.png"},
 {414700, 0, "fixation_cross.png"},
 {416000, 0, "fixation_cross.png"},
 {420000, 0, "fixation_cross.png"}
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


void load_image_and_create_texture(const char *filename, const char *folder)
/* load a graphic file, create a texture, and add an Entry in the global hashtable linking the file name to the texture */
{
        char path[256];
        snprintf(path, 255, "%s/%s", folder, filename);
        printf("adding %s to the hash\n", path);
        SDL_Surface *image = IMG_Load(path);
        assert (image != NULL);

        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
        assert (texture != NULL);

        ENTRY item;
        item.key = filename;
        item.data = texture;

        if (hsearch(item, ENTER) == NULL) {
                perror("Creating association image -> texture");
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


SDL_Keycode keyboard_wait()
{
        SDL_Event event;
        SDL_Keycode key = 0;
        int quit = 0;

        while ((!quit) && SDL_WaitEvent(&event)) {
                switch(event.type) {
                case SDL_KEYDOWN:
                        printf( "Key press detected\n" );
                        key = event.key.keysym.sym;
                        quit = 1;
                        break;
                case SDL_QUIT:
                     SDL_Quit();
                     exit(1);
                default:
                        break;
                }
        }
        return key;
}

SDL_Keycode monitor_keyboard()
{
     SDL_Event event;
     SDL_Keycode key = 0;

     while (SDL_PollEvent(&event)) {
          switch (event.type) {
          case SDL_QUIT:
               key = SDLK_ESCAPE;
               break;
          case SDL_KEYDOWN:
               key = event.key.keysym.sym;
               printf("%d pressed at %.0f\n", key, round(wall_clock()));
               break;
          }
     }

     return key;
}

void init()
{
     SDL_Init(SDL_INIT_VIDEO);
     SDL_Init(SDL_INIT_TIMER);
     IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

     if (FULLSCREEN)
          sdlWindow = SDL_CreateWindow("Streaming", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
     else
          sdlWindow = SDL_CreateWindow("Streaming", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

     sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

     SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
     SDL_RenderClear(sdlRenderer);
     SDL_RenderPresent(sdlRenderer);
     SDL_ShowCursor(SDL_DISABLE);
     // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
     // SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void clean_up()
{
     SDL_Delay(500);
     SDL_DestroyRenderer(sdlRenderer);
     SDL_DestroyWindow(sdlWindow);
     IMG_Quit();
     SDL_Quit();
}

void show_texture(SDL_Texture *tex, int width, int height)
{
     SDL_Rect dstrect = { (SCREEN_WIDTH - width) / 2,
                          (SCREEN_HEIGHT - height) / 2,
                           width,
                           height };
     SDL_RenderCopy(sdlRenderer, tex, NULL, &dstrect);
     SDL_RenderPresent(sdlRenderer);
}


int main()
{
    init();
    // display_splash(1000);

    /* Preload stimuli */
    int nstims = sizeof(pics)/sizeof(pics[0]);
    printf("%d images to load\n", nstims);
    hcreate(nstims);

    for (int i=0; i < nstims; i++)
            load_image_and_create_texture(pics[i], PICS_FOLDER);

    /* Wait for Start Signal ('t' key press) */
    while (keyboard_wait() != SDLK_t);

    /* start stimulation */
    reset_wall_clock();

    int ntrials = sizeof(trials) / sizeof(Trial);
    int quit = 0;
    for (int i=0; i < ntrials; i++) {

         double time1, time2, time3;
         SDL_Texture *tex = get_texture(trials[i].name);

         while (wall_clock() < trials[i].onset) {
              quit = monitor_keyboard() == SDLK_ESCAPE;
              if (quit) break;
              SDL_Delay(10);
         }
         time1 = wall_clock();

         if (quit) break;

         show_texture(tex, PIC_WIDTH, PIC_WIDTH);

         time2 = wall_clock();

         if (trials[i].duration > 0)
         {
              while (wall_clock() < trials[i].onset + trials[i].duration) {
                   quit = monitor_keyboard() == SDLK_ESCAPE;
                   if (quit) break;
                   SDL_Delay(10);
              }
              /* clear screen */
              SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
              SDL_RenderClear(sdlRenderer);
              SDL_RenderPresent(sdlRenderer);
         }
         time3 = wall_clock();

         if (quit) break;

         printf("%d %d %.0f %.0f %.0f\n", i, trials[i].onset, round(time1), round(time2), round(time3));
    }

    clean_up();
    return 0;
}

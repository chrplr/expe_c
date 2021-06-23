/* associate names to textures  */

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

#include <search.h>
//       #include <errno.h>





char * const pics[] =
{
     "lizzie_1024x768.jpg",
     "rainbow_1024x768.jpg"
};


void load_image_and_create_texture(char *filename)
     /* load a graphic file, create a texture, and add an Entry in the global hashtable linking the file name to the texture */
{
     SDL_Surface image = IMG_Load(filename);
     SDL_Texture texture = SDL_CreateTextureFromSurface(sdlRenderer, image);

     ENTRY item;
     item.key = filename;
     *(SDL_Surface *)item->data = texture;

     hsearch(item, ENTER);

     SDL_FreeSurface(image);
}

int main()
{
     int  N = sizeof(pics)/sizeof(pics[0]);
     ENTRY item, *result;

     if (hcreate(10 + N) == 0) {
          perror("Creation of hash table");
          return -1;
     };

     for (int i = 0; i < N; i++ )
     {
          load_image_and_create_texture(pics[i]);
     }

     for (int i = 0; i < N; i++ )
     {
          item.key = pics[i];
          result = hsearch(item, ENTER);
          printf("%s %d", result->key, *((int*)result->data));
     }


     
}

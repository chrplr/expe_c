/* Play a sound file (wav format) passed on the command line, using libsdl2
 *
 * Time-stamp: <2021-05-26 14:58:39 christophe@pallier.org> 
 *
 * Compile with:
 *   cc -W -Wall $(sdl2-config --cflags) test_playsound.c $(sdl2-config --libs) -o test_playsound
 */

#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
        if (argc != 2) {
                printf("Usage: %s WAVFILE\n", argv[0]);
                return 1;
        }

        if (SDL_Init(SDL_INIT_AUDIO) < 0)
                return 1;

        // Load sound file
        static SDL_AudioSpec wav_spec;
        static Uint8 *wav_buffer;
        static Uint32 wav_length;

        if (SDL_LoadWAV(argv[1], &wav_spec, &wav_buffer, &wav_length) == NULL) {
                SDL_Log("Failed to load wav file %s: %s", argv[1],
                        SDL_GetError());
                return 1;
        }
        // Open audio device
        SDL_AudioDeviceID dev;
        if ((dev = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0)) == 0) {
                SDL_Log("Failed to open audio: %s", SDL_GetError());
                return 1;
        }
        // Play the sound
        if (SDL_QueueAudio(dev, wav_buffer, wav_length) != 0) {
                SDL_Log("%s", SDL_GetError());
        }
        SDL_PauseAudioDevice(dev, 0);   // unpause

        // Wait till there is some audio not yet sent to the soundcard
        while (SDL_GetQueuedAudioSize(dev) > 0) {
                SDL_Delay(10);
                // we could detect a key press and call SDL_ClearQueuedAudio(SDL_AudioDeviceID dev) to abort
        }

        // Clean up
        SDL_CloseAudioDevice(dev);
        SDL_FreeWAV(wav_buffer);

        return 0;
}

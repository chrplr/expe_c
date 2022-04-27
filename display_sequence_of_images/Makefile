MAIN = streaming4
SRCS = streaming4.c

INCLUDES = -I/usr/include/SDL2

LIBS = -lSDL2 -lSDL2_image -lpthread

OBJS =$(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -g -O3


$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) *.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
# DO NOT DELETE

streaming4.o: /usr/include/stdio.h /usr/include/stdlib.h
streaming4.o: /usr/include/search.h /usr/include/features.h
streaming4.o: /usr/include/stdc-predef.h /usr/include/assert.h
streaming4.o: /usr/include/SDL2/SDL.h /usr/include/SDL2/SDL_main.h
streaming4.o: /usr/include/SDL2/SDL_stdinc.h /usr/include/SDL2/SDL_config.h
streaming4.o: /usr/include/SDL2/begin_code.h /usr/include/SDL2/close_code.h
streaming4.o: /usr/include/SDL2/SDL_assert.h /usr/include/SDL2/SDL_atomic.h
streaming4.o: /usr/include/SDL2/SDL_platform.h /usr/include/SDL2/SDL_audio.h
streaming4.o: /usr/include/SDL2/SDL_error.h /usr/include/SDL2/SDL_endian.h
streaming4.o: /usr/include/SDL2/SDL_mutex.h /usr/include/SDL2/SDL_thread.h
streaming4.o: /usr/include/SDL2/SDL_rwops.h /usr/include/SDL2/SDL_clipboard.h
streaming4.o: /usr/include/SDL2/SDL_cpuinfo.h /usr/include/SDL2/SDL_events.h
streaming4.o: /usr/include/SDL2/SDL_video.h /usr/include/SDL2/SDL_pixels.h
streaming4.o: /usr/include/SDL2/SDL_rect.h /usr/include/SDL2/SDL_surface.h
streaming4.o: /usr/include/SDL2/SDL_blendmode.h
streaming4.o: /usr/include/SDL2/SDL_keyboard.h
streaming4.o: /usr/include/SDL2/SDL_keycode.h
streaming4.o: /usr/include/SDL2/SDL_scancode.h /usr/include/SDL2/SDL_mouse.h
streaming4.o: /usr/include/SDL2/SDL_joystick.h
streaming4.o: /usr/include/SDL2/SDL_gamecontroller.h
streaming4.o: /usr/include/SDL2/SDL_quit.h /usr/include/SDL2/SDL_gesture.h
streaming4.o: /usr/include/SDL2/SDL_touch.h
streaming4.o: /usr/include/SDL2/SDL_filesystem.h
streaming4.o: /usr/include/SDL2/SDL_haptic.h /usr/include/SDL2/SDL_hints.h
streaming4.o: /usr/include/SDL2/SDL_loadso.h /usr/include/SDL2/SDL_log.h
streaming4.o: /usr/include/SDL2/SDL_messagebox.h
streaming4.o: /usr/include/SDL2/SDL_power.h /usr/include/SDL2/SDL_render.h
streaming4.o: /usr/include/SDL2/SDL_sensor.h /usr/include/SDL2/SDL_shape.h
streaming4.o: /usr/include/SDL2/SDL_system.h /usr/include/SDL2/SDL_timer.h
streaming4.o: /usr/include/SDL2/SDL_version.h /usr/include/SDL2/SDL_image.h
streaming4.o: lizzie.xpm

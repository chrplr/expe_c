#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([check_audio_visual_timing], [0.0.1], [christophe@pallier.org])
AC_CONFIG_SRCDIR([check_audio_visual_timing.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lSDL2':
AC_CHECK_LIB([SDL2], [SDL_Delay])
# FIXME: Replace `main' with a function in `-lpsychexp':
AC_CHECK_LIB([psychexp], [create_window])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

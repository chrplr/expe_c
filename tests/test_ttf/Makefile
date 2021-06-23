#OBJS specifies which files to compile as part of the project
SRC = lazy_foo_ttf.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w -std=c++0x 

# LIBS
LIBS=-I/usr/include/SDL2

#LINKER_FLAGS specifies the libraries we're linking against 
LINKER_FLAGS = -lSDL2 -lSDL2_image -lpthread -lSDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = lazy_foo

#This is the target that compiles our executable
all : $(SRC)
	$(CC) $(SRC) $(LIBS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

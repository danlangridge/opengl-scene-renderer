OBJS = main.cpp Particle.cpp Vector.cpp
CC = g++
COMPILER_FLAGS = -g
LINKER_FLAGS = -lGL -lGLU -lglut -lSOIL
OBJ_NAME = game
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

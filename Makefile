OBJS = main.cpp Sprite.o PFholder.o ParticleForceGenerator.o Particle.o Vector.o
CC = g++
INCLUDE_PATHS = -I./gravel-engine -I./
LINKER_FLAGS = -lGL -lGLU -lglut -lSOIL
COMPILER_FLAGS = -g -Fs $(INCLUDE_PATHS)
OBJ_NAME = game

engine : 
	cd ./gravel-engine; make clean; make all; mv *.o ./../

Sprite.o :
	$(CC) $(COMPILER_FLAGS) -c Sprite.cpp

all : engine $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 

clean : 
	rm *.o game

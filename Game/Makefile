
OBJS = gameplay.cpp items.cpp ui.cpp soundcontrol.cpp setting.cpp difficulty.cpp

CC = g++ -std=c++11

COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = gameplay

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
clean :
	$(RM) *.o gameplay

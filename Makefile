# This will get cleaned up soon.
#
# This is the makefile for a game project that is being built
# to test out the libgamepieces library.
#

#
# Note, $INCLUDES and $LIBS will need modification if your directory 
# structure is different from mine.  I have a projects directory with libgamepieces/ and lgpgame/ directly
# bellow it.
#


INCLUDES = -I./include -I../libgamepieces/include
LIBS = -L./lib -L../libgamepieces/lib
DEBUG = -ggdb


all: game modules

game: bin/game
	
rebuild: clean all


clean:
	rm -rf lib/*
	rm -rf bin/*
	rm -rf obj/*

bin/game: src/main.cpp lib/libgame.a
	g++ ${INCLUDES} ${LIBS} ${DEBUG} -o bin/game src/main.cpp -lgame -lgamepieces


modules: obj/game_room.o obj/game_world.o obj/game_genroom.o obj/game_maze.o

lib/libgame.a: modules
	ar rcs lib/libgame.a obj/game_room.o obj/game_world.o obj/game_genroom.o obj/game_maze.o

obj/game_room.o: src/game_room.cpp include/game_room.hpp
	g++ ${INCLUDES} ${DEBUG} -o obj/game_room.o -c src/game_room.cpp

obj/game_world.o: src/game_world.cpp include/game_world.hpp
	g++ ${INCLUDES} ${DEBUG} -o obj/game_world.o -c src/game_world.cpp

obj/game_genroom.o: src/game_genroom.cpp include/game_genroom.hpp
	g++ ${INCLUDES} ${DEBUG} -o obj/game_genroom.o -c src/game_genroom.cpp

obj/game_maze.o: src/game_maze.cpp include/game_maze.hpp
	g++ ${INCLUDES} ${DEBUG} -o obj/game_maze.o -c src/game_maze.cpp




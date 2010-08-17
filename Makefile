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


#
# The following variables point to the programs used to compile
# the project.  The commented out lines bellow are what I use to
# cross compile on my Linux box so that I don't have to boot into windows
# just to compile.  The uncommented lines are what I use to compile the Linux
# version.  If you are on some other system, you will want to change these
# lines to whatever works for you.
#
#CC  = i586-mingw32msvc-cc
#CXX = i586-mingw32msvc-c++
#AR  = i586-mingw32msvc-ar
CC  = gcc
CXX = g++
AR  = ar


all: bin/game lib/libgame.a

game: bin/game
	
rebuild: clean all


clean:
	rm -rf lib/*
	rm -rf bin/*
	rm -rf obj/*

bin/game: src/main.cpp lib/libgame.a
	${CXX} ${INCLUDES} ${LIBS} ${DEBUG} -o bin/game src/main.cpp -lgame -lgamepieces



lib/libgame.a: obj/game_room.o obj/game_world.o obj/game_genroom.o obj/game_maze.o obj/game_player.o obj/game_genplayer.o
	${AR} rcs lib/libgame.a obj/game_room.o obj/game_world.o obj/game_genroom.o obj/game_maze.o obj/game_player.o obj/game_genplayer.o

#
# Game Objects
#
obj/game_room.o: src/game_room.cpp include/game_room.hpp
	${CXX} ${INCLUDES} ${DEBUG} -o obj/game_room.o -c src/game_room.cpp

obj/game_world.o: src/game_world.cpp include/game_world.hpp
	${CXX} ${INCLUDES} ${DEBUG} -o obj/game_world.o -c src/game_world.cpp

obj/game_maze.o: src/game_maze.cpp include/game_maze.hpp
	${CXX} ${INCLUDES} ${DEBUG} -o obj/game_maze.o -c src/game_maze.cpp

obj/game_player.o: src/game_player.cpp include/game_player.hpp
	${CXX} ${INCLUDES} ${DEBUG} -o obj/game_player.o -c src/game_player.cpp


#
# Generators
#
obj/game_genroom.o: src/game_genroom.cpp include/game_genroom.hpp
	${CXX} ${INCLUDES} ${DEBUG} -o obj/game_genroom.o -c src/game_genroom.cpp


obj/game_genplayer.o: src/game_genplayer.cpp include/game_genplayer.hpp
	${CXX} ${INCLUDES} ${DEBUG} -o obj/game_genplayer.o -c src/game_genplayer.cpp



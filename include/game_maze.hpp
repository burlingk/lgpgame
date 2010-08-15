/// \file game_maze.hpp
/// \brief The description and definition of the game::Maze class.
/// \author Kenneth. M. Burling Jr. (a.k.a. Emry)
/// \version Alpha-0.001
///
/// copyright: Copyright &copy; 2008, 2009, 2010 K. M. Burling Jr.<br>
///            All Rights Reserved
///
/// Redistribution and use in source and binary forms, with or without modification, are permitted provided that
/// the following conditions are met:
///
/// * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
/// * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
///   disclaimer in the documentation and/or other materials provided with the distribution.
/// * Neither the name of the libgamepieces project team, nor the names of its contributors may be used to endorse or
///   promote products derived  from this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
/// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
/// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
/// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
/// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///
///
///  game::Maze is a class that will create and populate the maze that the user will run through.
///  It is quite possible that at a future time, it may also control some other changing aspects
///  of the maze throughout the course of the game.
///
/// File last updated 13:30 UTC on 14 Aug 2010

#ifndef _GAME_MAZE_HPP_
#define	_GAME_MAZE_HPP_

#include <game_world.hpp>
#include <game_room.hpp>

namespace game {

    using lgp::ObjectID;
    using lgp::Coordinate;

    class Maze
    {
    public:
        Maze();
        ~Maze();

        Maze(World *world);
        
        void generateMaze(void);

        ObjectID getRoom(int x, int y, int z);
        void setRoom(int x, int y, int z, ObjectID room);
        
    protected:
        ObjectID originRoomM;               //The Object ID of the room at location 0,0,0
        ObjectID startRoomM;                //The Object ID of the start of the maze.
        ObjectID finishRoomM;               //The Object ID of the end of the maze.

        World* worldM;                       //The world the Maze is in.


        ObjectID mapM[11][11][11];

        //Helper methods
        Direction pickDirection(Room &room);
        Direction reverseDirection(Direction direction);
        Coordinate newLocation(Room &room, Direction direction);




    };


} //end namespace game

#endif	// end _GAME_MAZE_HPP_

/// \file game_room.hpp
/// \brief The description and definition of the game::Room class.
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
///  game::Room is a variant of lgp::Object that represents a room.
///
/// File last updated 13:30 UTC on 14 Aug 2010

#ifndef _GAME_ROOM_HPP_
#define	_GAME_ROOM_HPP_

#include <lgp_object.hpp>

namespace game {
    using lgp::ObjectID;

    enum Direction {NORTH=1, SOUTH, EAST, WEST, UP, DOWN};

    class Room : public lgp::Object
    {
    public:
        Room();
        ~Room();

        Room(std::string name);

        //
        bool isExit(Direction direction);                  //Checks to see if a door exists for a given direction
        ObjectID getExit(Direction direction);             //Returns the room that an exit goes too.

        void setExit(Direction direction,ObjectID room);   //Sets the room that an exit goes too.  #-1 means no exit.

        std::string getDescription(void);
        void setDescription(std::string description);
        
    protected:
        //These values hold the Object ID of the rooms that the doors lead too.
        //If there is not a door in a given direction, then the value is #-1.
        ObjectID northDoorM;
        ObjectID southDoorM;
        ObjectID eastDoorM;
        ObjectID westDoorM;
        ObjectID upDoorM;
        ObjectID downDoorM;

        std::string descriptionM;
    };





}// end namespace game



#endif	// end  _GAME_ROOM_HPP_


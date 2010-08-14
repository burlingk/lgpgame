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

#include <game_room.hpp>


namespace game {

    Room::Room()
    {
        northDoorM = -1;
        southDoorM = -1;
        eastDoorM  = -1;
        westDoorM  = -1;
        upDoorM    = -1;
        downDoorM  = -1;
    }
    Room::~Room() {}

    Room::Room(std::string name)
    {
        nameM      = name;

        northDoorM = -1;
        southDoorM = -1;
        eastDoorM  = -1;
        westDoorM  = -1;
        upDoorM    = -1;
        downDoorM  = -1;
    }



    bool Room::isExit(Direction direction)
    {
        ObjectID door;
        switch (direction)
        {
            case NORTH:
                door = northDoorM;
                break;
            case SOUTH:
                door = southDoorM;
                break;
            case EAST:
                door = eastDoorM;
                break;
            case WEST:
                door = westDoorM;
                break;
            case UP:
                door = upDoorM;
                break;
            case DOWN:
                door = downDoorM;
                break;
            default:
                door = -1;
                break;
        }//end switch (direction)

        return(door != -1);
    } //end isExit();

    ObjectID Room::getExit(Direction direction)
    {
        switch(direction)
        {
            case NORTH:
                return northDoorM;
            case SOUTH:
                return southDoorM;
            case EAST:
                return eastDoorM;
            case WEST:
                return westDoorM;
            case UP:
                return upDoorM;
            case DOWN:
                return downDoorM;
            default:
                return -2;
        }//end switch (direction)
    } //end getExit;

    
    void Room::setExit(Direction direction,ObjectID room)
    {
        switch(direction)
        {
            case NORTH:
                northDoorM = room;
                break;
            case SOUTH:
                southDoorM = room;
                break;
            case EAST:
                eastDoorM = room;
                break;
            case WEST:
                westDoorM = room;
                break;
            case UP:
                upDoorM = room;
                break;
            case DOWN:
                downDoorM = room;
                break;
        } //end switfch (direction)
    }//end setExit()


    void Room::setDescription(std::string description)
    {
        descriptionM = description;
    }

    std::string Room::getDescription(void)
    {
        return descriptionM;
    }

}// end namespace game

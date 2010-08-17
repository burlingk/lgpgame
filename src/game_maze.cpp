/// \file game_maze.cpp
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

#include <game_maze.hpp>
#include <lgp_queue.hpp>
#include <lgp_stack.hpp>
#include <lgp_random.hpp>
#include <sstream>

#include <iostream>

namespace game {

    Maze::Maze()
    {
        startRoomM  = -1;
        finishRoomM = -1;
        for(int x=0; x<11;x++)
        {
            for(int y=0; y<11;y++)
            {
                for (int z=0; z<11; z++)
                {
                    mapM[x][y][z] = -1;
                }//end for(z)
            }//end for(y)
        }//end for(x)
    }//end Maze()
    Maze::~Maze(){}

    Maze::Maze(World *world)
    {
        worldM = world;

        startRoomM  = -1;
        finishRoomM = -1;

        for(int x=0; x<11;x++)
        {
            for(int y=0; y<11;y++)
            {
                for (int z=0; z<11; z++)
                {
                    mapM[x][y][z] = -1;
                }//end for(z)
            }//end for(y)
        }//end for(x)
    }//end Maze(std::string)

    /// Returns the Object ID that belongs to the room at a given location.
    ///
    /// Arrays are 0 indexed, and only have positive key values.
    /// The map is centered on 0,0,0 with a range of -5 to +5 for each axis.
    /// To map the two together, we simply take the coordinates provided for the
    /// map and add +5 to each value.  -5 becomes 0, 0 becomes 5, etc.  This way
    /// -5 to +5 is mapped to 0 to 11.
    ObjectID Maze::getRoom(int x, int y, int z)
    {
        x+= 5;
        y+= 5;
        z+= 5;
        return mapM[x][y][z];
    }

    void Maze::setRoom(int x, int y, int z, ObjectID room)
    {
        x+= 5;
        y+= 5;
        z+= 5;
        mapM[x][y][z] = room;
    }



    /// Chooses a direction for the maze builder to dig.
    ///
    /// The algorythm used here is simple.  The "digger" looks in
    /// each direction.  If there is already a door it moves on.
    /// If there is not already a door, then it looks to see if there
    /// is a room in the space past the wall.  If there is, it moves on.
    /// If the space in that direction is an empty space, then it adds
    /// it to the Queue named doors.  doors is a queue of potential doors.
    ///
    /// Once the Queue is completed, if doors.size() == 0, i.e. it is empty,
    /// then NODIRECTION is returned.  If doors.size() == 1, then whatever
    /// is on the queue is returned.  If the size is anything other than 0 or 1,
    /// then the digger picks a random direction from the Queue and returns that
    /// direction.
    Direction Maze::pickDirection(Room &room)
    {
        lgp::Queue<Direction> doors;
        lgp::Stack<Direction> candidates;
        lgp::Coordinate location = room.getLocation();


        //Select Initial Candidates (No door)
        if(!room.isExit(NORTH)){candidates.push(NORTH);}
        if(!room.isExit(SOUTH)){candidates.push(SOUTH);}
        if(!room.isExit(EAST)) {candidates.push(EAST); }
        if(!room.isExit(WEST)) {candidates.push(WEST); }
        if(!room.isExit(UP))   {candidates.push(UP);   }
        if(!room.isExit(DOWN)) {candidates.push(DOWN); }

        //Check for empty stack.
        if(candidates.size() == 0){return NODIRECTION;}

        while(candidates.size() != 0)
        {
            Direction direction = candidates.pop();
            lgp::Coordinate testCoords = newLocation(room, direction);

            //  I think this may have been my problem.  This code was using array specific variables, but all of the
            //  code that deals with the array maps the world specific locations to the array location already.  I think
            //  this may be why I was getting no rooms in the lower half of the world.
            if(testCoords.x > 5 || testCoords.x < -5 || testCoords.y > 5 || testCoords.y < -5 || testCoords.z > 5 || testCoords.z < -10)
            {
                //Discard value.  Out of range.
            }
            else
            {
                ObjectID testID = getRoom(testCoords.x,testCoords.y,testCoords.z);
                if(testID == -1){doors.push(direction);}
            }//end if out of range.
        }//end while candidates

        //Check for no doors.
        if(doors.size() == 0){return NODIRECTION;}

        //check for just one
        if(doors.size() == 1){return doors.pop();}

        int number = lgp::random(1,50);

        //Choose a random direction from those that are left.
        for(int i = 0; i < number; i++)
        {
            doors.push(doors.pop());
        }

        return doors.pop();
    } //end pickDirection()


    /// Given a direction, return is opposite.
    Direction Maze::reverseDirection(Direction direction)
    {
        switch(direction)
        {
            case NORTH:
                return SOUTH;
            case SOUTH:
                return NORTH;
            case EAST:
                return WEST;
            case WEST:
                return EAST;
            case UP:
                return DOWN;
            case DOWN:
                return UP;
            default:
                return NODIRECTION;
        } //end switch(direction)
    } //end reverseDirection()


    Coordinate Maze::newLocation(Room &room, Direction direction)
    {
        Coordinate tempLoc = room.getLocation();

        switch (direction)
        {
            case NORTH:
                tempLoc.y++;
                return tempLoc;
            case SOUTH:
                tempLoc.y--;
                return tempLoc;
            case EAST:
                tempLoc.x++;
                return tempLoc;
            case WEST:
                tempLoc.x--;
                return tempLoc;
            case UP:
                tempLoc.z++;
                return tempLoc;
            case DOWN:
                tempLoc.z--;
                return tempLoc;
        }

    } //end newLocation()


    /// The function that actually generates the maze.  :-)
    ///
    /// This function is at the heart of game::Maze.  It generates a
    /// random maze for the player to interact with.  At this time, it
    /// will be rather simple, but it will become more complex as the program
    /// improves.
    ///
    /// The algorytm:
    ///   bool complete  = false
    ///   OriginRoom = new room
    ///   while !complete
    ///       check for empty locations
    ///       if one or more empty locations exist
    ///           pick a location at random, add a door to it
    ///           push the current room onto the stack, and move to the new room
    ///       else
    ///           Pop the most recent room off the stack
    ///           Move to that room
    ///           if the stack is empty, and no empty locations exist: complete = true
    ///       endif
    ///   endwhile
    ///
    ///
    /// For some reason I am getting about 668 objects, instead of arround 1200.
    /// Will have to investigate a bit.
    void Maze::generateMaze(void)
    {
        using std::endl;
        using std::cout;

        lgp::Stack<Room*> roomStack;                                              //The stack that drives the "AI"
        originRoomM = worldM->generateObject("room", "The Center of the Maze");   //Create the origin room

        lgp::Object * roomTemp = worldM->getObjectById(originRoomM);              //Retrieve a pointer to originRoomM
        Room * currentRoom = dynamic_cast<Room*>(roomTemp);                      //and cast it propperly to a room.
        setRoom(0,0,0,originRoomM);                                              //Make it the origin.
        currentRoom->setLocation(0,0,0);                                         //
      


        bool complete = false;

        Room * newRoom;

        while (!complete)
        {
            //std::cout << ".";
            Direction newDirection = pickDirection(*currentRoom);
            if(newDirection != NODIRECTION)   //We will create a new room.
            {
                ObjectID newRoomID = worldM->generateObject("room", "A Room in a Maze");    //Create the new room.
                currentRoom->setExit(newDirection, newRoomID);                             //Create the door to the new room.

                roomTemp = worldM->getObjectById(newRoomID);
                newRoom = dynamic_cast<Room*>(roomTemp);

                newRoom->setExit(reverseDirection(newDirection), currentRoom->getId());   //Create the returning door.
                newRoom->setLocation(newLocation(*currentRoom, newDirection));            //Set the location of the new room.
                Coordinate newRoomLocation = newRoom->getLocation();
                
                setRoom(newRoomLocation.x, newRoomLocation.y, newRoomLocation.z, newRoomID);  //Put the new room on the map

                roomStack.push(currentRoom);             //Push the current room on the stack
                currentRoom = newRoom;                   //Move into the new room
            }
            else  //We are at a dead end, so we will attempt to go back a room.
            {
                currentRoom = roomStack.pop();
                if(roomStack.size() == 0 && pickDirection(*currentRoom) == NODIRECTION)
                {
                    complete = true;
                }
            }
            
        } //end while (!complete)

        //Pick Start Room:
        //This will put it in the bottom, back, left quardrant.
        if(getRoom(-5,-5,-5) != -1) { startRoomM = getRoom(-5,-5,-5);}
        else
        {
            bool done = false;
            for (int z = -5; z < 0; z++)
            {
                for(int y = -5; y < 0; y++)
                {
                    for(int x = -5; x < 0; x++)
                    {
                        if(getRoom(x,y,z) != -1)
                        {
                            if(!done)
                            {
                                startRoomM = getRoom(x,y,z);
                                done = true;
                            } //end if !done
                        } //end if getroom != -1
                    }//end x
                } //end y
            } //end z
        } // end else for setting startRoomM

        // Not Optimal, but it should work for now.
        if(startRoomM == -1) 
        {
            cout << "Problem.  Could not place starting room." << endl;
            cout << "Placing the start point at origin." << endl;
            startRoomM = getRoom(0,0,0);
        }

        //Pick the End Point:
        //This will put it in the forward, front right quadrant
        if(getRoom(5,5,5) != -1){finishRoomM = getRoom(5,5,5);}
        else
        {
            bool done = false;
            for(int z = 5; z > 0; z--)
            {
                for(int y = 5; y > 0; y--)
                {
                    for(int x = 5; x > 0; x--)
                    {
                        if(!done)
                        {
                            finishRoomM = getRoom(x,y,z);
                            done = true;
                        } //end if done
                    } //end x
                } //end y
            }//end z
        }// end else for seting finishRoomM

        // Not Optimal, but it MIGHT work for now.
        if(finishRoomM == -1)
        {
            cout << "Problem.  Could not place finishing room." << endl;
            cout << "Placing the end point at origin." << endl;
            finishRoomM = getRoom(0,0,0);
        }

        if(startRoomM == finishRoomM)
        {
            cout << "Ah Bugger. The start and the finish are the same room." << std::endl;
        }

        



    }//end generateMaze()


    void Maze::blankRoom(void)
    {
        workRoomM[0]  =    "                                ";
        workRoomM[1]  =    " ############################## ";
        workRoomM[2]  =    " #                            # ";
        workRoomM[3]  =    " #                            # ";
        workRoomM[4]  =    " #                            # ";
        workRoomM[5]  =    " #                            # ";
        workRoomM[6]  =    " #                            # ";
        workRoomM[7]  =    " #                            # ";
        workRoomM[8]  =    " #                            # ";
        workRoomM[9]  =    " #                            # ";
        workRoomM[10] =    " #                            # ";
        workRoomM[11] =    " #                            # ";
        workRoomM[12] =    " #                            # ";
        workRoomM[13] =    " #                            # ";
        workRoomM[14] =    " #                            # ";
        workRoomM[15] =    " #                            # ";
        workRoomM[16] =    " ############################## ";
        workRoomM[17] =    "                                ";
    } //end blankRoom()

    void Maze::prepareRoom(Room &room)
    {
        blankRoom();
        if(room.isExit(NORTH))
        {
            workRoomM[0] = "           |        |           ";
            workRoomM[1] = " ##########|        |########## ";
            workRoomM[2] = " #         |        |         # ";
        } //end NORTH


        if(room.isExit(SOUTH))
        {
            workRoomM[15] = " #         |        |         # ";
            workRoomM[16] = " ##########|        |########## ";
            workRoomM[17] = "           |        |           ";
        } //end SOUTH


        //
        // It is best to handle EAST, WEST, UP, and DOWN on a character by
        // character basis, because they potentially interfear with each other.

        if(room.isExit(EAST))
        {
            workRoomM[6][29]  = '-';
            workRoomM[6][30]  = '-';
            workRoomM[6][31]  = '-';
            
            workRoomM[7][30]  = ' ';
            workRoomM[8][30]  = ' ';
            workRoomM[9][30]  = ' ';
            workRoomM[10][30] = ' ';
            
            workRoomM[11][29]  = '-';
            workRoomM[11][30]  = '-';
            workRoomM[11][31]  = '-';
            
        }//end EAST

        if(room.isExit(WEST))
        {
            workRoomM[6][0]  = '-';
            workRoomM[6][1]  = '-';
            workRoomM[6][2]  = '-';

            workRoomM[7][1]  = ' ';
            workRoomM[8][1]  = ' ';
            workRoomM[9][1]  = ' ';
            workRoomM[10][1] = ' ';

            workRoomM[11][0]  = '-';
            workRoomM[11][1]  = '-';
            workRoomM[11][2]  = '-';

        }//end WEST


        //Prepare for the up/down
        // In the DF style:
        // ' ' = No Stairs
        // '<' = Up Stairs
        // '>' = Down Stairs
        // 'X' = Up/Down Stairs

        char stairsChar = ' ';

        if(room.isExit(UP) && room.isExit(DOWN))
        {
            stairsChar = 'X';
        }
        if(room.isExit(UP) && !room.isExit(DOWN))
        {
            stairsChar = '<';
        }
        if(!room.isExit(UP) && room.isExit(DOWN))
        {
            stairsChar = '>';
        }


        if(stairsChar != ' ')
        {
            //[7][12] - [10][19]
            for(int y = 7; y <= 10; y++)
            {
                for(int x=12; x <= 19; x++)
                {
                    workRoomM[y][x] = stairsChar;
                }
            }


        }


    }//end prepareRoom


    /// Display a room when given an Object ID for the room.
    ///
    /// This method converts the object ID to a room object, then calls
    /// the full version of the method.
    void Maze::displayRoom(lgp::ObjectID room)
    {
        Room * theRoom = dynamic_cast<Room *>(worldM->getObjectById(room));
        displayRoom(*theRoom);
    }

    void Maze::displayRoom(Room &room)
    {
        using std::cout;
        using std::endl;

        blankRoom();
        prepareRoom(room);

        cout << endl << endl << "          " << room.getName() << endl << endl;

        for(int y = 0; y < 18; y++)
        {
            cout << "          " << workRoomM[y] << endl;
        }

        cout << endl << endl << room.getDescription() << endl;


        cout << endl << exits(room) << endl << endl << endl;;

    } //end displayRoom()


    std::string Maze::exits(Room &room)
    {
        std::stringstream exitString("");

        exitString << "Exits: ";

        if(room.isExit(NORTH)){exitString << " NORTH ";}
        if(room.isExit(SOUTH)){exitString << " SOUTH ";}
        if(room.isExit(EAST)) {exitString << " EAST "; }
        if(room.isExit(WEST)) {exitString << " WEST "; }
        if(room.isExit(UP))   {exitString << " UP ";   }
        if(room.isExit(DOWN)) {exitString << " DOWN "; }

        return exitString.str();
    }


    ObjectID Maze::getStart(void){return startRoomM;};

    ObjectID Maze::getFinish(void){return finishRoomM;};

} //end namespace game
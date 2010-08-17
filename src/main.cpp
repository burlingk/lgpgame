/// \file main.cpp
/// \brief Main file for the lgpgame project.
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
/// This is the file containing the main() function for lgpgame.  lgpgame
/// is a project to put libgamepieces to work on something more concrete than
/// creating and destroying "trolls."
///
/// File last updated 13:30 UTC on 14 Aug 2010


//System includes
#include <algorithm>
#include <string>

//Boost includes
#include<boost/tokenizer.hpp>

//lgpGame includes
#include <lgpgame.hpp>
#include <game_maze.hpp>
#include <game_genplayer.hpp>

void processInput(game::Player &player, game::World &world, game::Maze &maze, bool &finished);
game::Direction string_to_direction(std::string direction);

int main(int argc, char** argv) {

    using std::cout;
    using std::endl;

    lgp::seed();                                //Seed the random number generator

    game::World theWorld;                       //Create the World object.  This time it is based off of game::World
                                                //so that we can customize as much as we want without effecting the lgp library.

    registerGenerators(theWorld);               //Register the object generators.

    lgp::ObjectID playerID = theWorld.generateObject("player", "player");  //Create a player object
    game::Player * player = dynamic_cast<game::Player *>(theWorld.getObjectById(playerID));

    game::Maze theMaze(&theWorld);              //Instantiate the maze class.

    theMaze.generateMaze();                     //Generate the maze.

    player->setCarrier(theMaze.getStart());
    

    theMaze.displayRoom(player->getCarrier());

    bool finished = false;

    while(!finished)
    {
        theMaze.displayRoom(player->getCarrier());

        processInput(*player, theWorld, theMaze, finished);


    }



    cout << "Exiting the program." << endl;
}




void registerGenerators(lgp::World &world)
{
    registerGenerator<lgp::GenCreature>(world, "creature");
    registerGenerator<game::GenRoom>(world, "room");
    registerGenerator<game::GenPlayer>(world, "player");
    return;
}


/// Collect input from the user and process it.
void processInput(game::Player &player, game::World &world, game::Maze &maze, bool &finished)
{
    using std::cout;
    using std::endl;

    //The prompt:  They will see this a lot.
    cout << "What would you like to do?" << endl <<"?: ";

    //First we get the input.
    std::string myInput;
    std::getline(std::cin,myInput);

    //Then we convert it to all caps.
    std::transform(myInput.begin(), myInput.end(), myInput.begin(), ::toupper);

    //Then we chop it up and push it onto a queue
    boost::tokenizer<> tok(myInput);
    lgp::Queue<std::string> wordList;

    for(boost::tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg)
    {
        wordList.push(*beg);
    }

    //If there is no input, then we can't do anything.
    if(wordList.size() == 0) 
    {
        maze.setFlashMessage("The was no input.");
        return;
    }

    //If there is one word, then it will be a command.
    if(wordList.size() == 1)
    {
        std::string command = wordList.pop();

        if (command == "QUIT" || command == "EXIT")
        {
            finished = true;
            return;
        }

        // Check to see if we have a direction.
        // If we do, try to move.
        game::Direction direction = string_to_direction(command);

        if(direction != game::NODIRECTION)
        {
            game::Room * room = dynamic_cast<game::Room*>(world.getObjectById(player.getCarrier()));  //Get access to the room.

            if(room->isExit(direction))
            {
                player.setCarrier(room->getExit(direction));
                if(player.getCarrier() == maze.getFinish())
                {
                    maze.setFlashMessage("You Win!");
                    return;
                }
                return;
            }
            else //command is a direction, but you can't go that way.
            {
                maze.setFlashMessage("You cannot go that direction");
                return;
            }
        }

        maze.setFlashMessage("The input was not understood.");
        return;


    }//end wordList.size() == 1
    
}//end processInput();


/// Returns a direction value.
///
/// If the provided string is a direction, it returns the value.
/// If it is not, the returns NODIRECTION.
game::Direction string_to_direction(std::string direction)
{
    std::transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
    if(direction == "NORTH"){return game::NORTH;}
    if(direction == "SOUTH"){return game::SOUTH;}
    if(direction == "EAST") {return game::EAST; }
    if(direction == "WEST") {return game::WEST; }
    if(direction == "UP")   {return game::UP;   }
    if(direction == "DOWN") {return game::DOWN; }
    return game::NODIRECTION;
}
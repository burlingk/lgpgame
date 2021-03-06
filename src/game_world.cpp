/// \file game_world.cpp
/// \brief A modified version of lgp::World specifically geared towards this game.
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
///   game::World is derived from lgp::World, and will be customized to fit the lgpGame project. :-)
///
/// File last updated 07:34 UTC on 10 Aug 2010



//LGP Headers
  //#include <lgp_generator.hpp>  //Provided via game_world.hpp from lgp_world.hpp
#include <lgp_queue.hpp>

//lgpgame headers
#include <game_world.hpp>

//System headers
#include <iostream>
#include <sstream>


namespace game {


    World::World()
    {
        return;
    }

    World::~World()
    {
        return;
    }




    std::string World::listGenerators(void)
    {
        std::stringstream list("");
        std::string returnVal;
        lgp::Queue<std::string> stringList;

        if (generatorsM.size() == 0)
        {
            return "[]";
        }

        lgp::GeneratorList::iterator current;



        for (current = generatorsM.begin(); current != generatorsM.end(); current++)
        {
            stringList.push(current->first);
        }

        list << "[";

        while(stringList.size() != 0)
        {
            std::string temp = stringList.pop();

            if(stringList.size() == 0)
            {
                list << "\"" << temp << "\"]";
            }
            else
            {
                list << "\"" << temp << "\" ";
            }
        }

        returnVal = list.str();

        return returnVal;
    }


} //end namespace game
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
/// File last updated 15:20 UTC on 8 Aug 2010



//lgpGame includes
#include <lgpgame.hpp>



int main(int argc, char** argv) {

    using std::cout;
    using std::endl;

    game::World theWorld;

    cout << "The Generator List at the start: " << endl << theWorld.listGenerators() << endl;

    //registerGenerator<lgp::GenCreature>(theWorld, "creature");
    //registerGenerator<game::GenRoom>(theWorld, "room");

    registerGenerators(theWorld);

    cout  << "The list now: " << endl << theWorld.listGenerators() << endl;


    cout << "Now I will try to create a creature named Bob." << endl;

    theWorld.generateObject("creature", "Bob");

    cout << "Bob should now be Object #1, since we have only created one object besides the world." << endl;

    cout << "#1 says its name is: " << theWorld.getObjectById(1)->getName() << endl << endl;




}




void registerGenerators(lgp::World &world)
{
    registerGenerator<lgp::GenCreature>(world, "creature");
    registerGenerator<game::GenRoom>(world, "room");
    return;
}

 
 
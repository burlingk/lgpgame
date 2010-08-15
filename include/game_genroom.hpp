


#ifndef _GAME_GENROOM_
#define _GAME_GENROOM_


#include <lgp_generator.hpp>



namespace game {

    class GenRoom : public lgp::IGenerator
    {
    public:
        GenRoom();
        virtual ~GenRoom();

        lgp::Object * generateObject(std::string name);

    protected:

    };


}//end namespace





#endif //end _GAME_GENROOM_




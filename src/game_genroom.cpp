


#include <game_genroom.hpp>
#include <game_room.hpp>




namespace game {

    GenRoom::GenRoom()
    {

    }

    GenRoom::~GenRoom()
    {

    }

    lgp::Object * GenRoom::generateObject(std::string name)
    {
        Room * newRoom = new Room;
        newRoom->setName(name);

        return dynamic_cast<lgp::Object *>(newRoom);
    }


}// end namespace game
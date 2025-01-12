#ifndef GAME_H
#define GAME_H

#include "./NPC.h"
#include "./Interaction.h"
#include "./Player.h"
#include "./GameMap.h"
#include <vector>

class Game
{
    private:
        GameMap gameMapObj;
        Player player;
        //std::vector<NPC> NPC_Vector;
        NPC npc1;

    public:
        Game(std::string GameName);
        void run();
        void updatePlayer();

};

#endif
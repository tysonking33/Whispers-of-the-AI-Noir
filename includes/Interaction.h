#ifndef INTERACTION_H
#define INTERACTION_H

#include "Player.h"
#include "NPC.h"

class Interaction {
public:
    static void interact(Player& player, NPC& npc) {
        std::cout << "Interaction between Player: " << player.getName() 
                  << " and NPC: " << npc.getName() << "\n";
        // Example interaction logic
        float trust = npc.getMetric("Trust");
        float honesty = npc.getMetric("Honesty");

        if (trust > 10 && honesty > 10) {
            std::cout << npc.getName() << ": I trust you. Here is some valuable information.\n";
        } else {
            std::cout << npc.getName() << ": I don't trust you enough to reveal anything.\n";
        }
    }
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <algorithm>

class Player : public Entity {
private:
    std::vector<std::string> inventory;
    float reputation; // Affects interactions with NPCs
    std::vector<std::vector<char>> gameMap;

public:
    Player(const std::string& name, std::vector<std::vector<char>> newGameMap);

    void addItem(const std::string& item);

    void setReputation(float value);

    float getReputation() const;

    void displayInfo() const override;

    void move(std::string moveString);
    void updateMap(std::vector<std::vector<char>> newGameMap);
};

#endif
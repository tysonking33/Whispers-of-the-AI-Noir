#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include <algorithm>

class Player : public Entity {
private:
    std::vector<std::string> inventory;
    float reputation; // Affects interactions with NPCs

public:
    Player(const std::string& name);

    void addItem(const std::string& item);

    void setReputation(float value);

    float getReputation() const;

    void displayInfo() const override;

    void move(std::string moveString);
};

#endif
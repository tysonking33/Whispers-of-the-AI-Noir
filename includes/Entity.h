#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <iostream>

// Base class for all game entities
class Entity
{
protected:
    std::string name;
    std::vector<int> position;
    std::vector<std::vector<char>> gameMap;

public:
    Entity(const std::string &name, std::vector<std::vector<char>> newGameMap) : name(name)
    {
        gameMap = newGameMap;
        position = {-1, -1};
    }

    virtual ~Entity() {}

    std::string getName() const { return name; }
    virtual void displayInfo() const = 0; // For terminal-based display
    void setPosition(int x, int y)
    {
        position = {x, y};
    }
    std::vector<int> getPosition() { return position; }

    void setMap(std::vector<std::vector<char>> newGameMap)
    {
        gameMap = newGameMap;
    }

    std::vector<std::vector<char>> getMap()
    {
        return gameMap;
    }
};

#endif
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

public:
    Entity(const std::string &name);
    virtual ~Entity() {}

    std::string getName() const;
    virtual void displayInfo() const = 0; // For terminal-based display
    void setPosition(int x, int y);
    std::vector<int> getPosition();
};

#endif
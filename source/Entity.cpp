#include "../includes/Entity.h"

Entity::Entity(const std::string &name) : name(name)
{
    position = {-1, -1};
}

std::string Entity::getName() const { return name; }

void Entity::setPosition(int x, int y)
{
    position = {x, y};
}
std::vector<int> Entity::getPosition(){ return position;}
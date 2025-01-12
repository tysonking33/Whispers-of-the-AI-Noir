#include "../includes/Player.h"

Player::Player(const std::string &name) : Entity(name), reputation(10.0f) {}

void Player::addItem(const std::string &item)
{
    inventory.push_back(item);
}

void Player::setReputation(float value)
{
    reputation = std::clamp(value, 0.0f, 20.0f);
}

float Player::getReputation() const { return reputation; }

void Player::displayInfo() const
{
    std::cout << "Player: " << name << "\nReputation: " << reputation << "\nInventory:\n";
    for (const auto &item : inventory)
    {
        std::cout << "  " << item << "\n";
    }
}

void Player::move(std::string moveString)
{
    if (moveString.compare("up") == 0)
    {
        std::vector<int> currentPos = getPosition();
        currentPos[0] = std::max(0, currentPos[0]-1);
        setPosition(currentPos[0], currentPos[1]);
    }
    else if (moveString.compare("down") == 0)
    {
        std::vector<int> currentPos = getPosition();
        currentPos[0] = std::min(9, currentPos[0]+1);
        setPosition(currentPos[0], currentPos[1]);
    }
    else if (moveString.compare("left") == 0)
    {
        std::vector<int> currentPos = getPosition();
        currentPos[0] = std::max(0, currentPos[1]-1);
        setPosition(currentPos[0], currentPos[1]);
    }
    else if (moveString.compare("right") == 0)
    {
        std::vector<int> currentPos = getPosition();
        currentPos[0] = std::min(9, currentPos[1]+1);
        setPosition(currentPos[0], currentPos[1]);
    }
}

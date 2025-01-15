#include "../includes/Player.h"

Player::Player(const std::string &name, std::vector<std::vector<char>> newGameMap) : Entity(name), reputation(10.0f), gameMap(newGameMap) {}

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

void Player::updateMap(std::vector<std::vector<char>> newGameMap)
{
    gameMap = newGameMap;
}

void Player::move(std::string moveString) {
    std::vector<int> currentPos = getPosition();
    int mapHeight = gameMap.size();
    int mapWidth = gameMap[0].size();

    int newX = currentPos[0];
    int newY = currentPos[1];

    if (moveString == "up" && currentPos[0] > 0) {
        newX = currentPos[0] - 1;
    } else if (moveString == "down" && currentPos[0] < mapHeight - 1) {
        newX = currentPos[0] + 1;
    } else if (moveString == "left" && currentPos[1] > 0) {
        newY = currentPos[1] - 1;
    } else if (moveString == "right" && currentPos[1] < mapWidth - 1) {
        newY = currentPos[1] + 1;
    }

    // Check if the new position is valid
    if (gameMap[newX][newY] == '.' || gameMap[newX][newY] == 'D') {
        setPosition(newX, newY);
    }
}


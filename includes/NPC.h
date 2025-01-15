#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For seeding rand()

struct Action
{
    std::string name;
};

class NPC : public Entity
{
protected:
    std::map<std::string, float> metrics;                                               // e.g., Honesty, Trust, Fear, etc.
    std::string role;                                                                   // e.g., Criminal, Police, Public
    int health;                                                                         // overall health
    std::map<std::string, std::pair<int, std::vector<Action>>> metricsThresholdActions; // map that holds the thresholds and corresponding actions
    std::string current_action;
    int action_count;     // for iterations
    int max_action_count; // max_number of iterations the npc will move
    int xPos, yPos;
    std::vector<std::vector<char>> map;

public:
    NPC(const std::string &name, const std::string &role, std::vector<std::vector<char>> newMap, int newX, int newY)
        : Entity(name), role(role), health(100), current_action("random walking"), action_count(0), max_action_count(3), xPos(newX), yPos(newY),map(newMap)
    {
        if (randIntRange(0, 2) == 1)
        {
            current_action = "idle standing";
            max_action_count = 3;
        }
    }

    void setPos(int newX, int newY)
    {
        xPos = newX;
        yPos = newY;
    }

    void setMap(std::vector<std::vector<char>> newMap)
    {
        map = newMap;
    }

    std::vector<int> getPosition()
    {
        std::vector<int> positionVector = {xPos, yPos};
        return positionVector;
    }

    bool stillDoingCurrentAction()
    {
        return action_count < max_action_count;
    }

    void doCurrentAction()
    {
        std::cout << "Current action: " <<  current_action << std::endl;
        if (stillDoingCurrentAction() == true)
        {
            std::cout << "still doing\n";
        }
        else
        {
            std::cout << "finding new action\n";
        }
        if (current_action.compare("random walking") && stillDoingCurrentAction())
        {
            std::cout << "randomWalking();\n";
            randomWalking();
        }
        else if (current_action.compare("idle standing") && stillDoingCurrentAction())
        {
            std::cout << "idle standing\n";
            action_count++;       
        }
        else {
            std::cout << "find new action\n";

            findNewAction();
        }
    }

    void findNewAction()
    {
        action_count = 0;
        std::cout << "finding new action\n";
        if (randIntRange(0, 2) == 1)
        {
            current_action = "idle standing";
            max_action_count = 3;
        }
        else
        {
            current_action = "random walking";
            max_action_count = 3;
        }
    }

    void randomWalking()
    {
        std::cout << "randomWalking()\n";
        // Define possible movements
        std::vector<std::vector<int>> possibleMovements = {
            {-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}};

        // Seed the random number generator
        std::srand(std::time(0));

        std::vector<int> selectedVector;
        char correspondingLetter = ' ';

        while (!possibleMovements.empty())
        {
            // Select a random index from the remaining possible movements
            int randomIndex = std::rand() % possibleMovements.size();
            selectedVector = possibleMovements[randomIndex];

            // Remove the selected movement from the list of possibilities
            possibleMovements.erase(possibleMovements.begin() + randomIndex);

            // Calculate the new position
            int newX = xPos + selectedVector[0];
            int newY = yPos + selectedVector[1];

            // Ensure the new position is within bounds
            if (newX < 0 || newY < 0 || newX >= (int)map.size() || newY >= (int)map[0].size())
            {
                continue; // Skip invalid positions
            }

            // Get the corresponding letter at the new position
            correspondingLetter = map[newX][newY];

            // Check if the corresponding letter is valid (e.g., '.' or 'D')
            if (correspondingLetter == '.' || correspondingLetter == 'D')
            {
                setPos(newX, newY);
                std::cout << "newX: " << newX << ", newY: " << newY << std::endl;
                action_count++;
                return; // Exit the function after finding a valid movement
            }
        }

        // If no valid movement was found
        std::cout << "No valid movements available." << std::endl;
    }

    int randIntRange(int min, int max)
    {
        return (rand() % (max - min + 1)) + min;
    }

    void displayInfo() const override
    {
        std::cout << "NPC: " << name << "\nRole: " << role << "\nMetrics:\n";
        for (const auto &[metricName, value] : metrics)
        {
            std::cout << "  " << metricName << ": " << value << "\n";
        }
    }
};

#endif
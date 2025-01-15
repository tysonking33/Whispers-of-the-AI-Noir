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

public:
    NPC(const std::string &name, const std::string &role, std::vector<std::vector<char>> newMap, int newX, int newY)
        : Entity(name, newMap), role(role), health(100), current_action("random walking"), action_count(0), max_action_count(3)
    {
        setPosition(newX, newY);
        if (randIntRange(0, 2) == 1)
        {
            current_action = "idle standing";
            max_action_count = 3;
        }
        initMetrics();
    }

    void initMetrics()
    {
        metrics["suspicion"] = 0;
        metrics["base suspicion"] = 0;
        metrics["recent events"] = 0;
        metrics["crime exposure"] = 0;
        
        metrics["morality"] = 0;
        metrics["base morality"] = 0;
        metrics["crime participation"] = 0;

        metrics["attention"] = 0;
        metrics["current activity"] = 0;
        metrics["environmental awareness"] = 0;

        metrics["stress"] = 0;
        metrics["base stress"] = 0;
        metrics["events encountered"] = 0;

        metrics["social interaction"] = 0;
        metrics["base personality"] = 0;
        metrics["relationship with player"] = 0;
    }

    void setSingleMetric(std::string currentMetric, int newValue)
    {
        if (currentMetric.compare("base suspicion") || currentMetric.compare("recent events") ||currentMetric.compare("crime exposure"))
        {
            metrics["currentMetric"] = std::clamp(newValue, 0, 100);
            metrics["suspicion"] = metrics["base suspicion"] + metrics["recent events"] * metrics["crime exposure"];
        }
        else if (currentMetric.compare("base morality") || currentMetric.compare("crime participation"))
        {
            metrics["currentMetric"] = std::clamp(newValue, 0, 100);
            metrics["morality"] = metrics["base morality"] - metrics["crime participation"];
        }
        else if (currentMetric.compare("current activity") || currentMetric.compare("environmental awareness"))
        {
            metrics["currentMetric"] = std::clamp(newValue, 0, 100);
            metrics["attention"] = metrics["current activity"] + metrics["environmental awareness"];
        }
        else if (currentMetric.compare("base stress") || currentMetric.compare("events encountered"))
        {
            metrics["currentMetric"] = std::clamp(newValue, 0, 100);
            metrics["stress"] = metrics["base stress"] + metrics["events encountered"];
        }
        else if (currentMetric.compare("base personality") || currentMetric.compare("relationship with player"))
        {

            metrics["currentMetric"] = std::clamp(newValue, 0, 100);
            metrics["social interaction"] = metrics["base personality"] + metrics["relationship with player"] - metrics["stress"];
        }
    }

    void calculateAllMetrics()
    {
        metrics["suspicion"] = metrics["base suspicion"] + metrics["recent events"] * metrics["crime exposure"];
        metrics["morality"] = metrics["base morality"] - metrics["crime participation"];
        metrics["attention"] = metrics["current activity"] + metrics["environmental awareness"];
        metrics["stress"] = metrics["base stress"] + metrics["events encountered"];
        metrics["social interaction"] = metrics["base personality"] + metrics["relationship with player"] - metrics["stress"];
    }

    bool stillDoingCurrentAction()
    {
        return action_count < max_action_count;
    }

    void doCurrentAction()
    {
        if (current_action.compare("random walking") && stillDoingCurrentAction())
        {
            randomWalking();
        }
        else if (current_action.compare("idle standing") && stillDoingCurrentAction())
        {
            action_count++;       
        }
        else {
            findNewAction();
        }
    }

    void findNewAction()
    {
        action_count = 0;
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
            int newX = position[0] + selectedVector[0];
            int newY = position[1] + selectedVector[1];

            // Ensure the new position is within bounds
            if (newX < 0 || newY < 0 || newX >= (int)gameMap.size() || newY >= (int)gameMap[0].size())
            {
                continue; // Skip invalid positions
            }

            // Get the corresponding letter at the new position
            correspondingLetter = gameMap[newX][newY];

            // Check if the corresponding letter is valid (e.g., '.' or 'D')
            if (correspondingLetter == '.' || correspondingLetter == 'D')
            {
                setPosition(newX, newY);
                action_count++;
                return; // Exit the function after finding a valid movement
            }
        }

        // If no valid movement was found
        std::cout << "No valid movements available." << std::endl;
    }

    void displaySingleMetric()
    {
        int current_value = 10;
        int percentage = current_value/100;
        int barWidth = 50; // Width of the progress bar
        int progress = static_cast<int>((percentage / 100) * barWidth); // Calculate progress in terms of bar width
        std::string current_metric = "Happiness";
        // Print the visual progress bar
        std::cout << current_metric << "[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < progress) {
                std::cout << "#";  // Fill the progress part with '#'
            } else {
                std::cout << " ";  // Fill the remaining part with spaces
            }
        }
        std::cout << "] " << std::fixed << std::setprecision(2) << percentage << "%" << std::endl;
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
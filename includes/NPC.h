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

// Define an activity structure to store activities for each score range
struct Activity
{
    int minScore;                              // Minimum score for the activity range
    int maxScore;                              // Maximum score for the activity range
    std::vector<std::string> nearbyActivities; // Activities requiring nearby NPCs
    std::vector<std::string> soloActivities;   // Activities done independently
};

// Define a structure to store activities for each metric
struct MetricActivities
{
    std::vector<Activity> activities; // List of activities for a given metric
};

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
    std::map<std::string, MetricActivities> ActivityBaselines;
    std::vector<std::string> activityHistory;               //store the activities that the npc completed

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
        initActivityBaselines();
    }

    // Function to add activities to a metric
    void addMetricActivities(const std::string &metric, const std::vector<Activity> &activities)
    {
        ActivityBaselines[metric] = MetricActivities{activities};
    }

    // Function to display activities for a given metric and score
    void displayActivities(const std::string &metric, int score, bool npcNearby)
    {
        const MetricActivities &metricData = ActivityBaselines[metric];

        for (const Activity &activity : metricData.activities)
        {
            if (score >= activity.minScore && score <= activity.maxScore)
            {
                std::cout << "Activities for " << metric << " score " << score << ":\n";
                const std::vector<std::string> &chosenActivities = npcNearby ? activity.nearbyActivities : activity.soloActivities;
                for (const std::string &action : chosenActivities)
                {
                    std::cout << " - " << action << "\n";
                }
                break;
            }
        }
    }

    void initActivityBaselines()
    {
        // Define activities for the "Suspicion" metric
        std::vector<Activity> suspicionActivities = {
            {0, 20, {"Chatting with other NPCs"},                                                                               // Nearby activities
             {"Walking", "Relaxing in public spaces"}},                                                                         // Solo activities
            {21, 40, {"Engaging in basic conversations"},                                                                       // Nearby activities
             {"Glancing around", "Walking with occasional pauses"}},                                                            // Solo activities
            {41, 60, {},                                                                                                        // Nearby activities
             {"Keeping distance from strangers", "Avoiding eye contact", "Reacting cautiously to unfamiliar NPCs or players"}}, // Solo activities
            {61, 80, {},                                                                                                        // Nearby activities
             {"Hiding", "Taking detours", "Nervously watching others", "Moving away from the player or detective"}},            // Solo activities
            {81, 100, {},                                                                                                       // Nearby activities
             {"Running", "Hiding in secluded areas", "Avoiding any interactions with the player or others"}}                    // Solo activities
        };

        // Define activities for the "Morality" metric
        std::vector<Activity> moralityActivities = {
            {0, 20, {"Meeting with known criminals"},                                            // Nearby activities
             {"Engaging in illegal activities (theft, vandalism)", "Avoiding law enforcement"}}, // Solo activities
            {21, 40, {"Joining groups that engage in shady activities"},                         // Nearby activities
             {"Lying", "Stealing small items"}},                                                 // Solo activities
            {41, 60, {"Interacting with the player normally"},                                   // Nearby activities
             {"Following local laws but may show occasional rebellious behavior"}},              // Solo activities
            {61, 80, {"Helping the player", "Engaging in community events"},                     // Nearby activities
             {"Supporting law enforcement"}},                                                    // Solo activities
            {81, 100, {"Assisting the player or detective", "Helping the community"},            // Nearby activities
             {"Reporting crimes"}}                                                               // Solo activities
        };

        // Define activities for the "Attention" metric
        std::vector<Activity> attentionActivities = {
            {0, 20, {},                                                                                                          // Nearby activities
             {"Engaged in activities like reading", "Playing games", "Watching TV"}},                                            // Solo activities
            {21, 40, {"Talking with others"},                                                                                    // Nearby activities
             {"Glancing around occasionally", "Walking in familiar routes"}},                                                    // Solo activities
            {41, 60, {},                                                                                                         // Nearby activities
             {"Paying attention to the environment while walking", "Reacting to loud sounds", "Casually observing other NPCs"}}, // Solo activities
            {61, 80, {"Monitoring the player’s actions"},                                                                        // Nearby activities
             {"Vigilant walking", "Checking for threats", "Avoiding poorly lit areas"}},                                         // Solo activities
            {81, 100, {"Alerting others of potential threats"},                                                                  // Nearby activities
             {"Actively avoiding the player or criminals", "Running away from danger"}},                                         // Solo activities
        };
        // Define activities for the "Stress" metric
        std::vector<Activity> stressActivities = {
            {0, 20, {"Talking"},                                                                                                   // Nearby activities
             {"Walking leisurely", "Sitting and enjoying themselves", "Engaging in calm activities like reading or watching TV"}}, // Solo activities
            {21, 40, {},                                                                                                           // Nearby activities
             {"Fidgeting", "Looking around nervously", "Taking occasional breaks or avoiding certain places"}},                    // Solo activities
            {41, 60, {},                                                                                                           // Nearby activities
             {"Avoiding the player or others they find intimidating", "Pacing", "Avoiding confrontations"}},                       // Solo activities
            {61, 80, {"Seeking help from trusted NPCs"},                                                                           // Nearby activities
             {"Hiding", "Running from perceived threats", "Becoming defensive or hostile", "Avoiding crowded areas"}},             // Solo activities
            {81, 100, {"Seeking refuge with law enforcement or allies"},                                                           // Nearby activities
             {"Panicking", "Running", "Hiding", "Making frantic phone calls"}},                                                    // Solo activities
        };

        // Define activities for the "Social Interaction" metric
        std::vector<Activity> socialInteractionActivities = {
            {0, 20, {},                                                                                                                                  // Nearby activities
             {"Staying alone", "Hiding", "Avoiding eye contact with NPCs and the player"}},                                                              // Solo activities
            {21, 40, {"Exchanging necessary information"},                                                                                               // Nearby activities
             {"Briefly talking with NPCs", "Walking alone in quiet areas"}},                                                                             // Solo activities
            {41, 60, {"Talking casually", "Engaging in basic exchanges with the player or others"},                                                      // Nearby activities
             {"Visiting common places like cafes or parks"}},                                                                                            // Solo activities
            {61, 80, {"Attending social gatherings", "Engaging in group conversations", "Helping others", "Cooperating with the player or detective"},   // Nearby activities
             {}},                                                                                                                                        // Solo activities
            {81, 100, {"Constantly engaging in conversations", "Participating in group activities", "Organizing events", "Offering help to the player"}, // Nearby activities
             {}},                                                                                                                                        // Solo activities
        };

        // Add metrics and their activities
        addMetricActivities("Suspicion", suspicionActivities);
        addMetricActivities("Morality", moralityActivities);
        addMetricActivities("Attention", attentionActivities);
        addMetricActivities("Stress", stressActivities);
        addMetricActivities("Social Interaction", socialInteractionActivities);

        // Display activities for a specific metric and score
        displayActivities("Suspicion", 35, false); // Example score for suspicion
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
        if (currentMetric.compare("base suspicion") || currentMetric.compare("recent events") || currentMetric.compare("crime exposure"))
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
        else
        {
            findNewAction();
        }
    }

    void findNewAction()
    {
        action_count = 0;
        int dice = randIntRange(0, 2);
        if (dice == 0)
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
        int percentage = current_value / 100;
        int barWidth = 50;                                              // Width of the progress bar
        int progress = static_cast<int>((percentage / 100) * barWidth); // Calculate progress in terms of bar width
        std::string current_metric = "Happiness";
        // Print the visual progress bar
        std::cout << current_metric << "[";
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < progress)
            {
                std::cout << "#"; // Fill the progress part with '#'
            }
            else
            {
                std::cout << " "; // Fill the remaining part with spaces
            }
        }
        std::cout << "] " << std::fixed << std::setprecision(2) << percentage << "%" << std::endl;
    }

    // min and max inclusive
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
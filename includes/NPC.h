#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include <algorithm>

class NPC : public Entity
{
private:
    std::map<std::string, float> metrics; // e.g., Honesty, Trust, Fear, etc.
    std::string role;                     // e.g., Criminal, Police, Public

public:
    NPC(const std::string &name, const std::string &role) : Entity(name), role(role)
    {
        metrics["emotional intelligence"] = 0;
        // metrics["empathy"] = 0;
        // metrics["emotional regulation"] = 0;
        metrics["physical strength and endurance"] = 0;
        // metrics["muscle mass"]
        // metrics["stamina"]
        // metrics["injuries"]
        metrics["cognitive ability"] = 0;
        // metrics["problem-solving speed"]
        // metrics["memory"]
        // metrics["focus"]
        metrics["morality"] = 0;
        // metrics["personal ethics"]
        // metrics["societal influence"]
        // metrics["personal conflict"]
        metrics["stress response"] = 0;
        // metrics["stress level"]
        // metrics["coping mechanisms"]
        // metrics["fight or flight"]
        metrics["social influence"] = 0;
        // metrics["charisma"]
        // metrics["persuasiveness"]
        // metrics["reputation"]
        metrics["decision accuracy"] = 0;
        // metrics["available information"]
        // metrics["decision-making capability"]
        // metrics["urgency"]
        metrics["risk-taking"] = 0;
        // metrics["impulsiveness"]
        // metrics["thrill-seeking"]
        // metrics["risk aversion"]
        metrics["curiosity"] = 0;
        // metrics["intellectual curiosity"]
        // metrics["environmental novelty"]
        // metrics["motivational drive"]
    }

    void setMetric(const std::string &metricName, float value)
    {
        if (metricName.compare("emotional intelligence"))
        {
            int value = (metrics["self-awareness"] * metrics["empathy"]) / (1 + metrics["emotional regulation"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("physical strength and endurance"))
        {
            int value = (metrics["muscle mass"] * metrics["stamina"]) / (1 + metrics["injuries"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("cognitive ability"))
        {
            int value = (metrics["problem-solving speed"] * metrics["memory"]) / (1 + metrics["focus"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("morality"))
        {
            int value = (metrics["personal ethics"] + metrics["societal influence"]) * metrics["personal conflict"];
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("stress response"))
        {
            int value = (metrics["stress level"] / (1 + exp(-metrics["coping mechanisms"]))) + metrics["fight or flight"];
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("social influence"))
        {
            int value = metrics["charisma"] * metrics["persuasiveness"] + metrics["reputation"];
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("decision accuracy"))
        {
            int value = (metrics["available information"] * metrics["decision-making capability"]) / (1 + exp(metrics["urgency"]));
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("risk-taking"))
        {
            int value = (metrics["impulsiveness"] * metrics["thrill-seeking"]) / (1 + metrics["risk aversion"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("curiosity"))
        {
            int value = (metrics["intellectual curiosity"] + metrics["environmental novelty"]) * (1 + metrics["motivational drive"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        /*---------------------------------------------------------------------------------------------------------------------*/
        if (metricName.compare("environmental sensitivity") == 0)
        {
            // Calculate environmental sensitivity
            int value = (20 * log(metrics["sensory acuity"] + 1)) / (metrics["environmental distraction"] + 1);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("social group influence") == 0)
        {
            // Calculate social group influence
            int value = (metrics["group affiliation"] * metrics["conformity tendency"]) / (1 + metrics["independence"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("trustworthiness") == 0)
        {
            // Calculate trustworthiness
            int value = (metrics["personal integrity"] + metrics["reputation"]) / (1 + metrics["external incentives"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("physical coordination and agility") == 0)
        {
            // Calculate physical coordination and agility
            int value = (metrics["physical agility"] * metrics["muscular coordination"]) / (1 + metrics["fatigue"]);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("conflict resolution") == 0)
        {
            // Calculate conflict resolution
            int value = (metrics["negotiation skill"] + metrics["aggression level"]) / (metrics["willingness to avoid conflict"] + 1);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
        else if (metricName.compare("energy and motivation") == 0)
        {
            // Calculate energy and motivation
            int value = (metrics["rest and recovery"] * metrics["personal goals or ambitions"]) / (metrics["fatigue"] + 1);
            metrics[metricName] = std::clamp(value, 0.0f, 20.0f);
        }
    }

    float getMetric(const std::string &metricName) const
    {
        if (metrics.find(metricName) != metrics.end())
        {
            return metrics.at(metricName);
        }
        return 0.0f;
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
#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include <algorithm>

class NPC : public Entity
{
protected:
    std::map<std::string, float> metrics; // e.g., Honesty, Trust, Fear, etc.
    std::string role;                     // e.g., Criminal, Police, Public

public:
    NPC(const std::string& name, const std::string& role) 
        : Entity(name), role(role) {
        // Initialize metrics to default values
        metrics["emotional intelligence"] = 0;
        metrics["empathy"] = 0;
        metrics["emotional regulation"] = 0;

        metrics["physical strength and endurance"] = 0;
        metrics["muscle mass"] = 0;
        metrics["stamina"] = 0;
        metrics["injuries"] = 0;

        metrics["cognitive ability"] = 0;
        metrics["problem-solving speed"] = 0;
        metrics["memory"] = 0;
        metrics["focus"] = 0;

        metrics["morality"] = 0;
        metrics["personal ethics"] = 0;
        metrics["societal influence"] = 0;
        metrics["personal conflict"] = 0;

        metrics["stress response"] = 0;
        metrics["stress level"] = 0;
        metrics["coping mechanisms"] = 0;
        metrics["fight or flight"] = 0;

        metrics["social influence"] = 0;
        metrics["charisma"] = 0;
        metrics["persuasiveness"] = 0;
        metrics["reputation"] = 0;

        metrics["decision accuracy"] = 0;
        metrics["available information"] = 0;
        metrics["decision-making capability"] = 0;
        metrics["urgency"] = 0;

        metrics["risk-taking"] = 0;
        metrics["impulsiveness"] = 0;
        metrics["thrill-seeking"] = 0;
        metrics["risk aversion"] = 0;

        metrics["curiosity"] = 0;
        metrics["intellectual curiosity"] = 0;
        metrics["environmental novelty"] = 0;
        metrics["motivational drive"] = 0;

        metrics["environmental sensitivity"] = 0;
        metrics["sensory acuity"] = 0;
        metrics["environmental distraction"] = 0;

        metrics["social group influence"] = 0;
        metrics["group affiliation"] = 0;
        metrics["conformity tendency"] = 0;
        metrics["independence"] = 0;

        metrics["trustworthiness"] = 0;
        metrics["personal integrity"] = 0;
        metrics["external incentives"] = 0;

        metrics["physical coordination and agility"] = 0;
        metrics["physical agility"] = 0;
        metrics["muscular coordination"] = 0;
        metrics["fatigue"] = 0;

        metrics["conflict resolution"] = 0;
        metrics["negotiation skill"] = 0;
        metrics["aggression level"] = 0;
        metrics["willingness to avoid conflict"] = 0;

        metrics["energy and motivation"] = 0;
        metrics["rest and recovery"] = 0;
        metrics["personal goals or ambitions"] = 0;
    }
    void setMetric(const std::string &metricName, int value)
    {
        if (metrics.find(metricName) != metrics.end())
        {
            metrics[metricName] = std::clamp(value, 0, 20);
        }
    }


    void calculateMetric(const std::string &metricName)
    {
        if (metricName.compare("emotional intelligence"))
        {
            int value = (metrics["self-awareness"] * metrics["empathy"]) / (1 + metrics["emotional regulation"]);
            metrics[metricName] = std::clamp(value, 0, 20);
        }
        else if (metricName.compare("physical strength and endurance"))
        {
            int value = (metrics["muscle mass"] * metrics["stamina"]) / (1 + metrics["injuries"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("cognitive ability"))
        {
            int value = (metrics["problem-solving speed"] * metrics["memory"]) / (1 + metrics["focus"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("morality"))
        {
            int value = (metrics["personal ethics"] + metrics["societal influence"]) * metrics["personal conflict"];
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("stress response"))
        {
            int value = (metrics["stress level"] / (1 + exp(-metrics["coping mechanisms"]))) + metrics["fight or flight"];
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("social influence"))
        {
            int value = metrics["charisma"] * metrics["persuasiveness"] + metrics["reputation"];
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("decision accuracy"))
        {
            int value = (metrics["available information"] * metrics["decision-making capability"]) / (1 + exp(metrics["urgency"]));
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("risk-taking"))
        {
            int value = (metrics["impulsiveness"] * metrics["thrill-seeking"]) / (1 + metrics["risk aversion"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("curiosity"))
        {
            int value = (metrics["intellectual curiosity"] + metrics["environmental novelty"]) * (1 + metrics["motivational drive"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        if (metricName.compare("environmental sensitivity") == 0)
        {
            // Calculate environmental sensitivity
            int value = (20 * log(metrics["sensory acuity"] + 1)) / (metrics["environmental distraction"] + 1);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }

        else if (metricName.compare("social group influence") == 0)
        {
            // Calculate social group influence
            int value = (metrics["group affiliation"] * metrics["conformity tendency"]) / (1 + metrics["independence"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("trustworthiness") == 0)
        {
            // Calculate trustworthiness
            int value = (metrics["personal integrity"] + metrics["reputation"]) / (1 + metrics["external incentives"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("physical coordination and agility") == 0)
        {
            // Calculate physical coordination and agility
            int value = (metrics["physical agility"] * metrics["muscular coordination"]) / (1 + metrics["fatigue"]);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("conflict resolution") == 0)
        {
            // Calculate conflict resolution
            int value = (metrics["negotiation skill"] + metrics["aggression level"]) / (metrics["willingness to avoid conflict"] + 1);
            metrics[metricName] = std::clamp(value, 0, 20);;
        }
        else if (metricName.compare("energy and motivation") == 0)
        {
            // Calculate energy and motivation
            int value = (metrics["rest and recovery"] * metrics["personal goals or ambitions"]) / (metrics["fatigue"] + 1);
            metrics[metricName] = std::clamp(value, 0, 20);;
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
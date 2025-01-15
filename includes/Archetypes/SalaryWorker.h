#ifndef SALARYWORKER_H
#define SALARYWORKER_H

#include "../NPC.h"

class SalaryWorker : public NPC {
public:
    SalaryWorker(const std::string& name, std::vector<std::vector<char>> newMap, int newX, int newY) 
        : NPC(name, "Salary Worker", newMap, newX, newY) {
        metrics["emotional intelligence"] = 15;
        metrics["empathy"] = 12;
        metrics["emotional regulation"] = 14;

        metrics["physical strength and endurance"] = 8;
        metrics["muscle mass"] = 7;
        metrics["stamina"] = 6;

        metrics["cognitive ability"] = 16;
        metrics["problem-solving speed"] = 15;
        metrics["memory"] = 14;
        metrics["focus"] = 16;

        metrics["morality"] = 14;
        metrics["personal ethics"] = 16;

        metrics["stress response"] = 10;
        metrics["stress level"] = 12;

        metrics["social influence"] = 12;
        metrics["charisma"] = 10;

        metrics["decision accuracy"] = 14;

        metrics["risk-taking"] = 6;

        metrics["curiosity"] = 10;

        metrics["energy and motivation"] = 12;
    }
};

#endif
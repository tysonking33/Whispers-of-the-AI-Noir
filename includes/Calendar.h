#ifndef CALENDAR_H
#define CALENDAR_H

#include <ctime>
#include <iostream>
#include <iomanip> // For std::setw and std::setfill


class Calendar
{
private:
    int timeHr; // int 24hr format, e.g. 23:59
    int timeMin;
    std::tm *localTime; // for date and day of the week
public:
    Calendar() : timeHr(0), timeMin(0)
    {
        // Get current time
        std::time_t now = std::time(nullptr);

        // Convert to local time
        localTime = std::localtime(&now);

        printTimeOfDay();
    }

    void printTimeOfDay()
    {
        std::cout << "\033[32m" // Set text color to white
            << "Right now is "
            << std::setw(2) << std::setfill('0') << timeHr << ":"
            << std::setw(2) << std::setfill('0') << timeMin
            << "\033[0m"    // Reset text color to default
            << std::endl;

        std::cout << "\033[32mCurrent Date: "
                  << (localTime->tm_year + 1900) << "-" // Year
                  << (localTime->tm_mon + 1) << "-"     // Month
                  << localTime->tm_mday                 // Day of the month
                  << "\033[0m"    // Reset text color to default
                  << std::endl;

        // Get the current day of the week
        const char *days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        std::cout << "\033[32mCurrent Day: " << days[localTime->tm_wday] << "\033[0m" << std::endl;
    }
    void UpdateTimeofDay()
    {
        timeMin += 5;
        if (timeMin == 60)
        {
            timeMin = 00;
            timeHr++;
        }
        if (timeHr == 24)
        {
            timeHr = 00;
            localTime->tm_mday += 1;

            // Re-normalize localTime using mktime
            std::time_t updatedTime = std::mktime(localTime);
            if (updatedTime != -1)
            {
                localTime = std::localtime(&updatedTime);
            }
        }
        printTimeOfDay();
    }
};

#endif
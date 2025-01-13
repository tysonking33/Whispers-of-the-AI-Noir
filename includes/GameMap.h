#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include <string.h>
#include <iostream>

class GameMap {
private:
    std::vector<std::vector<char>> grid; // 2D vector to hold the map
    int rows;
    int cols;
    std::string MapName;

public:
    // Constructor to initialize the map with given size
    GameMap(int rows, int cols, std::string NewMapName);

    // Method to display the map
    void display() const;

    // Method to modify a cell in the map
    void setCell(int x, int y, char value);

    // Method to get a value from a specific cell
    char getCell(int x, int y) const;

    std::vector<int> GetMapDimensions();

    std::vector<std::vector<char>> getMap()
    {
        return grid;
    }
    
};

#endif

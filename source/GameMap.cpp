#include "../includes/GameMap.h"

// Constructor to initialize the map with given size
GameMap::GameMap(int rows, int cols, std::string NewMapName) : rows(rows), cols(cols), MapName(NewMapName)
{
    grid = std::vector<std::vector<char>>(rows, std::vector<char>(cols, '.'));
}

// Method to display the map
void GameMap::display() const
{
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            std::cout << cell << " ";
        }
        std::cout << '\n';
    }
}

// Method to modify a cell in the map
void GameMap::setCell(int x, int y, char value)
{
    if (x >= 0 && x < rows && y >= 0 && y < cols)
    {
        grid[x][y] = value;
    }
    else
    {
        std::cerr << "Invalid cell position: (" << x << ", " << y << ")\n";
    }
}

// Method to get a value from a specific cell
char GameMap::getCell(int x, int y) const
{
    if (x >= 0 && x < rows && y >= 0 && y < cols)
    {
        return grid[x][y];
    }
    std::cerr << "Invalid cell position: (" << x << ", " << y << ")\n";
    return '\0'; // Return null character if out of bounds
}

std::vector<int> GameMap::GetMapDimensions()
{
    std::vector<int> Dimensions = {rows, cols};
    return Dimensions;
}
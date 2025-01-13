#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int MIN_ROOM_SIZE = 4;
int MIN_WALL_THICKNESS = 1;

void display(std::vector<std::vector<char>> Map)
{
    for (const auto& row : Map)
    {
        for (char cell : row)
        {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }

}

int randIntRange(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void draw_walls(std::vector<std::vector<char>> &house, int width, int height)
{
    for (int i = 1; i < height; i++)
    {
        if (house[i][0] == '.')
        {
            house[i][0] = '#';
        }
        if (house[i][width-1] == '.')
        {
            house[i][width-1] = '#';
        }
    }

    for (int i = 0; i < width; i++)
    {
        if (house[0][i] == '.')
        {
            house[0][i] = '#';
        }
        if (house[height-1][i] == '.')
        {
            house[height-1][i] = '#';
        }
    }
}

void partition_house(std::vector<std::vector<char>> &house, int x, int y, int width, int height)
{
    // Base case: if the area is too small, stop partitioning
    if (width < MIN_ROOM_SIZE || height < MIN_ROOM_SIZE)
        return;

    // Randomly decide whether to split horizontally or vertically
    if (width > height)
    {
        // Split vertically
        int split_x = randIntRange(x + MIN_WALL_THICKNESS, x + width - MIN_WALL_THICKNESS);
        // Draw vertical wall
        for (int i = y; i < y + height; i++)
        {
            house[i][split_x] = '#';  // # represents wall
        }
        // Place a door on the vertical wall
        int door_y = randIntRange(y + 1, y + height - 2); // Avoid edges
        house[door_y][split_x] = 'D'; // D represents a door

        // Recursively partition the left and right regions
        partition_house(house, x, y, split_x - x, height);
        partition_house(house, split_x + 1, y, x + width - split_x - 1, height);
    }
    else
    {
        // Split horizontally
        int split_y = randIntRange(y + MIN_WALL_THICKNESS, y + height - MIN_WALL_THICKNESS);
        // Draw horizontal wall
        for (int i = x; i < x + width; i++)
        {
            house[split_y][i] = '#';  // # represents wall
        }
        // Place a door on the horizontal wall
        int door_x = randIntRange(x + 1, x + width - 2); // Avoid edges
        house[split_y][door_x] = 'D'; // D represents a door

        // Recursively partition the top and bottom regions
        partition_house(house, x, y, width, split_y - y);
        partition_house(house, x, split_y + 1, width, y + height - split_y - 1);
    }
}

int main()
{
    int width = 30, height = 20;
    srand(static_cast<unsigned>(time(0)));


    std::vector<std::vector<char>> Map = std::vector<std::vector<char>>(height, std::vector<char>(width, '.'));

    display(Map);

    partition_house(Map, 0, 0, width, height);
    draw_walls(Map, width, height);

    std::cout << "---------------------------------------------------------\n";

    display(Map);

    return 0;
}

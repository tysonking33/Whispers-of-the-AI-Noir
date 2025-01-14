#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int MIN_ROOM_SIZE = 4;
int MIN_WALL_THICKNESS = 1;

void display(std::vector<std::vector<char>> Map)
{
    for (const auto &row : Map)
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
        if (house[i][width - 1] == '.')
        {
            house[i][width - 1] = '#';
        }
    }

    for (int i = 0; i < width; i++)
    {
        if (house[0][i] == '.')
        {
            house[0][i] = '#';
        }
        if (house[height - 1][i] == '.')
        {
            house[height - 1][i] = '#';
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
            house[i][split_x] = '#'; // # represents wall
        }
        // Place a door on the vertical wall
        int door_y = randIntRange(y + 1, y + height - 2); // Avoid edges
        house[door_y][split_x] = 'D';                     // D represents a door

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
            house[split_y][i] = '#'; // # represents wall
        }
        // Place a door on the horizontal wall
        int door_x = randIntRange(x + 1, x + width - 2); // Avoid edges
        house[split_y][door_x] = 'D';                    // D represents a door

        // Recursively partition the top and bottom regions
        partition_house(house, x, y, width, split_y - y);
        partition_house(house, x, split_y + 1, width, y + height - split_y - 1);
    }
}

bool not_next_to_door(const std::vector<std::vector<char>> &house, int x, int y)
{
    int height = house.size();
    int width = house[0].size();

    // Ensure the position (x, y) is within bounds
    if (x < 0 || x >= height || y < 0 || y >= width)
        return false;

    // Check if the current cell is empty
    if (house[x][y] != '.')
        return false;

    // Check all neighboring cells, ensuring indices are within bounds
    int dx[] = {-1, 0, 1};
    int dy[] = {-1, 0, 1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int nx = x + dx[i];
            int ny = y + dy[j];

            // Skip the current cell (x, y) itself
            if (nx == x && ny == y)
                continue;

            // Skip out-of-bounds neighbors
            if (nx < 0 || nx >= height || ny < 0 || ny >= width)
                continue;

            // Check if the neighbor is a door
            if (house[nx][ny] == 'D')
                return false;
        }
    }

    // No doors in the vicinity
    return true;
}


#include <queue>


// Helper function to perform flood-fill and mark a room
void markRoom(std::vector<std::vector<char>> &house, std::vector<std::vector<int>> &roomMap, int roomID, int startX, int startY)
{
    int height = house.size();
    int width = house[0].size();

    std::queue<std::pair<int, int>> q;
    q.push({startX, startY});
    roomMap[startY][startX] = roomID;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && house[ny][nx] == '.' && roomMap[ny][nx] == -1)
            {
                roomMap[ny][nx] = roomID;
                q.push({nx, ny});
            }
        }
    }
}

// Helper function to check if there is enough space for a sofa of at least 2 units
bool canPlaceSofa(const std::vector<std::vector<char>> &house, int x, int y, bool horizontal)
{
    int height = house.size();
    int width = house[0].size();

    if (horizontal)
    {
        return x + 1 < width && house[y][x] == '.' && house[y][x + 1] == '.';
    }
    else
    {
        return y + 1 < height && house[y][x] == '.' && house[y + 1][x] == '.';
    }
}

void placeSofa(std::vector<std::vector<char>> &house, int x, int y, bool horizontal)
{
    if (horizontal)
    {
        house[y][x] = 'S';
        house[y][x + 1] = 'S';
    }
    else
    {
        house[y][x] = 'S';
        house[y + 1][x] = 'S';
    }
}

void decorate_rooms(std::vector<std::vector<char>> &house)
{
    int height = house.size();
    int width = house[0].size();

    // Create a room map to track room IDs
    std::vector<std::vector<int>> roomMap(height, std::vector<int>(width, -1));
    int roomID = 0;

    // Mark all rooms with unique IDs
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (house[y][x] == '.' && roomMap[y][x] == -1)
            {
                markRoom(house, roomMap, roomID, x, y);
                roomID++;
            }
        }
    }

    // Track decorations in each room
    std::vector<bool> hasSofa(roomID, false);
    std::vector<bool> hasVase(roomID, false);
    std::vector<bool> hasTV(roomID, false);

    // Place decorations
    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            if (house[y][x] == '.' && not_next_to_door(house, y, x))
            {
                int currentRoomID = roomMap[y][x];

                // 20% chance to place a decoration
                if (rand() % 10 < 2)
                {
                    char decoration;
                    int randType = rand() % 4; // 0 = Table, 1 = Sofa, 2 = TV, 3 = Vase

                    if (randType == 0)
                    {
                        decoration = 'T'; // Table
                    }
                    else if (randType == 1)
                    {
                        if (!hasSofa[currentRoomID])
                        {
                            // Check if there's enough space for a sofa
                            bool horizontal = rand() % 2 == 0; // Randomly choose horizontal or vertical
                            if (canPlaceSofa(house, x, y, horizontal))
                            {
                                placeSofa(house, x, y, horizontal);
                                hasSofa[currentRoomID] = true;
                                continue;
                            }
                        }
                    }
                    else if (randType == 2)
                    {
                        if (hasSofa[currentRoomID] && !hasTV[currentRoomID])
                        {
                            decoration = 'V'; // TV
                            hasTV[currentRoomID] = true;
                        }
                        else
                        {
                            continue; // Skip placing TV if the room doesn't have a sofa or already has a TV
                        }
                    }
                    else
                    {
                        if (!hasVase[currentRoomID])
                        {
                            decoration = 'A'; // Vase
                            hasVase[currentRoomID] = true;
                        }
                        else
                        {
                            continue; // Skip placing Vase if one already exists
                        }
                    }

                    house[y][x] = decoration;

                    // Rule: Ensure tables have at least one chair
                    if (decoration == 'T')
                    {
                        bool chairPlaced = false;
                        int dx[] = {-1, 1, 0, 0};
                        int dy[] = {0, 0, -1, 1};

                        for (int i = 0; i < 4; i++)
                        {
                            int nx = x + dx[i];
                            int ny = y + dy[i];
                            if (nx >= 1 && nx < width - 1 && ny >= 1 && ny < height - 1 &&
                                house[ny][nx] == '.' && not_next_to_door(house, ny, nx))
                            {
                                house[ny][nx] = 'C'; // Place chair
                                chairPlaced = true;
                                break;
                            }
                        }

                        // If no space for a chair, remove the table
                        if (!chairPlaced)
                        {
                            house[y][x] = '.';
                        }
                    }
                }
            }
        }
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

    decorate_rooms(Map);

    std::cout << "---------------------------------------------------------\n";

    display(Map);

    return 0;
}

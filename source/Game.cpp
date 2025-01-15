#include "../includes/Game.h"

Game::Game(std::string GameName): gameMapObj(10, 10, "Game Map"), player("Detective", gameMapObj.getMap()), npc1("Witness", "Public", gameMapObj.getMap(), 5,2), salaryMan0("Jim", gameMapObj.getMap(), 3,3) 
{
    std::cout << "Welcome to " << GameName << std::endl;
    gameMapObj.display();

    // Pass the required argument (player name) to the Player constructor
    player.addItem("Notebook");
    player.addItem("Fingerprint Kit");
    player.setPosition(9, 9);

    // Create NPC and set their properties
    npc1.setPosition(5, 2);

    salaryMan0.setPosition(8,9);

    player.displayInfo();
    npc1.displayInfo();

    // Interaction between player and NPC
    Interaction::interact(player, npc1);

    // Update map cells with player and NPC positions
    gameMapObj.setCell(player.getPosition()[0], player.getPosition()[1], 'P');
    gameMapObj.setCell(npc1.getPosition()[0], npc1.getPosition()[1], 'N');

    // Display the final game map
    gameMapObj.display();
}

void Game::updatePlayer(std::string input)
{
    gameMapObj.setCell(player.getPosition()[0], player.getPosition()[1], '.');
    player.move(input);
    gameMapObj.setCell(player.getPosition()[0], player.getPosition()[1], 'P');
}

void Game::updateNPC()
{
    gameMapObj.setCell(npc1.getPosition()[0], npc1.getPosition()[1], 'X');
    npc1.doCurrentAction();
    gameMapObj.setCell(npc1.getPosition()[0], npc1.getPosition()[1], 'N');
}


void Game::run()
{
    bool GameRunBool = true;
    while (GameRunBool)
    {
        std::string input;
        std::cout << "Enter a command: ";
        std::cin >> input;

        for (char &c : input) {
            c = std::tolower(c);
        }
        if (input.compare("exit") == 0)
        {
                std::cout << "\033[31mGame Over\033[0m" << std::endl;
            exit(1);
        }

        updatePlayer(input);
        updateNPC();

        gameMapObj.display();

    }
}

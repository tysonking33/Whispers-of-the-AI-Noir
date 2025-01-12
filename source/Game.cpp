#include "../includes/Game.h"

Game::Game(std::string GameName): gameMapObj(10, 10, "Game Map"), player("Detective"), npc1("Witness", "Public") 
{
    std::cout << "Welcome to " << GameName << std::endl;
    gameMapObj.display();

    // Pass the required argument (player name) to the Player constructor
    player.addItem("Notebook");
    player.addItem("Fingerprint Kit");
    player.setPosition(9, 9);

    // Create NPC and set their properties
    npc1.setMetric("Honesty", 15.0f);
    npc1.setMetric("Trust", 12.0f);
    npc1.setMetric("Fear", 5.0f);
    npc1.setPosition(5, 2);

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

void Game::updatePlayer()
{
    std::string input;
    std::cout << "Enter a command: ";
    std::cin >> input;

    for (char &c : input) {
        c = std::tolower(c);
    }

    gameMapObj.setCell(player.getPosition()[0], player.getPosition()[1], '.');

    player.move(input);

    gameMapObj.setCell(player.getPosition()[0], player.getPosition()[1], 'P');
}

void Game::run()
{
    bool GameRunBool = true;
    while (GameRunBool)
    {
        updatePlayer();


        gameMapObj.display();

        exit(1);
    }
}

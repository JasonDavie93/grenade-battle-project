#pragma once
// Classes
#include "Screen.h"
#include "Player.h"
#include "Platform.h"
// Default Libraries
#include <SFML/Graphics.hpp>
//#include "Door.h"

// Forward declarations
class Game;
class Platform;
class Player;

class LevelScreen : public Screen
{
public:
    LevelScreen(Game* newGamePtr);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    std::string levelIDstr; // String representing the level ID
    int levelIDint; // Integer representing the level ID

private:
    Player* player1; // Pointer to player 1 object
    Player* player2; // Pointer to player 2 object

    bool gameRunning; // Flag indicating if the game is currently running
    std::vector<Platform*> platformTiles; // Vector of platform objects
    sf::Font gameFont; // Font used for text rendering
    sf::Text scoreDisplay; // Text displaying the score
    int scoreValue; // Current score
    sf::View cameraView; // View used for camera rendering
    int currentLevel; // Current level number
};

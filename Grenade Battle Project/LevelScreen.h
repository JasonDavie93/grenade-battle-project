#pragma once

// Default libraries
#include <SFML/Graphics.hpp>
#include <iostream>

// Classes
#include "Screen.h" // Parent class
// Include all things in the level
#include "OnScreenActor.h"
#include "EndingScreen.h"

// Forward declarations
class Game;
class Platform;
class Player;
class Grenade;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamePtr);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void FireGrenade(sf::Vector2f firePosition, sf::Vector2f fireVelocity, int grenadeOwner);

    void TriggerEndState(bool player1win, bool player2win);

    bool CheckGrenadeAlive(bool isGrenadeAlive);

    std::string levelIDstr; // String to store the level ID
    int levelIDint; // Integer to store the level ID

protected:
    // No protected members declared in this class

private:
    Player* player1; // Pointer to player 1 object
    Player* player2; // Pointer to player 2 object

    EndingScreen endScreen; // Instance of the EndPanel class
    bool gameRunning; // Flag indicating whether the game is running
    bool grenadeAlive; // Flag indicating whether a grenade is alive
    bool player1Win; // Flag indicating whether player 1 has won
    bool player2Win; // Flag indicating whether player 2 has won
    std::vector<Platform*> platformTiles; // Vector of Platform objects
    std::vector<Grenade*> grenadeVector; // Vector of Grenade objects

    sf::Font gameFont; // Font for displaying text
    sf::Text scoreDisplay; // Text object for displaying score
    int scoreValue; // Current score value

    sf::View cameraView; // View for camera positioning

    sf::Music gameMusic; // Music for the game

    int currentLevel; // Current level number
};

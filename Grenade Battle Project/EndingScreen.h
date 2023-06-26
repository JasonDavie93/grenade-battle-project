#pragma once

// Base class
#include "OnScreenActor.h"

// Default libraries
#include <SFML/Graphics.hpp>

class EndingScreen :
    public OnScreenActor
{

public:
    // Constructor
    EndingScreen(sf::RenderWindow* newWindow);

    // Overridden functions from base class
    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    // Override function from base class to set position
    void SetPosition(sf::Vector2f newPosition) override;

    // Custom functions specific to EndPanel
    void StartAnimation();       // Starts animation
    void ResetPosition();        // Resets position
    void DecideWin(bool newPlayer1win, bool newPlayer2win);   // Determines the winner

private:
  
    sf::Sprite backgroundOverLay;   //Sprite for overlay 
    sf::Text title;              // Text for title
    sf::Text message;            // Text for message
    sf::RenderWindow* window;    // Pointer to the SFML window

    bool animatingIn;            // Flag to indicate if animation is in progress
    sf::Clock animationClock;    // Clock for animation timing

    bool player1win;             // Flag to indicate if player 1 wins
    bool player2win;             // Flag to indicate if player 2 wins
};

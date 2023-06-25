#pragma once
// Default libraries
#include <iostream>
// Classes
#include "OnScreenActor.h"
// Forward declarations
// class Grenade;
class LevelScreen;

// Definition of the Player class, which inherits from OnScreenActor
class Player : public OnScreenActor
{
public:
    // Constructor
    Player(std::string newPlayerIDstr, int newPlayerIDint);

    // Overrides the Update function from the base class
    void Update(sf::Time frameTime) override;
    // Overrides the Draw function from the base class
    void Draw(sf::RenderTarget& target) override;

    // Overrides the HandleCollision function from the base class
    void HandleCollision(OnScreenActor& other) override;

    // Setter functions to set the player's ID
    void SetPlayerID(std::string newPlayerIDstr);
    void SetPlayerID(int newPlayerIDint);

private:
    // Private helper function for player movement
    void PlayerMovement();

    // Calculates the position of the pip based on the given time
    sf::Vector2f GetPipPosition(float pipTime);

    // Private member variables
    sf::Vector2f twoFramesOldPos; // Position of the player two frames ago
    sf::Vector2f velocity; // Velocity of the player
    sf::Vector2f acceleration; // Acceleration of the player
    sf::Sprite playerSprite; // Sprite for rendering the player
    sf::Sound playerJumpSound; // Sound for player jumps
    sf::Sound playerDeathSound; // Sound for player deaths
    std::string playerIDstr; // ID of the player as a string
    int playerIDint; // ID of the player as an integer
    LevelScreen* playerLevel; // Pointer to the LevelScreen the player is in
    bool isGrounded; // Flag indicating if the player is on the ground
    bool isAlive; // Flag indicating if the player is alive
    sf::Vector2f hitboxOffset; // Offset of the player's hitbox
    sf::Vector2f hitboxScale; // Scale of the player's hitbox
    sf::Vector2f aimTarget; // Target position for aiming
    // Grenade* playerGrenade; // Pointer to a Grenade object (commented out)
    std::vector<sf::Sprite> pips; // Vector of sprites representing pips
};

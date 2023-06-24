#pragma once

// Default libraries
#include <iostream>

// Classes
#include "OnScreenActor.h"

// Forward declarations
// class Grenade;

class LevelScreen;

class Player : public OnScreenActor
{
public:
    Player();
    void Update(sf::Time frameTime) override;
    void HandleCollision(OnScreenActor& other) override;

    void SetPlayerID(std::string newPlayerIDstr);
    void SetPlayerID(int newPlayerIDint);

private:
    void PlayerMovement();

    // void AimGrenade(sf::Vector2f newAimTarget);
    // void FireGrenade(sf::Vector2f newAimTarget);

    sf::Vector2f twoFramesOldPos;    // Position from two frames ago
    sf::Vector2f velocity;           // Velocity of the player
    sf::Vector2f acceleration;       // Acceleration of the player
    sf::Sprite playerSprite;         // Sprite representing the player
    sf::Sound playerJumpSound;       // Sound for player's jump
    sf::Sound playerDeathSound;      // Sound for player's death
    std::string playerIDstr;         // String representing the player's ID
    int playerIDint;                 // Integer representing the player's ID
    LevelScreen* playerLevel;        // Pointer to the level screen the player belongs to
    bool isGrounded;                 // Flag indicating if the player is grounded
    bool isAlive;                    // Flag indicating if the player is alive
    sf::Vector2f hitboxOffset;       // Offset of the player's hitbox
    sf::Vector2f hitboxScale;        // Scale of the player's hitbox
    sf::Vector2f aimTarget;          // Target for aiming
    // Grenade* playerGrenade;      // Pointer to the player's grenade
};

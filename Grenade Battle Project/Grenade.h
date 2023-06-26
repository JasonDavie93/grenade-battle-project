#pragma once
#include "PhysicsObject.h"

// Forward declarations of classes
class LevelScreen;
class Player;
class OnScreenActor;

// Grenade class, derived from PhysicsObject
class Grenade 
    : public PhysicsObject
{
public:
    // Constructor
    Grenade(sf::Vector2f newPosition, sf::Vector2f newFireVelocity, int owner);

    // Update function, overrides the base class function
    void Update(sf::Time frameTime) override;

    // Draw function, overrides the base class function
    void Draw(sf::RenderTarget& target) override;

    // Function to handle collision with OnScreenActor objects, overrides the base class function
    void HandleCollision(OnScreenActor& other) override;

    // Public setters
    void SetOwner(int newOwner);
    void SetAlive(bool newIsAlive);

    // Public member variables
    int owner; // The number for the player that fired the grenade
    bool isAlive;
    LevelScreen* grenadeLevel; // Pointer to the LevelScreen object

private:
    // Private data 
};

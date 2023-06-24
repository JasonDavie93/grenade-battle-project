// Classes
#include "Player.h"
#include "AssetManager.h"

// Practical Task - Physics Alternatives
enum class PhysicsType
{
    BACKWARDS_EULER,    // Implicit Euler
    SYMPLECTIC_EULER    // Semi-Implicit Euler
};

Player::Player()
    : OnScreenActor()
    , twoFramesOldPos(100, 300)
    , velocity(0, 0)
    , acceleration(0, 0)
    , playerSprite()
    , playerJumpSound()
    , playerDeathSound()
    , playerIDstr()
    , playerIDint()
    , playerLevel()
    , isGrounded()
    , isAlive()
    , hitboxOffset()
    , hitboxScale()
    , aimTarget()
    //, playerGrenade()
{
 
    sprite.setTexture(AssetManager::RequestTexture("player_" + playerIDstr + "_stand")); // Sets the player's sprite texture

    collisionType = CollisionType::CIRCLE; // Sets the collision type to circle

    collisionOffset = sf::Vector2f(0.0f, 0.0f); // Sets the collision offset
    collisionScale = sf::Vector2f(1.0f, 1.0f); // Sets the collision scale

    // Constructor initialization of member variables
}

void Player::Update(sf::Time frameTime)
{
    // Practical Task - Physics Alternatives
    const float DRAG_MULT = 10.0f;
    const PhysicsType physics = PhysicsType::BACKWARDS_EULER;
    switch (physics)
    {
    case PhysicsType::BACKWARDS_EULER:
    {
        // IMPLICIT EULER (BACKWARD EULER) - used for accuracy

        // Update acceleration
        PlayerMovement();

        // Update velocity
        velocity += acceleration * frameTime.asSeconds();

        // Apply drag
        velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

        // Update position
        SetPosition(GetPosition() + velocity * frameTime.asSeconds());
    }
    break;
    case PhysicsType::SYMPLECTIC_EULER:
    {
        // SEMI-IMPLICIT EULER (SYMPLECTIC EULER) - Used for ease of implementation

        // Update velocity
        velocity += acceleration * frameTime.asSeconds();

        // Apply drag
        velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

        // Update position
        SetPosition(GetPosition() + velocity * frameTime.asSeconds());

        // Move the player
        PlayerMovement();
    }
    break;
    }
}

void Player::HandleCollision(OnScreenActor& other)
{
    // Practical Task - Physics Alternatives
    sf::Vector2f depth = CalculateCollisionDepth(other);
    sf::Vector2f newPosition = GetPosition();
    const float JUMPSPEED = 1000;
    if (abs(depth.x) < abs(depth.y))
    {
        // Move in x direction
        newPosition.x += depth.x;
        velocity.x = 0;
        acceleration.x = 0;
    }
    else
    {
        // Move in y direction
        newPosition.y += depth.y;
        velocity.y = 0;
        acceleration.y = 0;

        // Collision from above
        if (depth.y < 0)
        {
            velocity.y = -JUMPSPEED;
        }
    }
    SetPosition(newPosition);
}

void Player::PlayerMovement()
{
    // Practical Task - Physics Alternatives
    const float ACCEL = 5000;
    const float GRAVITY = 1000;

    acceleration.x = 0;
    acceleration.y = GRAVITY;

    if (playerIDint == 1)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            acceleration.x = -ACCEL; // Sets acceleration to the left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            acceleration.x = ACCEL; // Sets acceleration to the right
        }
    }

    if (playerIDint == 2)
    {
        acceleration.x = ACCEL; // Sets acceleration to the right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            acceleration.x = -ACCEL; // Sets acceleration to the left
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // No acceleration change for the right key
        }
    }
}

void Player::SetPlayerID(std::string newPlayerIDstr)
{
    playerIDstr = newPlayerIDstr;
    sprite.setTexture(AssetManager::RequestTexture("player_" + playerIDstr + "_stand")); // Sets the player's sprite texture based on the ID
}

void Player::SetPlayerID(int newPlayerIDint)
{
    playerIDint = newPlayerIDint;
}

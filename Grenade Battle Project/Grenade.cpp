#include "Grenade.h"
#include "AssetManager.h"
#include "VectorHelper.h"
#include "OnScreenActor.h"

enum class PhysicsType
{
    BACKWARDS_EULER,     // Implicit Euler
    SYMPLECTIC_EULER     // Semi-Implicit Euler
};

    Grenade::Grenade(sf::Vector2f newPosition, sf::Vector2f newFireVelocity, int owner)
        : PhysicsObject(),
        owner(owner),
        isAlive(true)
    {
        // Set the texture of the grenade sprite
        sprite.setTexture(AssetManager::RequestTexture("grenade"));

        // Set the position and velocity of the grenade
        SetPosition(newPosition);
        velocity = newFireVelocity;

        applyDrag = false;

        collisionType = CollisionType::AABB;

        collisionOffset = sf::Vector2f(0.0f, 0.0f);
        collisionScale = sf::Vector2f(0.5f, 0.5f);
    }

    // Update the grenade's state
    void Grenade::Update(sf::Time frameTime)
    {
        PhysicsObject::Update(frameTime);

        // Update grenade movement here
    }

    // Draw the grenade
    void Grenade::Draw(sf::RenderTarget& target)
    {
        PhysicsObject::Draw(target);
    }

    // Set the owner of the grenade
    void Grenade::SetOwner(int newOwner)
    {
        owner = newOwner;
    }

    // Set the alive state of the grenade
    void Grenade::SetAlive(bool newIsAlive)
    {
        isAlive = newIsAlive;
    }

    // Handle collision with another OnScreenActor
    void Grenade::HandleCollision(OnScreenActor& other)
    {
        //Practical Task - Physics Alternatives
        // Calculate the depth of the collision
        sf::Vector2f depth = CalculateCollisionDepth(other);
        sf::Vector2f newPosition = GetPosition();

        //Practical Task - Reflection
        // Calculate vectors for collision reflection
        sf::Vector2f topRight = sf::Vector2f(other.GetAABB().left + other.GetAABB().width, other.GetAABB().top);
        sf::Vector2f bottomLeft = sf::Vector2f(other.GetAABB().left, other.GetAABB().top + other.GetAABB().height);
        sf::Vector2f topLeft = sf::Vector2f(other.GetAABB().left, other.GetAABB().top);

        // Check the direction of collision and update position and velocity accordingly
        if (abs(depth.x) < abs(depth.y))
        {
            // Move in the x direction
            newPosition.x += depth.x * 2.0f;

            // Calculate the reflection of velocity based on the collision normal
            velocity = VectorHelper::GetReflection(velocity, VectorHelper::Normalise(VectorHelper::GetNormal(topLeft - bottomLeft)));

            // acceleration.x = 0;
        }
        else
        {
            // Move in the y direction
            newPosition.y += depth.y * 2.0f;

            // Calculate the reflection of velocity based on the collision normal
            velocity = VectorHelper::GetReflection(velocity, VectorHelper::Normalise(VectorHelper::GetNormal(topLeft - topRight)));

            // acceleration.y = 0;

            // Collision from above
            if (depth.y < 0)
            {
                // velocity.y = -JUMPSPEED;
            }
        }

        SetPosition(newPosition);
    }



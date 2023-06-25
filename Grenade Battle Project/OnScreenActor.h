#pragma once

// Default libraries
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


//Practical Task - Collision Geometry
enum class CollisionType

{
	CIRCLE, // Collision type for a circle collider
	AABB // Collision type for an AABB (Axis-Aligned Bounding Box) collider
};

class OnScreenActor
{
public:
	// Constructor
	OnScreenActor();

	virtual void Update(sf::Time frameTime);                      // Update function for the actor
	virtual void Draw(sf::RenderTarget& target);                  // Draw function for the actor

	// Public Getters
	sf::Vector2f GetPosition();                                    // Get the position of the actor
	// Public Setter
	virtual void SetPosition(sf::Vector2f newPosition);            // Set the position of the actor
	void SetPosition(float newX, float newY);                      // Set the position of the actor using individual coordinates
	bool CheckCollision(OnScreenActor other);                       // Check collision with another actor
	void SetColliding(bool newColliding);                           // Set the colliding flag for the actor
	sf::Vector2f CalculateCollisionDepth(OnScreenActor other);      // Calculate the depth of collision with another actor
	virtual void HandleCollision(OnScreenActor& other);             // Handle the collision with another actor
	void SetAlive(bool newAlive);                                   // Set the alive flag for the actor
	sf::FloatRect GetAABB();
protected:
	sf::Sprite sprite;												// Sprite representing the actor
	sf::Vector2f collisionOffset;                                   // Offset of the collider from the position
	sf::Vector2f collisionScale;                                    // Scale of the collider
	CollisionType collisionType;                                    // Type of the collider (circle or AABB)
	sf::Vector2f position;
	bool alive;                                                     // Flag indicating if the actor is alive
private:
	// Private Getters
	sf::Vector2f GetCollisionCentre(); // Get the center point of the collider
	float GetCircleColliderRadius(); // Get the radius of the circle collider
	
	//data
	bool colliding;
};







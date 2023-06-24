#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// Enumeration for different collision types
enum class CollisionType
{
	CIRCLE,	// Circle collision type
	AABB	// Axis-aligned bounding box collision type
};

// Base class for sprite objects
class SpriteObject
{
public:
	//Constructor
	SpriteObject();
	// Updates the sprite object with each frame
	virtual void Update(sf::Time frameTime);
	// Draws the sprite object on the specified render target
	virtual void Draw(sf::RenderTarget& target);
	// Public getter for the position of the sprite object
	sf::Vector2f GetPosition();
	// Public setter for the position of the sprite object
	virtual void SetPosition(sf::Vector2f newPosition);
	// Public setter for the position of the sprite object using individual coordinates
	void SetPosition(float newX, float newY);
	// Checks collision between this sprite object and another sprite object
	bool CheckCollision(SpriteObject other);
	// Sets the collision state of the sprite object
	void SetColliding(bool newColliding);
	// Calculates the depth of collision between this sprite object and another sprite object
	sf::Vector2f CalculateCollisionDepth(SpriteObject other);
	// Handles the collision between this sprite object and another sprite object
	virtual void HandleCollision(SpriteObject& other);
	// Sets the alive state of the sprite object
	void SetAlive(bool newAlive);

protected:
	sf::Sprite sprite;               // The sprite used for rendering
	sf::Vector2f collisionOffset;    // Offset used for collision detection
	sf::Vector2f collisionScale;     // Scale used for collision detection
	CollisionType collisionType;     // Type of collision detection (circle or AABB)
	bool alive;                      // Alive state of the sprite object

private:

	// Private getter for the collision center of the sprite object (used for circle collision)
	sf::Vector2f GetCollisionCentre();
	// Private getter for the radius of the circle collider (used for circle collision)
	float GetCircleColliderRadius();
	// Private getter for the axis-aligned bounding box (AABB) of the sprite object (used for AABB collision)
	sf::FloatRect GetAABB();
	// Data
	sf::Vector2f position;           // Position of the sprite object
	bool colliding;                  // Collision state of the sprite object
};
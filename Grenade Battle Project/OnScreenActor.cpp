//Default libraries
#include <algorithm>

//Classes
#include "OnScreenActor.h"
#include "VectorHelper.h"

// Constructor
OnScreenActor::OnScreenActor()
	: sprite()  // Initializing member variables
	, position(0,0)
	, colliding(false)
	, collisionOffset(0, 0)
	, collisionScale(1, 1)
	, collisionType(CollisionType::AABB)
	, alive(true)
{

}

// Update function
void OnScreenActor::Update(sf::Time frameTime)
{
	// TODO: Implement the logic for updating the actor's state based on frameTime
}

// Draw function
void OnScreenActor::Draw(sf::RenderTarget& target)
{
	if (!alive)
	{
		return; // If the actor is not alive, exit the function
	}

	//Practical Task - Collision Geometry

	target.draw(sprite); // Draw the actor's sprite

	bool drawCollider = true; // Flag indicating whether to draw the collider or not

	if (drawCollider)
	{
		// Draw the collider based on its collision type
		switch (collisionType)
		{
		case CollisionType::AABB:
		{
			// Draw an AABB (Axis-Aligned Bounding Box) collider
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
			sf::Color collisionColour = sf::Color::Green;

			// Change color to red if a collision happens
			if (colliding)
			{
				collisionColour = sf::Color::Red;
			}

			collisionColour.a = 100;
			rectangle.setFillColor(collisionColour);
			target.draw(rectangle);
		}
		break;
		case CollisionType::CIRCLE:
		{
			// Draw a circular collider
			sf::CircleShape circle;
			sf::Vector2f shapePosition = GetCollisionCentre();
			float circleRadius = GetCircleColliderRadius();
			shapePosition.x -= circleRadius;
			shapePosition.y -= circleRadius;
			circle.setPosition(shapePosition);
			circle.setRadius(circleRadius);
			sf::Color collisionColour = sf::Color::Green;

			// Change color to red if a collision happens
			if (colliding)
			{
				collisionColour = sf::Color::Red;
			}

			collisionColour.a = 100;
			circle.setFillColor(collisionColour);
			target.draw(circle);
		}
		break;
		default:
			break;
		}
	}
}

// Get the position of the actor
sf::Vector2f OnScreenActor::GetPosition()
{
	return position;
}

// Set the position of the actor
void OnScreenActor::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

// Set the position of the actor using separate X and Y coordinates
void OnScreenActor::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

// Check for collision between this actor and another actor
bool OnScreenActor::CheckCollision(OnScreenActor other)
{
	if (!alive || !other.alive)
	{
		
	}
	return GetAABB().intersects(other.GetAABB());
	//Practicle Task - Collision Geometry

	switch (collisionType)
	{
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
		{
			// Check for collision between two AABB colliders
			return GetAABB().intersects(other.GetAABB());
		}
		else
		{
			// Check for collision between AABB and circular colliders

			sf::Vector2f nearestPointToCircle = other.GetCollisionCentre();
			sf::FloatRect thisAABB = GetAABB();

			// Clamp the nearest point to the boundaries of the AABB
			nearestPointToCircle.x = std::max(thisAABB.left, std::min(nearestPointToCircle.x, thisAABB.left + thisAABB.width));
			nearestPointToCircle.y = std::max(thisAABB.top, std::min(nearestPointToCircle.y, thisAABB.top + thisAABB.height));

			sf::Vector2f displacement = nearestPointToCircle - other.GetCollisionCentre();

			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = other.GetCircleColliderRadius();

			return squareDistance <= circleRadius * circleRadius;
		}
	}
	break;
	case CollisionType::CIRCLE:
	{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			// Check for collision between two circular colliders

			// Get the vector representing the displacement between the two circles
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

			// Get the magnitude of that vector, which is how far apart the circle centres are
			float squareDistance = VectorHelper::SquareMagnitude(displacement);

			// Compare that to the combined radii of the two circles
			float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

			return squareDistance <= combinedRadii * combinedRadii;
		}
		else
		{
			// Check for collision between circular and AABB colliders

			sf::Vector2f nearestPointToCircle = GetCollisionCentre();
			sf::FloatRect otherAABB = other.GetAABB();

			// Clamp the nearest point to the boundaries of the other AABB
			nearestPointToCircle.x = std::max(otherAABB.left, std::min(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
			nearestPointToCircle.y = std::max(otherAABB.top, std::min(nearestPointToCircle.y, otherAABB.top + otherAABB.height));

			sf::Vector2f displacement = nearestPointToCircle - GetCollisionCentre();

			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = GetCircleColliderRadius();

			return squareDistance <= circleRadius * circleRadius;
		}
	}
	break;
	default:
	{
		return GetAABB().intersects(other.GetAABB()); // Default to AABB intersection if collision types are unknown
	}
	break;
	}
}

// Set the colliding flag of the actor
void OnScreenActor::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

// Calculate the depth of collision between this actor and another actor
sf::Vector2f OnScreenActor::CalculateCollisionDepth(OnScreenActor other)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();
	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();
	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;
	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
	{
		minDistance.x = -minDistance.x;
	}

	if (actualDistance.y < 0)
	{
		minDistance.y = -minDistance.y;
	}

	return actualDistance - minDistance;
}

// Handle collision with another actor
void OnScreenActor::HandleCollision(OnScreenActor& other)
{
	// Do nothing in the base class, should be implemented in child classes
}

// Set the alive flag of the actor
void OnScreenActor::SetAlive(bool newAlive)
{
	alive = newAlive;
}

// Get the center point of the actor's collider
sf::Vector2f OnScreenActor::GetCollisionCentre()
{
	sf::Vector2f centre = position;
	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;
	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;
	return centre;
}

// Get the radius of the circular collider
float OnScreenActor::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	if (bounds.width > bounds.height)
	{
		return bounds.width * 0.5f;
	}
	else
	{
		return bounds.height * 0.5f;
	}
}

// Get the AABB (Axis-Aligned Bounding Box) of the actor's collider
sf::FloatRect OnScreenActor::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;
	sf::Vector2f centre = GetCollisionCentre();
	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;
	return bounds;
}

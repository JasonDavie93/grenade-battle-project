// Default libraries
#include <algorithm>

// Classes
#include "SpriteObject.h"
// TODO: Include the VectorHelper

SpriteObject::SpriteObject()
	: sprite()
	, position(0, 0)
	, colliding(false)
	, collisionOffset(0, 0)
	, collisionScale(1, 1)
	, collisionType(CollisionType::AABB)
	, alive(true)
{
	// Constructor implementation
	// Initialize member variables
}

void SpriteObject::Update(sf::Time frameTime)
{
	// TODO: Implement sprite object update logic
	// Update the sprite object's state based on the frame time
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	// If not alive, skip drawing
	if (!alive)
	{
		return;
	}

	// Draw the sprite
	target.draw(sprite);

	bool drawCollider = true;

	if (drawCollider)
	{
		// Draw collider based on the collision type
		switch (collisionType)
		{
		case CollisionType::AABB:
		{
			// AABB collision type
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));

			sf::Color collisionColour = sf::Color::Green;

			// Turn red if a collision happens
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
			// Circle collision type
			sf::CircleShape circle;

			sf::Vector2f shapePosition = GetCollisionCentre();
			float circleRadius = GetCircleColliderRadius();
			shapePosition.x -= circleRadius;
			shapePosition.y -= circleRadius;

			circle.setPosition(shapePosition);
			circle.setRadius(circleRadius);
			sf::Color collisionColour = sf::Color::Green;

			// Turn red if a collision happens
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

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool SpriteObject::CheckCollision(SpriteObject other)
{
	// If either object is not alive, no collision
	if (!alive || !other.alive)
	{
		return false;
	}

	switch (collisionType)
	{
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
		{
			// AABB vs. AABB collision detection
			return GetAABB().intersects(other.GetAABB());
		}
		else
		{
			// AABB vs. Circle collision detection

			// Get the nearest point on the AABB to the circle
			sf::Vector2f nearestPointToCircle = other.GetCollisionCentre();
			sf::FloatRect thisAABB = GetAABB();

			nearestPointToCircle.x = std::max(thisAABB.left, std::min(nearestPointToCircle.x, thisAABB.left + thisAABB.width));
			nearestPointToCircle.y = std::max(thisAABB.top, std::min(nearestPointToCircle.y, thisAABB.top + thisAABB.height));
			sf::Vector2f displacement = nearestPointToCircle - other.GetCollisionCentre();

			// TODO: Calculate square distance using VectorHelper
			//float squareDistance = VectorHelper::SquareMagnitude(displacement);

			float circleRadius = other.GetCircleColliderRadius();

			// TODO: Return whether square distance is less than or equal to the circle radius squared
			return /*squareDistance <= circleRadius * circleRadius*/ false;
		}
	}
	break;

	case CollisionType::CIRCLE:
	{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			// Circle vs. Circle collision detection

			// Get the vector representing the displacement between the two circles
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

			// TODO: Get the square distance using VectorHelper
			//float squareDistance = VectorHelper::SquareMagnitude(displacement);

			// Compare the square distance with the combined radii of the two circles
			float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

			// TODO: Return whether square distance is less than or equal to the combined radii squared
			return /*squareDistance <= combinedRadii * combinedRadii*/ false;
		}
		else
		{
			// Circle vs. AABB collision detection

			sf::Vector2f nearestPointToCircle = GetCollisionCentre();
			sf::FloatRect otherAABB = other.GetAABB();

			nearestPointToCircle.x = std::max(otherAABB.left, std::min(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
			nearestPointToCircle.y = std::max(otherAABB.top, std::min(nearestPointToCircle.y, otherAABB.top + otherAABB.height));

			sf::Vector2f displacement = nearestPointToCircle - GetCollisionCentre();

			// TODO: Calculate square distance using VectorHelper
			//float squareDistance = VectorHelper::SquareMagnitude(displacement);

			float circleRadius = GetCircleColliderRadius();

			// TODO: Return whether square distance is less than or equal to the circle radius squared
			return /*squareDistance <= circleRadius * circleRadius*/ false;
		}
	}
	break;

	default:
	{
		// Default collision detection using AABB
		return GetAABB().intersects(other.GetAABB());
	}
	break;
	}
}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f SpriteObject::CalculateCollisionDepth(SpriteObject other)
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

void SpriteObject::HandleCollision(SpriteObject& other)
{
	// Do nothing, to be implemented in child classes
}

void SpriteObject::SetAlive(bool newAlive)
{
	alive = newAlive;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;

	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

float SpriteObject::GetCircleColliderRadius()
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

sf::FloatRect SpriteObject::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;

	return bounds;
}

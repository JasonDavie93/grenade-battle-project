//Classes
#include "Player.h"
#include "AssetManager.h"

//Practical Task - Physics Alternatives
enum class PhysicsType
{
	BACKWARD_EULER
	, POSITION_VERLET
	BACKWARDS_EULER //Implicit Euler
	, SYMPLECTIC_EULER //Semi-Implicit Euler
};
Player::Player()
	: SpriteObject()
	

	void Player::Update(sf::Time frameTime)
{
	const float DRAG_MULT = 10.0f;
	const PhysicsType physics = PhysicsType::BACKWARDS_EULER;

	switch (physics)
	{
	case PhysicsType::BACKWARDS_EULER:
	{
		//IMPLICIT EULER (BACKWARD EULER)

		//Update acceleration
		PlayerMovement();

		velocity += acceleration * frameTime.asSeconds();


		//drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

		SetPosition(GetPosition() + velocity * frameTime.asSeconds());


	}
	break;

	case PhysicsType::SYMPLECTIC_EULER:
	{
		//SEMI-IMPLICIT EULER (SYMPLECTIC EULER)
		velocity += acceleration * frameTime.asSeconds();

		//drag
		velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();

		SetPosition(GetPosition() + velocity * frameTime.asSeconds());

		//Update acceleration
		PlayerMovement();
	}
	break;
	}
}

void Player::HandleCollision(SpriteObject& other)
{
	sf::Vector2f depth = CalculateCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();
	const float JUMPSPEED = 1000;

	if (abs(depth.x) < abs(depth.y))
	{
		//Move in x direction
		newPosition.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		//Move in y direction
		newPosition.y += depth.y;
		velocity.y = 0;
		acceleration.y = 0;

		//Collision from above
		if (depth.y < 0)
		{
			velocity.y = -JUMPSPEED;
		}
	}

	SetPosition(newPosition);
}

void Player::UpdateAcceleration()
void Player::PlayerMovement()
{
	const float ACCEL = 5000;
	const float GRAVITY = 1000;


	acceleration.x = 0;
	acceleration.y = GRAVITY;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;

	}
}
#include "PhysicsObject.h"
#include "PhysicsObject.h"

// Practical Task - Physics Alternatives
enum class PhysicsType
{
	BACKWARDS_EULER,  // Implicit Euler
	SYMPLECTIC_EULER  // Semi-Implicit Euler
};

PhysicsObject::PhysicsObject()
	: OnScreenActor()
	, gravity(1000.0f)
	, velocity()
	, acceleration(0, 0)
	, applyDrag(true)
{
	// Constructor for the PhysicsObject class.
	// Initializes the object's properties, such as gravity, velocity, acceleration, and applyDrag.
}

void PhysicsObject::Update(sf::Time frameTime)
{
	OnScreenActor::Update(frameTime);

	// Practical Task - Physics Alternatives
	const float DRAG_MULT = 10.0f;
	const float JOYSTICK_DRAG = 5.0f;
	const PhysicsType physics = PhysicsType::BACKWARDS_EULER;

	switch (physics)
	{
	case PhysicsType::BACKWARDS_EULER:
	{
		// Implicit Euler (Backward Euler) - used for accuracy

		// Update the velocity based on the acceleration and frame time.
		velocity += acceleration * frameTime.asSeconds();

		// Apply drag if a joystick is connected.
		if (sf::Joystick::isConnected(0) && sf::Joystick::isConnected(1))
		{
			if (applyDrag)
			{
				// Apply drag to the velocity in the x-direction.
				velocity.x = velocity.x - velocity.x * DRAG_MULT * JOYSTICK_DRAG * frameTime.asSeconds();
			}
		}
		else
		{
			if (applyDrag)
			{
				// Apply drag to the velocity in the x-direction.
				velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
			}
		}

		SetAccelaration();  // Set the acceleration of the object.
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());  // Update the position based on the velocity.
	}
	break;

	case PhysicsType::SYMPLECTIC_EULER:
	{
		// Semi-Implicit Euler (Symplectic Euler) - Used for ease of implementation
		// Update the velocity based on the acceleration and frame time.
		velocity += acceleration * frameTime.asSeconds();

		// Apply drag if a joystick is connected.
		if (sf::Joystick::isConnected(0) && sf::Joystick::isConnected(1))
		{
			if (applyDrag)
			{
				// Apply drag to the velocity in the x-direction.
				velocity.x = velocity.x - velocity.x * DRAG_MULT * JOYSTICK_DRAG * frameTime.asSeconds();
			}
		}
		else
		{
			if (applyDrag)
			{
				// Apply drag to the velocity in the x-direction.
				velocity.x = velocity.x - velocity.x * DRAG_MULT * frameTime.asSeconds();
			}
		}

		SetAccelaration();  // Set the acceleration of the object.

	}
	break;
	}
}
void PhysicsObject::SetVelocity(sf::Vector2f newVelocity)
{
	// Set the velocity of the object.
	velocity = newVelocity;
}
void PhysicsObject::SetAccelaration()
{
	// Set the acceleration of the object.
	acceleration.x = 0;
	acceleration.y = gravity;
}

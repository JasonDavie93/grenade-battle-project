#pragma once

// Including the header file for the OnScreenActor class
#include "OnScreenActor.h"

// Declaration of the PhysicsObject class, which inherits from OnScreenActor
class PhysicsObject :
	public OnScreenActor
{
public:
	PhysicsObject(); // Default constructor
	// Overriding the Update function from the OnScreenActor class
	virtual void Update(sf::Time frameTime) override;

	// Function to set the velocity of the physics object
	virtual void SetVelocity(sf::Vector2f newVelocity);

	// Function to set the acceleration of the physics object
	virtual void SetAccelaration(); // Note: Typo in function name, should be SetAcceleration
protected:
	float gravity; // Variable to store the gravity value
	sf::Vector2f velocity; // Variable to store the velocity of the physics object
	sf::Vector2f acceleration; // Variable to store the acceleration of the physics object
	bool applyDrag; // Flag indicating whether to apply drag to the physics object
private:

};


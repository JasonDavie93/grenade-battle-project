#pragma once
// Default libraries
#include <iostream>
// Classes
#include "PhysicsObject.h"
// Forward declarations
class Grenade;
class LevelScreen;

// Definition of the Player class, which inherits from PhysicsObject
class Player : public PhysicsObject
{
public:
	// Constructor
	Player(std::string newPlayerIDstr, int newPlayerIDint, LevelScreen* newCurrentLevel);

	// Overrides the Update function from the base class
	void Update(sf::Time frameTime) override;
	// Overrides the Draw function from the base class
	void Draw(sf::RenderTarget& target) override;

	// Overrides the HandleCollision function from the base class
	void HandleCollision(OnScreenActor& other) override;

	// Setter functions to set the player's ID
	void SetPlayerID(std::string newPlayerIDstr);
	void SetPlayerID(int newPlayerIDint);

	int takep1Lives(int lifeTake1);
	int takep2Lives(int lifeTake2);

	LevelScreen* playerLevel;
private:
	void SetAcceleration() override;
	sf::Vector2f GetPipPosition(float pipTime);

	void FireGrenade();

	sf::Vector2f twoFramesOldPos;
	sf::Sprite playerSprite;
	sf::Sound playerJumpSound;
	sf::Sound playerDeathSound;
	std::string playerIDstr;
	int playerIDint;
	bool isGrounded;
	bool isAlive;
	sf::Vector2f aimTarget;
	Grenade* playerGrenade;
	std::vector<sf::Sprite> pips;

	sf::Vector2f fireVelocity;

	sf::Time fireCooldown;
	sf::Clock fireTimer;

	int playerLives;
	int player1Lives;
	int player2Lives;
};
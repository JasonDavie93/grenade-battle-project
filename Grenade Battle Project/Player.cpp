//Classes
#include "Player.h"
#include "AssetManager.h"
#include "LevelScreen.h"
#include "Screen.h"
#include "Grenade.h"

Player::Player(std::string newPlayerIDstr, int newPlayerIDint, LevelScreen* newCurrentLevel)
	: PhysicsObject()
	, twoFramesOldPos(100, 300)
	, playerSprite()
	, playerJumpSound()
	, playerDeathSound()
	, playerIDstr(newPlayerIDstr)
	, playerIDint(newPlayerIDint)
	, playerLevel(newCurrentLevel)
	, isGrounded(true)
	, isAlive(true)
	, aimTarget(0, 0)
	, pips()
	, playerGrenade(nullptr)
	, fireVelocity()
	, fireCooldown(sf::seconds(2.5f))
	, fireTimer()
	, playerLives(3)
	, player1Lives(3)
	, player2Lives(3)
{
	sprite.setTexture(AssetManager::RequestTexture("player_" + playerIDstr + "_stand"));

	collisionType = CollisionType::CIRCLE;

	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);

	//Add sprites to pips
	const int NUM_PIPS = 5;

	for (int i = 0; i < NUM_PIPS; ++i)
	{
		pips.push_back(sf::Sprite());
		pips[i].setTexture(AssetManager::RequestTexture("pip"));
	}
}

void Player::Update(sf::Time frameTime)
{
	//Practical Task - Gravity Prediction
	PhysicsObject::Update(frameTime);

	SetPosition(GetPosition() + velocity * frameTime.asSeconds());

	float pipTime = 0.0f;
	float pipTimeStep = 0.1f;

	for (int i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime));
		pipTime += pipTimeStep;
	}

	//Update acceleration
	//SetAcceleration();

	float joystickZ = sf::Joystick::getAxisPosition(playerIDint - 1, sf::Joystick::Z);

	//Fire grenade
	if (playerIDint == 1)
	{
		if (joystickZ < 0 && fireTimer.getElapsedTime() >= fireCooldown)
		{
			FireGrenade();
		}
	}
	if (playerIDint == 2)
	{
		if (joystickZ < 0 && fireTimer.getElapsedTime() >= fireCooldown)
		{
			FireGrenade();
		}
	}
}

void Player::Draw(sf::RenderTarget& target)
{
	PhysicsObject::Draw(target);

	//Draw pips
	for (int i = 0; i < pips.size(); ++i)
	{
		target.draw(pips[i]);
	}
}

void Player::HandleCollision(OnScreenActor& other)
{
	//Practical Task - Physics Alternatives
	sf::Vector2f depth = CalculateCollisionDepth(other);
	sf::Vector2f newPosition = GetPosition();
	const float JUMPSPEED = 500;

	if (abs(depth.x) < abs(depth.y))
	{
		//Move in x direction
		newPosition.x += depth.x * 2.0f;
		velocity.x = 0;
		acceleration.x = 0;
	}
	else
	{
		//Move in y direction
		newPosition.y += depth.y * 2.0f;
		velocity.y = 0;
		acceleration.y = 0;

		//Collision from above
		if (depth.y < 0)
		{
			if (playerIDint == 1)
			{
				if (sf::Joystick::isButtonPressed(0, 0))
				{
					velocity.y = -JUMPSPEED;
				}
			}
			if (playerIDint == 2)
			{
				if (sf::Joystick::isButtonPressed(1, 0))
				{
					velocity.y = -JUMPSPEED;
				}
			}
		}
	}

	SetPosition(newPosition);

	OnScreenActor* onScreenActorPtr = &other;
	Grenade* grenadePtr = dynamic_cast<Grenade*>(onScreenActorPtr);

	if (grenadePtr != nullptr)
	{
		if (playerIDint == 1)
		{
			player1Lives = takep1Lives(1);
		}

		if (playerIDint == 2)
		{
			player2Lives = takep2Lives(1);
		}

		//playerLevel->DestroyGrenade(playerGrenade)
		if (player1Lives <= 0)
		{
			playerLevel->TriggerEndState(true, false);
		}
		if (player2Lives <= 0)
		{
			playerLevel->TriggerEndState(false, true);
		}
	}
}

void Player::SetAcceleration()
{
	//Practical Task - Physics Alternatives
	PhysicsObject::SetAcceleration();

	const float ACCEL = 5000.0f;
	const float JOYSTICK_FACTOR = 0.1f;
	const float DEADZONE = 10.0f;

	if (sf::Joystick::isConnected(playerIDint - 1))
	{
		float joystickX = sf::Joystick::getAxisPosition(playerIDint - 1, sf::Joystick::X);
		float joystickU = sf::Joystick::getAxisPosition(playerIDint - 1, sf::Joystick::U);
		float joystickV = sf::Joystick::getAxisPosition(playerIDint - 1, sf::Joystick::V);

		if (joystickX > DEADZONE || joystickX < -DEADZONE)
		{
			acceleration.x = joystickX * ACCEL * JOYSTICK_FACTOR;
		}
		if (joystickU > DEADZONE || joystickU < -DEADZONE)
		{
			fireVelocity.x = joystickU / JOYSTICK_FACTOR;
		}
		if (joystickV > DEADZONE || joystickV < -DEADZONE)
		{
			fireVelocity.y = joystickV / JOYSTICK_FACTOR;
		}
	}
	else if (!sf::Joystick::isConnected(playerIDint - 1))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			acceleration.x = -ACCEL;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			acceleration.x = ACCEL;
		}
	}
}

sf::Vector2f Player::GetPipPosition(float pipTime)
{
	//Practical Task - Gravity Prediction
	sf::Vector2f pipPosition;

	pipPosition = sf::Vector2f(0.0f, gravity / 2.0f) * pipTime * pipTime
		+ fireVelocity * pipTime
		+ GetPosition();

	return pipPosition;
}

void Player::FireGrenade()
{
	playerLevel->FireGrenade(GetPosition(), fireVelocity, playerIDint); //Position, velocity, owner
	fireTimer.restart();
}

void Player::SetPlayerID(std::string newPlayerIDstr)
{
	playerIDstr = newPlayerIDstr;
	sprite.setTexture(AssetManager::RequestTexture("player_" + playerIDstr + "_stand"));
}

void Player::SetPlayerID(int newPlayerIDint)
{
	playerIDint = newPlayerIDint;
}

int Player::takep1Lives(int lifeTake1)
{
	player1Lives = player1Lives - lifeTake1;
	return player1Lives;
}

int Player::takep2Lives(int lifeTake2)
{
	player2Lives = player2Lives - lifeTake2;
	return player2Lives;
}

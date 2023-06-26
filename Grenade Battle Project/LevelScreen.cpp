// Default libraries
#include <fstream>
#include <iostream>

// Classes
#include "LevelScreen.h"
#include "Screen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "Game.h"
#include "Player.h"
#include "Grenade.h"

LevelScreen::LevelScreen(Game* newGamePtr)
	: Screen(newGamePtr)
	, levelIDstr()
	, levelIDint()
	, player1(nullptr)
	, player2(nullptr)
	, endScreen(newGamePtr->GetWindow())
	, gameRunning(true)
	, grenadeAlive()
	, player1Win(false)
	, player2Win(false)
	, platformTiles()
	, grenadeVector()
	, gameFont()
	, scoreDisplay()
	, scoreValue(0)
	, cameraView()
	, gameMusic()
	,currentLevel()
	
{
	

	player1 = new Player("1", 1, this); // Create a new Player object with ID "1" and player number 1
	player2 = new Player("2", 2, this); // Create a new Player object with ID "2" and player number 2

	player1->SetPlayerID("1"); // Set the player ID to use when setting textures
	player2->SetPlayerID("2"); // Set the player ID to use when setting textures

	player1->SetPlayerID(1); // Set the player ID to use when setting controls
	player2->SetPlayerID(2); // Set the player ID to use when setting controls

	player1->SetPosition(300.0f, 700.0f); // Set the position of player 1
	player2->SetPosition(700.0f, 700.0f); // Set the position of player 2

	platformTiles.push_back(new Platform(sf::Vector2f(300.0f, 900.0f))); // Create a new Platform object and add it to the vector

	int x = 0;


	for (int i = 0; i < 50; i++)
	{
		int j = 25;

		platformTiles.push_back(new Platform(sf::Vector2f(x + j, 900.0f))); // Create a new Platform object and add it to the vector

		x = x + j;
	}
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{
		// Updates
		player1->Update(frameTime);
		player2->Update(frameTime);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			platformTiles[i]->Update(frameTime);
		}

		for (int g = 0; g < grenadeVector.size(); g++)
		{
			grenadeVector[g]->Update(frameTime);
		}

		// Collisions
		player1->SetColliding(false);
		player2->SetColliding(false);

		for (int i = 0; i < platformTiles.size(); i++)
		{
			platformTiles[i]->SetColliding(false);
		}

		for (int g = 0; g < grenadeVector.size(); g++)
		{
			grenadeVector[g]->SetColliding(false);
		}

		for (int i = 0; i < platformTiles.size(); i++)
		{
			if (platformTiles[i]->CheckCollision(*player1))
			{
				player1->SetColliding(true);
				platformTiles[i]->SetColliding(true);
				platformTiles[i]->HandleCollision(*player1);
				player1->HandleCollision(*platformTiles[i]);
			}

			if (platformTiles[i]->CheckCollision(*player2))
			{
				player2->SetColliding(true);
				platformTiles[i]->SetColliding(true);
				platformTiles[i]->HandleCollision(*player2);
				player2->HandleCollision(*platformTiles[i]);
			}

			for (int g = 0; g < grenadeVector.size(); g++)
			{
				if (platformTiles[i]->CheckCollision(*grenadeVector[g]))
				{
					platformTiles[i]->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					platformTiles[i]->HandleCollision(*grenadeVector[g]);
					grenadeVector[g]->HandleCollision(*platformTiles[i]);
				}
			}
		}

		for (int g = 0; g < grenadeVector.size(); g++)
		{
			if (grenadeVector[g]->CheckCollision(*player1))
			{
				if (grenadeVector[g]->owner == 1)
				{
					// Handle collision between player 1 and grenade owned by player 1
				}
				else if (grenadeVector[g]->owner == 2)
				{
					player1->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					player1->HandleCollision(*grenadeVector[g]);
					grenadeVector[g]->SetAlive(false);
					grenadeAlive = false;
				}
			}

			if (grenadeVector[g]->CheckCollision(*player2))
			{
				if (grenadeVector[g]->owner == 1)
				{
					player2->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					player2->HandleCollision(*grenadeVector[g]);
					grenadeVector[g]->SetAlive(false);
					grenadeAlive = false;
				}
				else if (grenadeVector[g]->owner == 2)
				{
					// Handle collision between player 2 and grenade owned by player 2
				}
			}
		}
	}
	else
	{
		endScreen.Update(frameTime);

	}
	if (!grenadeAlive)
	{
		grenadeVector.clear();
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	// Draw the world
	for (int i = 0; i < platformTiles.size(); ++i)
	{
		platformTiles[i]->Draw(target);
	}

	for (int g = 0; g < grenadeVector.size(); ++g)
	{
		grenadeVector[g]->Draw(target);
	}

	player1->Draw(target); // Draw players last
	player2->Draw(target);

	// Draw UI elements
	if (!gameRunning)
	{
		endScreen.Draw(target);
	}
}

void LevelScreen::FireGrenade(sf::Vector2f firePosition, sf::Vector2f fireVelocity, int grenadeOwner)
{
	grenadeAlive = true;
	grenadeVector.push_back(new Grenade(firePosition, fireVelocity, grenadeOwner));
	
}

void LevelScreen::TriggerEndState(bool player1win, bool player2win)
{
	if (player1win)
	{
		gameRunning = false;
		endScreen.DecideWin(true, false);
		endScreen.StartAnimation();
	}
	else if (player2win)
	{
		gameRunning = false;
		endScreen.DecideWin(false, true);
		endScreen.StartAnimation();
	}
}
bool LevelScreen::CheckGrenadeAlive(bool isGrenadeAlive)
{
	return false;
}


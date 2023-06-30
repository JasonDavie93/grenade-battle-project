// Default libraries
#include <fstream>
#include <iostream>
#include <SFML/Audio.hpp>

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
	, scoreDisplayP1()
	, scoreDisplayP2()
	, scoreValueP1(0)
	, scoreValueP2(0)
	, cameraView()
	, gameMusic()
	, currentLevel()
	, owner()
	
	
{

	
	
	//P1 Text Set Up
	scoreDisplayP1.setFont(AssetManager::RequestFont("dogica"));
	scoreDisplayP1.setPosition(40.0f, 10.0f);
	scoreDisplayP1.setCharacterSize(30);
	scoreDisplayP1.setFillColor(sf::Color::Blue);
	//P2 Text Set Up
	scoreDisplayP2.setFont(AssetManager::RequestFont("dogica"));
	scoreDisplayP2.setPosition(1600.0f, 10.0f);
	scoreDisplayP2.setCharacterSize(30);
	scoreDisplayP2.setFillColor(sf::Color::Red);


	player1 = new Player("1", 1, this); // Create a new Player object with ID "1" and player number 1
	player2 = new Player("2", 2, this); // Create a new Player object with ID "2" and player number 2

	player1->SetPlayerID("1"); // Set the player ID to use when setting textures
	player2->SetPlayerID("2"); // Set the player ID to use when setting textures

	player1->SetPlayerID(1); // Set the player ID to use when setting controls
	player2->SetPlayerID(2); // Set the player ID to use when setting controls

	player1->SetPosition(300.0f, 700.0f); // Set the position of player 1
	player2->SetPosition(700.0f, 700.0f); // Set the position of player 2

	platformTiles.push_back(new Platform(sf::Vector2f(300.0f, 900.0f))); // Create a new Platform object and add it to the vector
// Base platform and Column
	int x1 = 0;
	int y1 = -40;
	int y2 = -40;

	// Base Platform
	for (int i = 0; i < 74; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x1 + j, 900.0f)));
		x1 = x1 + j;
	}

	// Left Column of the play area
	for (int i = 0; i < 40; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(0, y1 + j)));
		y1 = y1 + j;
	}

	// Right Column of the play area
	for (int i = 0; i < 40; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x1 + 25, y2 + j)));
		y2 = y2 + j;
	}
// Bottom Platform 1 (Left)
	int x2 = 50;
	for (int i = 0; i < 24; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x2 + j, 700.0f)));
		x2 = x2 + j;
	}

	// Middle Platform 1 (Bottom)
	int x3 = 600;
	for (int i = 0; i < 24; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x3 + j, 600.0f)));
		x3 = x3 + j;
	}

	// Bottom Platform 2 (Right)
	int x4 = 1200;
	for (int i = 0; i < 24; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x4 + j, 700.0f)));
		x4 = x4 + j;
	}

	// Middle Platform 2 (Top)
	int x5 = 725;
	for (int i = 0; i < 15; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x5 + j, 400.0f)));
		x5 = x5 + j;
	}

	// Right Platform 2 (Top)
	int x6 = 1200;
	for (int i = 0; i < 74; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x6 + j, 250.0f)));
		x6 = x6 + j;
	}

	int x7 = 50;
	for (int i = 0; i < 23; i++)
	{
		int j = 25;
		platformTiles.push_back(new Platform(sf::Vector2f(x7 + j, 250.0f)));
		x7 = x7 + j;

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
				if (grenadeVector[g]->GetOwner() == 1)
				{
					// Handle collision between player 1 and grenade owned by player 1
					
				}
				else if (grenadeVector[g]->GetOwner() == 2)
				{
					player1->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					player1->HandleCollision(*grenadeVector[g]);
					grenadeVector[g]->SetAlive(false);
					grenadeAlive = false;
					scoreValueP2 ++;
				

				}
			}

			if (grenadeVector[g]->CheckCollision(*player2))
			{
				if (grenadeVector[g]->GetOwner() == 1)
				{
					player2->SetColliding(true);
					grenadeVector[g]->SetColliding(true);
					player2->HandleCollision(*grenadeVector[g]);
					grenadeVector[g]->SetAlive(false);
					grenadeAlive = false;
					scoreValueP1 ++;
					

				}
				else if (grenadeVector[g]->GetOwner() == 2)
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
	target.draw(scoreDisplayP1);
	scoreDisplayP1.setString("Score: " + std::to_string(scoreValueP1));

	target.draw(scoreDisplayP2);
	scoreDisplayP2.setString("Score: " + std::to_string(scoreValueP2));
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


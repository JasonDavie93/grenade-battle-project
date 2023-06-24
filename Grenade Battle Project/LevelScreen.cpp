#include "LevelScreen.h"
#include "AssetManager.h"
#include "Screen.h"
#include "Platform.h"
#include "Game.h"
#include "Player.h"

#include <fstream>
#include <iostream>

LevelScreen::LevelScreen(Game* newGamePtr)
    : Screen(newGamePtr)
    , player1(nullptr)
    , player2(nullptr)
    , gameRunning(true)
    , platformTiles()
    , gameFont()
    , scoreDisplay()
    , scoreValue()
    , cameraView()
    , currentLevel()
{
    // Constructor implementation

    // Initialize member variables
}

void LevelScreen::Update(sf::Time frameTime)
{
    if (gameRunning)
    {
        // Update game entities
        player1->Update(frameTime);
        player2->Update(frameTime);

        for (int i = 0; i < platformTiles.size(); i++)
        {
            platformTiles[i]->Update(frameTime);
        }
    }
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
    // Draw the world

    for (int i = 0; i < platformTiles.size(); ++i)
    {
        platformTiles[i]->Draw(target);
    }
}

#include "Game.h"
#include "Screen.h"
#include "LevelScreen.h"

Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
	, currentScreen(nullptr)
{
	// Window setup
	window.setMouseCursorVisible(false);

	// TODO: Setup screens
	//currentScreen = new LevelScreen(this);
}

// Constructor:
// - Initializes the Game object with member variables
// - Sets up the window with the specified size, title, and window style
// - Sets the game clock
// - Initializes the current screen pointer to nullptr
Game::Game()
	: window(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
	, currentScreen(nullptr)
{
	// Window setup
	window.setMouseCursorVisible(false);

	// TODO: Setup screens
	//currentScreen = new LevelScreen(this);
}

// The main game loop that runs as long as the window is open
void Game::RunGameLoop()
{
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandling();
	}
}

// Handles events such as window close and key press
void Game::EventHandling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		// Close the game if escape is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

// Updates the game state
void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	// Update current screen
	//if (currentScreen != nullptr)
	//{
	//	currentScreen->Update(frameTime);
	//}

	// TODO: Handle changes to other screens
}

// Draws the game screen
void Game::Draw()
{
	window.clear();

	// Draw current screen
	//if (currentScreen != nullptr)
	//{
	//	currentScreen->Draw(window);
	//}

	window.display();
}

// Returns a pointer to the game window
sf::RenderWindow* Game::GetWindow()
{
	return &window;
}

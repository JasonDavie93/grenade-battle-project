//Classes
#include "Game.h"
#include "Screen.h"
#include "LevelScreen.h"

	Game::Game()
		//Initiallizer list
		: window(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close) // Create the game window with specified properties
		, gameClock() // Initialize the game clock
		, currentScreen(nullptr) // Set the current screen to null pointer initially
	{
		window.setMouseCursorVisible(false); // Hide the mouse cursor
		currentScreen = new LevelScreen(this); // Create a new LevelScreen and assign it as the current screen
	}

	void Game::RunGameLoop()
	{
		//Repeat as long as the window is open
		while (window.isOpen())
		{
			Update(); // Update the game logic
			Draw(); // Draw the game elements on the screen
			EventHandling(); // Handle user input events
		}
	}
	void Game::EventHandling()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close(); // Close the game if the window is closed

			
				//Close the game if esc is pressed
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close();  // Close the game if the Escape key is pressed
				}
		}
	}

	void Game::Update()
	{
		sf::Time frameTime = gameClock.restart(); // Get the elapsed time since the last frame
		//Update current screen
		if (currentScreen != nullptr)
		{
			currentScreen->Update(frameTime);  // Update the current screen with the elapsed frame time
		}

		//TODO: Handle changes to other screens
	}
	void Game::Draw()
	{
		window.clear(); // Clear the window
		//Draw current screen
		if (currentScreen != nullptr)
		{
			currentScreen->Draw(window);  // Draw the current screen on the window
		}

		window.display();  // Display the window contents

	}
	sf::RenderWindow* Game::GetWindow()
	{
		return &window; // Return a pointer to the game window
	}
#pragma once
// Default Libraries
#include <SFML/Graphics.hpp>
#include "LevelScreen.h"

// Forward declarations
class Screen;

class Game
{
public:
	Game();

	void RunGameLoop();

	void EventHandling();
	void Update();
	void Draw();

	sf::RenderWindow* GetWindow();

private:
	sf::RenderWindow window; // The game window
	sf::Clock gameClock; // Clock for measuring time

	Screen* currentScreen; // Pointer to the current screen
};

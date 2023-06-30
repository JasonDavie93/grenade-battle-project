#pragma once
//Default libraries
#include <SFML/Graphics.hpp>
//Classes
#include "OnScreenActor.h"
//Forward declarations
class LevelScreen;

class Platform
	: public OnScreenActor
{

public:
	Platform(const sf::Vector2f& positsion);
private:
	sf::RectangleShape shape;
	//Platform(sf::Vector2f newPosition);
	LevelScreen* currentLevel;
};
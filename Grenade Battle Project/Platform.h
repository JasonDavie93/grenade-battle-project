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
	Platform(sf::Vector2f newPosition);
private:
	LevelScreen* currentLevel;
};
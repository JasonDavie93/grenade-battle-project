#include "Platform.h"
#include "AssetManager.h"

Platform::Platform(const sf::Vector2f& Position)
	: OnScreenActor()
	, currentLevel()
{

	sprite.setTexture(AssetManager::RequestTexture("tile"));

	collisionOffset = sf::Vector2f(0.0f, 0.0f);
	collisionScale = sf::Vector2f(1.0f, 1.0f);
	SetPosition(Position);

}

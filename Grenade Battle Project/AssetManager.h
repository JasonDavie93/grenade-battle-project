#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <iostream>

class AssetManager
{
public:
	//static methods to request and manage assets
	// Request a texture by name
	static sf::Texture& RequestTexture(std::string textureName);
	// Request a font by name
	static sf::Font& RequestFont(std::string fontName);
	// Request a sound buffer by name
	static sf::SoundBuffer& RequestSoundBuffer(std::string bufferName);
	// Destroy all loaded assets
	static void DestroyAllAssets();


private:
	// Static maps to store loaded assets
	// Map to store loaded textures, using texture name as key
	static std::map<std::string, sf::Texture> textures;
	// Map to store loaded fonts, using font name as key
	static std::map<std::string, sf::Font> fonts;
	// Map to store loaded sound buffers, using buffer name as key
	static std::map<std::string, sf::SoundBuffer> soundBuffers;


};

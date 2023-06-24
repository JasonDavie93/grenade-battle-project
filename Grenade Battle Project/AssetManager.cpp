#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffers;

// Definitions of static members

// Initialize the static maps for storing assets
std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Font> AssetManager::fonts;
std::map<std::string, sf::SoundBuffer> AssetManager::soundBuffers;

// Request a texture by name
sf::Texture& AssetManager::RequestTexture(std::string textureName)
{
    auto pairFound = textures.find(textureName); // Search the textures map for the specified texture name

    if (pairFound != textures.end())
    {
        // We found an existing texture! Use it
        return pairFound->second; // Return the texture (value) associated with the texture name (key)
    }
    else
    {
        sf::Texture& newTexture = textures[textureName]; // Create a new entry in the textures map with the texture name as the key
        newTexture.loadFromFile("Assets/Graphics/" + textureName + ".png"); // Load the texture from the specified file
        return newTexture; // Return the newly loaded texture
    }
}

// Request a font by name
sf::Font& AssetManager::RequestFont(std::string fontName)
{
    auto pairFound = fonts.find(fontName); // Search the fonts map for the specified font name

    if (pairFound != fonts.end())
    {
        // We found an existing font! Use it
        return pairFound->second; // Return the font (value) associated with the font name (key)
    }
    else
    {
        sf::Font& newFont = fonts[fontName]; // Create a new entry in the fonts map with the font name as the key
        newFont.loadFromFile("Assets/Fonts/" + fontName + ".tff"); // Load the font from the specified file
        return newFont; // Return the newly loaded font
    }
}

// Request a sound buffer by name
sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string bufferName)
{
    auto pairFound = soundBuffers.find(bufferName); // Search the soundBuffers map for the specified buffer name

    if (pairFound != soundBuffers.end())
    {
        // We found an existing sound buffer! Use it
        return pairFound->second; // Return the sound buffer (value) associated with the buffer name (key)
    }
    else
    {
        sf::SoundBuffer& newSoundBuffer = soundBuffers[bufferName]; // Create a new entry in the soundBuffers map with the buffer name as the key
        newSoundBuffer.loadFromFile("Assets/Audio/" + bufferName + ".png"); // Load the sound buffer from the specified file
        return newSoundBuffer; // Return the newly loaded sound buffer
    }
}

// Destroy all loaded assets
void AssetManager::DestroyAllAssets()
{
    textures.clear(); // Clear the textures map, freeing the memory of the loaded textures
    fonts.clear(); // Clear the fonts map, freeing the memory of the loaded fonts
    soundBuffers.clear(); // Clear the soundBuffers map, freeing the memory of the loaded sound buffers
}

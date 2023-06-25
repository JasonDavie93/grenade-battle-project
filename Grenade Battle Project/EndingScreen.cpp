#include "EndingScreen.h"
#include "AssetManager.h"
#include "EaseOutFunction.h"

EndingScreen::EndingScreen(sf::RenderWindow* newWindow)
    : OnScreenActor()
    , background()
    , title()
    , message()
    , window(newWindow)
    , animatingIn(false)
    , animationClock()
    , player1win()
    , player2win()
{
    // Initializing member variables and setting up the background texture

    background.setTexture(AssetManager::RequestTexture("panel_blue"));
    background.setScale(6.0f, 6.0f);

    // Set up the title font and character size based on the winner
    title.setFont(AssetManager::RequestFont("dogica"));
    title.setCharacterSize(70);
    DecideWin(player1win, player2win);

    // Set up the message font, character size, and content
    message.setFont(AssetManager::RequestFont("dogica"));
    message.setCharacterSize(30);
    message.setString("Press Esc to quit");

    // Reset the position of the EndPanel
    ResetPosition();
}

void EndingScreen::Update(sf::Time frameTime)
{
    if (animatingIn)
    {
        // Animation logic to move the panel from its initial position to the final position

        float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
        float yPos = window->getSize().y;
        float finalYPos = window->getSize().y * 0.5f - background.getGlobalBounds().height * 0.5f;

        sf::Vector2f begin(xPos, yPos);
        sf::Vector2f change(0, finalYPos - yPos);
        float duration = 0.2f;
        float time = animationClock.getElapsedTime().asSeconds();

        // Calculate the new position based on easing function
        sf::Vector2f newPosition = EaseOutFunction::EaseOutQuad(begin, change, duration, time);
        SetPosition(newPosition);

        if (time >= duration)
        {
            SetPosition(begin + change);
            animatingIn = false;
        }
    }
}

void EndingScreen::Draw(sf::RenderTarget& target)
{
    // Draw the EndPanel components onto the target

    OnScreenActor::Draw(target);  // Assuming there's an implementation in the base class
    target.draw(background);
    target.draw(message);
    target.draw(title);
}

void EndingScreen::SetPosition(sf::Vector2f newPosition)
{
    // Set the position of the EndPanel and adjust the positions of the title and message

    background.setPosition(newPosition);

    // Center the title on the x-direction
    float titleX = background.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
    title.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

    // Center the message on the x and y directions
    float messageX = background.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
    float messageY = background.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;

    message.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));
}

void EndingScreen::StartAnimation()
{
    // Start the animation by setting the flag and restarting the animation clock

    animatingIn = true;
    animationClock.restart();
}

void EndingScreen::ResetPosition()
{
    // Reset the position of the EndPanel to the initial position

    float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
    float yPos = window->getSize().y;

    SetPosition(sf::Vector2f(xPos, yPos));
}
void EndingScreen::DecideWin(bool player1win, bool player2win)
{
    // Determine the winner based on the boolean values and set the title accordingly
    if (player1win)
    {
        title.setString("PLAYER 2 WINS");
    }
    else if (player2win)
    {
        title.setString("PLAYER 1 WINS");
    }
}

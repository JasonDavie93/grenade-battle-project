#include "EndingScreen.h"
#include "AssetManager.h"
#include "EasingFunction.h"

EndingScreen::EndingScreen(sf::RenderWindow* newWindow)
    : OnScreenActor()
    , backgroundOverLay()
    , title()
    , message()
    , window(newWindow)
    , animatingIn(false)
    , animationClock()
    , player1win()
    , player2win()
{

    backgroundOverLay.setTexture(AssetManager::RequestTexture("backgroundEndPanel"));
    backgroundOverLay.setScale(6.0f, 6.0f);

    // Set up the title font and character size based on the winner
    title.setFont(AssetManager::RequestFont("georgia"));
    title.setCharacterSize(70);
    DecideWin(player1win, player2win);

    // Set up the message font, character size, and content
    message.setFont(AssetManager::RequestFont("dogica"));
    message.setCharacterSize(30);
    message.setString("Press Esc to quit");
    message.setFillColor(sf::Color::Black);
    // Reset the position of the EndPanel
    ResetPosition();
}

void EndingScreen::Update(sf::Time frameTime)
{
    if (animatingIn)
    {
        // Animation logic to move the panel from its initial position to the final position

        float xPos = window->getSize().x * 0.5f - backgroundOverLay.getGlobalBounds().width * 0.5f;
        float yPos = window->getSize().y;
        float finalYPos = window->getSize().y * 0.5f - backgroundOverLay.getGlobalBounds().height * 0.5f;

        sf::Vector2f begin(xPos, yPos);
        sf::Vector2f change(0, finalYPos - yPos);
        float duration = 0.2f;
        float time = animationClock.getElapsedTime().asSeconds();

        // Calculate the new position based on easing function
        sf::Vector2f newPosition = EasingFunction::EaseOutQuad(begin, change, duration, time);
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
    // Draw the EndingScreen components onto the target

    OnScreenActor::Draw(target);  // Assuming there's an implementation in the base class
    target.draw(backgroundOverLay);
    target.draw(message);
    target.draw(title);
}

void EndingScreen::SetPosition(sf::Vector2f newPosition)
{
    // Set the position of the EndingScreen and adjust the positions of the title and message

    backgroundOverLay.setPosition(newPosition);

    // Center the title on the x-direction
    float titleX2 = backgroundOverLay.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
    title.setPosition(sf::Vector2f(newPosition.x + titleX2, newPosition.y + 50));

    // Center the message on the x and y directions
    float messageX2 = backgroundOverLay.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
    float messageY2 = backgroundOverLay.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;

    message.setPosition(sf::Vector2f(newPosition.x + messageX2, newPosition.y + messageY2));

}

void EndingScreen::StartAnimation()
{
    // Start the animation by setting the flag and restarting the animation clock

    animatingIn = true;
    animationClock.restart();
}

void EndingScreen::ResetPosition()
{
    // Reset the position of the EndScreen to the initial position

    float xPos = window->getSize().x * 0.5f - backgroundOverLay.getGlobalBounds().width * 0.5f;
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

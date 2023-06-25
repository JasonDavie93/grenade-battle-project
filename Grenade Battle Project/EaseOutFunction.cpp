#include "EaseOutFunction.h"

//Practical task - Easing function

sf::Vector2f EaseOutFunction::EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
    // Calculate the quadratic ease out value
    sf::Vector2f quadEaseOut = (-(change / (duration * duration)) * (time * time) + (2.0f * (change / duration) * time) + begin);

    // Return the calculated value
    return quadEaseOut;
}

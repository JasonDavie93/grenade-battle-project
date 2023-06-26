#include "EasingFunction.h"

//Practical task - Easing function

sf::Vector2f EasingFunction::EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time)
{
    sf::Vector2f quadEaseOut = (-(change / (duration * duration)) * (time * time) + (2.0f * (change / duration) * time) + begin);
    return quadEaseOut;
}
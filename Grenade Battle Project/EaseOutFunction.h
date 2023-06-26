#pragma once

#include <SFML/Graphics.hpp>

// This pragma directive ensures that the header file is included only once during compilation, preventing multiple inclusions and potential errors.

// Practical task - Easing function
namespace EaseOutFunction
{
    // This namespace contains various easing functions used for interpolation and animation.

    // EaseOutQuad is an easing function that applies quadratic easing to a vector of values.
    // It takes four parameters:
    //   - 'begin': the starting vector value
    //   - 'change': the vector value change or difference
    //   - 'duration': the total duration of the easing
    //   - 'time': the current time within the easing duration
    // It returns a new vector that represents the eased value at the given time.
    sf::Vector2f EaseOutQuad(sf::Vector2f begin, sf::Vector2f change, float duration, float time);
    // The function uses the Ease Out Quad equation to calculate the eased value. The easing equation provides a smooth transition between the starting and ending values.
}



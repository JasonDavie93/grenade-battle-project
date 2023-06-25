#pragma once
// Default libraries
#include <SFML/System.hpp>

// Namespace for VectorHelper functions
namespace VectorHelper
{
    // Calculates the squared magnitude of a 2D vector
    float SquareMagnitude(sf::Vector2f vec);

    // Calculates the magnitude of a 2D vector
    float Magnitude(sf::Vector2f vec);

    // Normalizes a 2D vector, making it unit length
    // Practical Task - Reflection
    sf::Vector2f Normalise(sf::Vector2f vec);

    // Calculates the dot product of two 3D vectors
    float Dot(sf::Vector3f a, sf::Vector3f b);

    // Calculates the dot product of two 2D vectors
    float Dot(sf::Vector2f a, sf::Vector2f b);

    // Calculates the cross product of two 3D vectors
    sf::Vector3f Cross(sf::Vector3f a, sf::Vector3f b);

    // Calculates the reflection of an incident vector off a surface with a given normal in 3D
    sf::Vector3f GetReflection(sf::Vector3f incident, sf::Vector3f normal);

    // Calculates the reflection of an incident vector off a surface with a given normal in 2D
    sf::Vector2f GetReflection(sf::Vector2f incident, sf::Vector2f normal);

    // Calculates the normal vector of a line defined by two points in 3D
    sf::Vector3f GetNormal(sf::Vector3f line1, sf::Vector3f line2);

    // Calculates the normal vector of a line defined by a point in 2D
    sf::Vector2f GetNormal(sf::Vector2f line);
};
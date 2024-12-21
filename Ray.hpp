#pragma once
#include "SFML/Graphics.hpp"
#include "Boundary.hpp"

double distance(sf::Vector2f a) {
	return sqrt((a.x * a.x) + (a.y * a.y));
}

sf::Vector2f normalize(sf::Vector2f a) {
	double len = distance(a);
	if (len == 0) return sf::Vector2f(0, 0);
	return sf::Vector2f(a.x / len, a.y / len);
}

class Ray {
public:
    sf::Vertex line[2];

    Ray(sf::Vector2f pos, float angle) {
        line[0].position = pos;
        line[1].position.x = pos.x + cos(angle) * 10.f;
        line[1].position.y = pos.y + sin(angle) * 10.f;
    }

    void lookAt(sf::Vector2f a) {
        sf::Vector2f direction = a - line[0].position;
        direction = normalize(direction);
        line[1].position = line[0].position + direction * 10.f;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(line, 2, sf::Lines);
    }

    void setOrigin(sf::Vector2f newOrigin) {
        sf::Vector2f direction = line[1].position - line[0].position;
        line[0].position = newOrigin;
        line[1].position = newOrigin + direction;
    }

    sf::Vector2f cast(Boundary& wall) {
        float x1 = wall.line[0].position.x;
        float y1 = wall.line[0].position.y;
        float x2 = wall.line[1].position.x;
        float y2 = wall.line[1].position.y;

        float x3 = line[0].position.x;
        float y3 = line[0].position.y;
        float x4 = line[1].position.x;
        float y4 = line[1].position.y;

        float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

        if (std::abs(den) < 0.0001f)
            return sf::Vector2f(-1, -1);

        float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
        float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

        if (t > 0 && t < 1 && u > 0) {
            return sf::Vector2f(
                x1 + t * (x2 - x1),
                y1 + t * (y2 - y1)
            );
        }

        return sf::Vector2f(-1, -1);
    }
};

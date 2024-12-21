#pragma once
#include "SFML/Graphics.hpp"

class Boundary {
public:
	sf::Vertex line[2];

	Boundary(sf::Vector2f a, sf::Vector2f b, sf::Color color) {
		line[0].position = a;
		line[1].position = b;

		line[0].color = color;
		line[1].color = color;
	}

	void draw(sf::RenderWindow& window) {
		window.draw(line, 2, sf::Lines);
	}
};
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boundary.hpp"
#include "Ray.hpp"
#include "Particle.hpp"
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 600), "Ray caster");

    sf::Event event;

    std::vector<Boundary> walls;
    walls.push_back(Boundary(sf::Vector2f(0, 0), sf::Vector2f(700, 0), sf::Color::White));
    walls.push_back(Boundary(sf::Vector2f(0, 0), sf::Vector2f(0, 600), sf::Color::White));
    walls.push_back(Boundary(sf::Vector2f(0, 600), sf::Vector2f(700, 600), sf::Color::White));
    walls.push_back(Boundary(sf::Vector2f(700, 600), sf::Vector2f(700, 0), sf::Color::White));

    srand(time(0));

    for (int i = 0; i < 5; i++) {
        walls.push_back(Boundary(sf::Vector2f(rand() % 700, rand() % 600), sf::Vector2f(rand() % 700, rand() % 600), sf::Color::White));
    }
    
    Particle particle(sf::Vector2f(350, 600));

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        particle.setPos(worldPos);

        window.clear();
        
        for (auto& wall : walls) {
            wall.draw(window);
        }

        particle.draw(window);
        particle.look(walls, window);
        window.display();
    }
}

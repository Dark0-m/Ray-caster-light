#include <SFML/Graphics.hpp>
#include <iostream>
#include "Boundary.hpp"
#include "Ray.hpp"
#include "Particle.hpp"
#include <random>

void get_lines_from_rect(sf::RectangleShape rectangle, std::vector<Boundary>& walls) {
    sf::Vector2f topLeft = rectangle.getPosition();
    sf::Vector2f topRight = topLeft + sf::Vector2f(rectangle.getSize().x, 0);
    sf::Vector2f bottomLeft = topLeft + sf::Vector2f(0, rectangle.getSize().y);
    sf::Vector2f bottomRight = topLeft + rectangle.getSize();

    walls.push_back(Boundary(topLeft, topRight, sf::Color::White));
    walls.push_back(Boundary(topRight, bottomRight, sf::Color::White));
    walls.push_back(Boundary(bottomRight, bottomLeft, sf::Color::White));
    walls.push_back(Boundary(bottomLeft, topLeft, sf::Color::White));
}

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
    
    Particle particle(sf::Vector2f(350, 600));

    sf::RectangleShape box1;
    box1.setPosition(300, 400);
    box1.setSize(sf::Vector2f(100, 100));

    sf::RectangleShape box2;
    box2.setPosition(600, 200);
    box2.setSize(sf::Vector2f(100, 100));

    sf::RectangleShape box3;
    box3.setPosition(200, 300);
    box3.setSize(sf::Vector2f(100, 100));

    get_lines_from_rect(box1, walls);
    get_lines_from_rect(box2, walls);
    get_lines_from_rect(box3, walls);
    

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

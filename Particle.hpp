class Particle {
public:
    sf::Vector2f pos;
    std::vector<Ray> rays;

    Particle(sf::Vector2f window_size) {
        pos = window_size / 2.f;

        for (int a = 0; a < 360; a += 10) {
            float angleRadians = a * (3.14159265359f / 180.f);
            rays.emplace_back(pos, angleRadians);
        }
    }

    void setPos(sf::Vector2f a) {
        pos = a;
        for (auto& ray : rays) {
            ray.setOrigin(pos);
        }
    }

    void look(std::vector<Boundary>& walls, sf::RenderWindow& window) {
        for (auto& ray : rays) {
            sf::Vector2f closest(-1, -1);
            float record = INFINITY;

            for (auto& wall : walls) {
                sf::Vector2f pt = ray.cast(wall);

                if (pt != sf::Vector2f(-1, -1)) {
                    float dis = static_cast<float>(sqrt(pow(pt.x - pos.x, 2) + pow(pt.y - pos.y, 2)));

                    if (dis < record) {
                        record = dis;
                        closest = pt;
                    }
                }
            }

            if (closest != sf::Vector2f(-1, -1)) {
                sf::Vertex line[2];
                line[0].position = pos;
                line[0].color = sf::Color::White;
                line[1].position = closest;
                line[1].color = sf::Color::White;

                window.draw(line, 2, sf::Lines);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape circle(7.f);
        circle.setOrigin(7.f, 7.f);
        circle.setPosition(pos);
        circle.setFillColor(sf::Color::White);

        window.draw(circle);

        for (auto& ray : rays) {
            ray.draw(window);
        }
    }
};

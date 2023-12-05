#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle Movement");
    sf::CircleShape circle(50.0f);
    circle.setFillColor(sf::Color::Red);

    sf::Vector2f position(400, 300);
    sf::Vector2f velocity(0, 0);
    sf::Vector2f acceleration(0, 0);

    const float maxSpeed = 200.0f;
    const float accelRate = 10.0f;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            acceleration.x = -accelRate;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            acceleration.x = accelRate;
        }
        else {
            acceleration.x = 0;
        }

        velocity += acceleration * deltaTime;
        if (std::abs(velocity.x) > maxSpeed) {
            velocity.x = maxSpeed * ((velocity.x > 0) - (velocity.x < 0));
        }
        position += velocity * deltaTime;

        if (position.x < 0) {
            position.x = 0;
            velocity.x = 0;
        }
        if (position.x + circle.getRadius() * 2 > window.getSize().x) {
            position.x = window.getSize().x - circle.getRadius() * 2;
            velocity.x = 0;
        }

        circle.setPosition(position);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}

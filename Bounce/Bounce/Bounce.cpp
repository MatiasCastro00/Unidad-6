#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bouncing Ball");
    sf::CircleShape ball(50.0f); 
    ball.setFillColor(sf::Color::Blue);

    sf::Vector2f position(400, 0); 
    sf::Vector2f velocity(0, 0); 
    const float gravity = 980.0f; 
    const float bounceFactor = 0.7f; 

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();


        velocity.y += gravity * deltaTime;


        position += velocity * deltaTime;


        if (position.y + ball.getRadius() * 2 > window.getSize().y) {
            position.y = window.getSize().y - ball.getRadius() * 2;
            velocity.y = -velocity.y * bounceFactor;
        }

        ball.setPosition(position);

        window.clear();
        window.draw(ball);
        window.display();
    }

    return 0;
}

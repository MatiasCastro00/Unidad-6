#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle Animation");
    sf::CircleShape circle(50.0f); 
    circle.setFillColor(sf::Color::Green);

    float V0 = 0.4f; 
    float aceleration = 1.05;
    float Vfinal = 5.0f; 
    float currentSpeed = V0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        circle.move(currentSpeed, 0);

        if (circle.getPosition().x > window.getSize().x) {
            circle.setPosition(-circle.getRadius() * 2, circle.getPosition().y);
            if (currentSpeed < Vfinal) {
                currentSpeed *= aceleration;
            }
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}

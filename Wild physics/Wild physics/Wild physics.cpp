#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cstdlib> 

using namespace std;
using namespace sf;

Texture crosshairTexture;
Texture etTexture;
Sprite crosshair;

class Crosshair {
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	Crosshair(const string& texturePath) {
		if (!texture.loadFromFile(texturePath)) {
		}
		sprite.setTexture(texture);
		sprite.setScale(0.5f, 0.5f);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}

	void updatePosition(const Vector2i& mousePosition) {
		sprite.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}
};
class Enemy {
private:
	sf::Sprite sprite;
	Vector2f velocity;
	float acceleration;
	bool useGravity;

	void updateMovement(float deltaTime, int width, int height) {
		if (useGravity) {

			velocity.y += acceleration * deltaTime;
		}

		sprite.move(velocity * deltaTime);


		if (sprite.getPosition().x < 0 || sprite.getPosition().x > width) {
			velocity.x = -velocity.x;
		}
		if (sprite.getPosition().y < 0 || sprite.getPosition().y > height) {
			velocity.y = -velocity.y;
		}
	}

public:
	Enemy(const Texture& texture, float x, float y, bool gravity = false)
		: sprite(texture), velocity(Vector2f(100.0f, 0)), acceleration(500.0f), useGravity(gravity) {
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setPosition(x, y);
		sprite.setScale(0.1f, 0.1f);

		if (!useGravity) {
			velocity.x = static_cast<float>((rand() % 200) - 100); 
		}
	}

	void update(float deltaTime, int width, int height) {
		updateMovement(deltaTime, width, height);
	}

	const Sprite& getSprite() const {
		return sprite;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}
};


class EnemyManager {
private:
	std::unique_ptr<Enemy> enemy;
	sf::Texture texture;
	int score;

	void createEnemy(int width, int height) {
		float randomX = static_cast<float>(rand() % width);
		float randomY = static_cast<float>(rand() % height);
		bool useGravity = rand() % 2 == 0; // Elegir aleatoriamente entre MRU y MRUA
		enemy = std::make_unique<Enemy>(texture, randomX, randomY, useGravity);
	}

public:
	EnemyManager(const string& texturePath) : score(0) {
		if (!texture.loadFromFile(texturePath)) {
			// Handle error
		}
	}

	void initialize(int width, int height) {
		createEnemy(width, height);
	}

	void update(float deltaTime, int width, int height) {
		if (!enemy) {
			createEnemy(width, height);
			score++;
			cout << "Score: " << score << endl;
		}
		else {
			enemy->update(deltaTime, width, height);
		}
	}

	void draw(RenderWindow& window) {
		if (enemy) {
			enemy->draw(window);
		}
	}

	void checkHits(const Vector2i& mousePosition) {
		if (enemy && enemy->getSprite().getGlobalBounds().contains(Vector2f(mousePosition))) {
			enemy.reset();
		}
	}
};


int main() {
	int width = 1000;
	int height = 800;
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "Sniper");

	Crosshair crosshair("crosshair.png");
	EnemyManager enemyManager("et.png");
	enemyManager.initialize(width, height);

	sf::Clock clock;

	while (App.isOpen()) {
		sf::Event event;
		while (App.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				App.close();
			}

			Vector2i mousePos = Mouse::getPosition(App);

			if (event.type == Event::MouseButtonPressed) {
				if (event.mouseButton.button == Mouse::Left) {
					enemyManager.checkHits(mousePos);
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();
		enemyManager.update(deltaTime, width, height);

		App.clear();
		App.setMouseCursorVisible(false);
		enemyManager.draw(App);
		crosshair.updatePosition(Mouse::getPosition(App));
		crosshair.draw(App);
		App.display();
	}
	return 0;
}
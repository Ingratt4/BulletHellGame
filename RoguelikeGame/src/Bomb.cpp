#include "Headers/Bomb.h";

Bomb::Bomb(sf::Vector2f startPos, sf::Vector2f targetPos) {
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(startPos);

	sf::Vector2f direction = targetPos - startPos;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	velocity = (direction / length) * 200.f;

	explosionTimer = 2.0f;
	}

	void Bomb::update(float deltaTime){
		if (!exploded) {
			shape.move(velocity * deltaTime);
			explosionTimer -= deltaTime;
			if (explosionTimer <= 0) {
				explode();
			}
		}
	}

	void Bomb::explode() {
		exploded = true;
		shape.setFillColor(sf::Color::Yellow);
	}
	void Bomb::draw(sf::RenderWindow& window) {
		window.draw(shape);
	}

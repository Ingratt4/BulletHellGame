#include "headers\BulletManager.h"

Bullet::Bullet(const sf::Vector2f& pos, const sf::Vector2f& vel) :
	velocity(vel) {
	shape.setRadius(5.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(pos);
}
	


void BulletManager::spawnBullet(const sf::Vector2f& position, const sf::Vector2f& target) {
	sf::Vector2f direction = target - position;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) direction /= length;

	sf::Vector2f velocity = direction * bulletSpeed;
	bullets.emplace_back(position, velocity);
}

void BulletManager::update(float dt) {
	for (auto it = bullets.begin(); it != bullets.end(); ) {
		it->shape.move(it->velocity * dt);
		sf::Vector2f pos = it->shape.getPosition();

		if (pos.x < 0 || pos.x > MAX_WIDTH || pos.y < 0 || pos.y > MAX_HEIGHT) {
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}
}

void BulletManager::draw(sf::RenderWindow& window) const {
	for (const auto& bullet : bullets) {
		window.draw(bullet.shape);
	}
}

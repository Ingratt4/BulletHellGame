#include "headers\BulletManager.h"

Bullet::Bullet(const sf::Vector2f& pos, const sf::Vector2f& vel, float bulletDamage, BulletOwner owner) :
	velocity(vel), owner(owner), bulletDamage(bulletDamage) {
	shape.setRadius(5.f);
	shape.setFillColor(owner == BulletOwner::Player ? sf::Color::Green : sf::Color::Red);
	shape.setPosition(pos);

}
	


void BulletManager::spawnBullet(const sf::Vector2f& position, const sf::Vector2f& target, BulletOwner owner, float damage) {

	sf::Vector2f direction = target - position;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) direction /= length;

	sf::Vector2f velocity = direction * bulletSpeed;
	bullets.emplace_back(position, velocity, damage, owner);
}

void BulletManager::update(float dt, std::vector<Damageable*>& targets)
{
	for (auto it = bullets.begin(); it != bullets.end(); ) {
		it->shape.move(it->velocity * dt);

		// Check if bullet goes offscreen
		sf::Vector2f pos = it->shape.getPosition();
		if (pos.x < 0 || pos.x > MAX_WIDTH || pos.y < 0 || pos.y > MAX_HEIGHT) {
			it = bullets.erase(it);
			continue;
		}

		// Check for collisions
		bool hit = false;
		checkCollision(*it, targets, hit);

		if (hit) {
			it = bullets.erase(it); // Remove bullet if it hit something
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

void BulletManager::checkCollision(Bullet& bullet, std::vector<Damageable*>& targets, bool& hit)
{
	for (Damageable* target : targets) {
		if (target->getBounds().findIntersection(bullet.shape.getGlobalBounds())) {
			target->takeDamage(bullet.bulletDamage);
			hit = true;
			return;
		}
	}

}



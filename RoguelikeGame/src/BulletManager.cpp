#include "headers\BulletManager.h"
#include <iostream>



Bullet::Bullet(const sf::Vector2f& pos, const sf::Vector2f& vel, float bulletDamage, BulletOwner owner)
	: velocity(vel), owner(owner), bulletDamage(bulletDamage) {
	std::cout << "[Bullet] Constructing bullet\n";
	shape.setRadius(5.f);
	shape.setFillColor(owner == BulletOwner::Player ? sf::Color::Green : sf::Color::Red);
	shape.setPosition(pos);
}

	


BulletManager::BulletManager()
{
	std::cout << "BulletManager constructor called\n";
	bullets.reserve(100);
}

void BulletManager::spawnBullet(const sf::Vector2f& position, const sf::Vector2f& target, BulletOwner owner, float damage) {

	sf::Vector2f direction = target - position;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) direction /= length;

	sf::Vector2f velocity = direction * bulletSpeed;
	std::cout << "[spawnBullet] position: " << position.x << ", " << position.y << "\n";
	std::cout << "[spawnBullet] target: " << target.x << ", " << target.y << "\n";
	std::cout << "[spawnBullet] velocity: " << velocity.x << ", " << velocity.y << "\n";

	bullets.emplace_back(std::make_unique<Bullet>(position, velocity, damage, owner));
}

void BulletManager::update(float dt, std::vector<Damageable*>& targets)
{
	for (auto it = bullets.begin(); it != bullets.end(); ) {
		(*it)->shape.move((*it)->velocity * dt);

		// Check if bullet goes offscreen
		sf::Vector2f pos = (*it)->shape.getPosition();
		if (pos.x < 0 || pos.x > MAX_WIDTH || pos.y < 0 || pos.y > MAX_HEIGHT) {
			it = bullets.erase(it);
			continue;
		}

		// Check for collisions
		bool hit = false;
		if (targets.empty()) {
			std::cout << "[BulletManager::update] targets is EMPTY!\n";
		}
		else {
			for (auto* ptr : targets) {
				if (!ptr) {
					std::cout << "[BulletManager::update] Found nullptr in targets!\n";
				}
				else {
					std::cout << "[BulletManager::update] target pointer is valid\n";
				}
			}
		}

		checkCollision(*(*it), targets, hit);

		if (hit) {
			
			it = bullets.erase(it); // Remove bullet if it hit something
		}
		else {
			++it;
		}
	}
}

void BulletManager::checkCollision(Bullet& bullet, std::vector<Damageable*>& targets, bool& hit)
{
	std::cout << "[BulletManager::checkCollision] Checking bullet collision with " << targets.size() << " targets.\n";

	for (Damageable* target : targets) {
		if (!target) {
			std::cout << "[BulletManager::checkCollision] Skipping null target pointer.\n";
			continue;
		}

		try {
			sf::FloatRect targetBounds = target->getBounds();
			sf::FloatRect bulletBounds = bullet.shape.getGlobalBounds();

			if (targetBounds.findIntersection(bulletBounds)) {
				std::cout << "[BulletManager::checkCollision] Bullet collided with target!\n";

				if (target->isParryActive()) {
					auto parryBounds = target->getParryBounds();
					if (parryBounds.has_value() &&
						parryBounds->contains(bullet.shape.getPosition())) {

						std::cout << "[BulletManager::checkCollision] Bullet Parried!\n";
						reflectEnemyProjectile(bullet);

						bulletTransferQueue.push(std::make_unique<Bullet>(bullet));

						continue;
					}


				}

				// Only deal damage if not parried
				
				if ((bullet.owner == BulletOwner::Player && target->isEnemy()) ||
					(bullet.owner == BulletOwner::Enemy && target->isPlayer())) {

					target->takeDamage(bullet.bulletDamage);
					hit = true;
					return;
				}
				else {
					std::cout << "[BulletManager::checkCollision] Bullet hit same-team target, ignoring damage.\n";
				}
			}
		}
		catch (...) {
			std::cout << "[BulletManager::checkCollision] Exception occurred during collision check. Target might be corrupted.\n";
		}
	}

}

void BulletManager::reflectEnemyProjectile(Bullet& bullet)
{
	if (bullet.owner == BulletOwner::Enemy) {
		bullet.owner = BulletOwner::Player;
		bullet.velocity = -(bullet.velocity);
	}

}

std::queue<std::unique_ptr<Bullet>> BulletManager::bulletTransferCheck() {
	std::queue<std::unique_ptr<Bullet>> temp;
	if (bulletTransferQueue.size() >= 1) {
		while (!bulletTransferQueue.empty()) {
			temp.push(std::move(bulletTransferQueue.front()));
			bulletTransferQueue.pop();
		}
	}
	return temp; 
}


void BulletManager::insertBullet(std::unique_ptr<Bullet> bullet) {
	bullets.emplace_back(std::move(bullet));
}



void BulletManager::draw(sf::RenderWindow& window) const {
	for (const auto& bullet : bullets) {
		window.draw(bullet->shape); 
	}
}
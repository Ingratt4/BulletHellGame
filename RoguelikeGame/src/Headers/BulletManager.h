#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "SFML\Graphics.hpp";
#include "Bullet.h";
#include "Damageable.h"
#include <queue>

class BulletManager {


public:
	BulletManager();
	void spawnBullet(const sf::Vector2f& position, const sf::Vector2f& target, BulletOwner owner, float damage);
	void update(float dt, std::vector<Damageable*>& targets);
	void draw(sf::RenderWindow& window) const;
	void checkCollision(Bullet& bullet, std::vector<Damageable*>& targets, bool& hit);
	void reflectEnemyProjectile(Bullet& bullet);
	std::queue<std::unique_ptr<Bullet>> bulletTransferCheck();
	void insertBullet(std::unique_ptr<Bullet> bullet);


private:
	std::vector<std::unique_ptr<Bullet>> bullets;
	std::queue<std::unique_ptr<Bullet>> bulletTransferQueue;

	float bulletSpeed = 500.f;
	const float MAX_HEIGHT = 1080.f;
	const float MAX_WIDTH = 1920.f;
};
#endif // BULLETMANAGER_H
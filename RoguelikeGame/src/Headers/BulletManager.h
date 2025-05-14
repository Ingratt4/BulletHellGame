#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "SFML\Graphics.hpp";
#include "Bullet.h";
#include "Damageable.h"

class BulletManager {

public:

	void spawnBullet(const sf::Vector2f& position, const sf::Vector2f& target, BulletOwner owner, float damage);
	void update(float dt, std::vector<Damageable*>& targets);
	void draw(sf::RenderWindow& window) const;
	void checkCollision(Bullet& bullet, std::vector<Damageable*>& targets, bool& hit);


private:
	std::vector<Bullet> bullets;
	float bulletSpeed = 500.f;
	const float MAX_WIDTH = 1920.f;
	const float MAX_HEIGHT = 1080.f;

};
#endif // BULLETMANAGER_H
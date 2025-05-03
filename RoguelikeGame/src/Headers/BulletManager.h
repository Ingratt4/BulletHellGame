#include "SFML\Graphics.hpp";
#include "Bullet.h";

class BulletManager {

public:

	void spawnBullet(const sf::Vector2f& position, const sf::Vector2f& target);
	void update(float dt);
	void draw(sf::RenderWindow& window) const;


private:
	std::vector<Bullet> bullets;
	float bulletSpeed = 500.f;
	const float MAX_WIDTH = 1920.f;
	const float MAX_HEIGHT = 1080.f;

};
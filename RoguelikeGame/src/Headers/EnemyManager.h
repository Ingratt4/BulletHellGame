#include "SFML\Graphics.hpp"
#include "Enemy.h"
#include "BulletManager.h"

class EnemyManager {
public:
	void deleteEnemy();
	void spawnEnemy(const sf::Vector2f& position);
	void EnemyManager::update(const sf::Vector2f& playerPos, BulletManager& enemyBulletManager, float dt);
	void draw(sf::RenderWindow& window) const;
	std::vector<Enemy>& getEnemies();
private:
	std::vector<Enemy> enemies;
	int enemyLimit = 1;


};
#include "SFML\Graphics.hpp"
#include "Enemy.h"

class EnemyManager {
public:
	void deleteEnemy();
	void addEnemy();
private:
	std::vector<Enemy> enemies;


};
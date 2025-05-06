#include <SFML/Graphics.hpp>
#include "AttackRange.h"


class Enemy {
public:
	Enemy();
	void move(float dx, float dy);
	void moveTowardsPlayer(sf::Vector2f playerPos, float dt);
	void draw(sf::RenderWindow& window);
	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	void checkAttackArea();
	void attack(sf::Vector2f playerPos, float dt);
	bool isPlayerInAttackRange(sf::Vector2f playerPos);
private:
	sf::RectangleShape body;
	AttackRange attackRange;
	int health;
	float speed;
};
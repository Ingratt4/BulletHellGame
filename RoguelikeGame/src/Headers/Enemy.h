#ifndef ATTACK_RANGE_H
#define ATTACK_RANGE_H



#include <SFML/Graphics.hpp>
#include "AttackRange.h";
#include "Damageable.h";


class Enemy : public Damageable{
public:
	Enemy();
	void move(float dx, float dy);
	void moveTowardsPlayer(sf::Vector2f playerPos, float dt);
	void draw(sf::RenderWindow& window) const;
	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	void checkAttackArea();
	void attack(sf::Vector2f playerPos, float dt);
	bool isPlayerInAttackRange(sf::Vector2f playerPos);
	float getAttackCooldown();
	void setAttackCooldown(float cooldown);
	int getHealth() const;
	void takeDamage(float damage) override;
	sf::FloatRect getBounds() const override;
	bool isDead();
	void updateHealthbarLocation();


	bool isEnemy() const override;
	bool isPlayer() const override;

private:
	sf::RectangleShape body;
	AttackRange attackRange;
	sf::RectangleShape redHealth;
	sf::RectangleShape greenHealth;
	int health;
	float speed;
	float attackCooldown;
	bool dead = false;
};

#endif // ATTACK_RANGE_H
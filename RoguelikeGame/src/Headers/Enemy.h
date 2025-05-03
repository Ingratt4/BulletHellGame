#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Bomb.h";

class Enemy {
public:
	Enemy();
	void move(float dx, float dy);
	void draw(sf::RenderWindow& window);
	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	void checkAttackArea();
private:
	sf::RectangleShape body;
	sf::CircleShape attackArea;
	Bomb bomb;
	int health;
};
#define BOMB_H

#include "SFML\Graphics.hpp";
class Bomb {

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	float explosionTimer;
	bool exploded = false;

public:
	Bomb(sf::Vector2f startPos, sf::Vector2f targetPos);
	void update(float deltaTime);
	void explode();
	void draw(sf::RenderWindow& window);
};
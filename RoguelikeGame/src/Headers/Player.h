#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
	Player();
	void move(float dx, float dy);
	void draw(sf::RenderWindow& window);
	const sf::Vector2f getPosition();
private:
	sf::RectangleShape body;
	int health;
};
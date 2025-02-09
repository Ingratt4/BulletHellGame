#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
	Player();
	void move(float dx, float dy);
	void draw(sf::RenderWindow& window);
	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
private:
	sf::RectangleShape body;
	int health;
};
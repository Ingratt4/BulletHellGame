#define GUN_H
#include <SFML/Graphics.hpp>

class Gun {
public:
	Gun();
	void draw(sf::RenderWindow& window);
	float getSpeed();
	sf::CircleShape bullet;


private:
	float bulletSpeed;


};

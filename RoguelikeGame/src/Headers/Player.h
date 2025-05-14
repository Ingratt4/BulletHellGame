#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Damageable.h";

class Player : public Damageable {
public:
	Player();
	void move(float dx, float dy);
	void draw(sf::RenderWindow& window);
	const sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pos);
	void updateHealth();
	void updateHealthbarLocation();
	void takeDamage(float damage) override;
	sf::FloatRect getBounds() const override;
	
private:
	sf::RectangleShape body;
	sf::RectangleShape redHealth;
	sf::RectangleShape greenHealth;
	sf::FloatRect hitbox;
	int health;
};
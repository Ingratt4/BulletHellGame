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
	void updateParryAreaLocation();
	void takeDamage(float damage) override; 
	bool isParryActive() const override;
	std::optional<sf::FloatRect> getParryBounds() const override;
	sf::FloatRect getBounds() const override;
	bool isDead();
	void update(float dt);
	void parry(float dt);
	void dash(float dx, float dy);
	void tryStartParry();

	bool isEnemy() const override;
	bool isPlayer() const override;

private:
	sf::RectangleShape body;
	sf::RectangleShape redHealth;
	sf::RectangleShape greenHealth;
	
	sf::FloatRect hitbox;

	float parryDuration =0.f; 
	float parryCooldown =0.f;
	sf::CircleShape parryArea;
	bool isParrying = false;
	bool canParry = true;

	int health;
	bool dead = false;
};
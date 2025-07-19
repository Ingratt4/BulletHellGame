#pragma once
#include <SFML/Graphics.hpp>



class Damageable {
public:

	virtual void takeDamage(float damage) = 0;
	virtual sf::FloatRect getBounds() const = 0;
	virtual ~Damageable() = default;
	virtual bool isParryActive() const { return false; }
	virtual std::optional<sf::FloatRect> getParryBounds() const { return std::nullopt; }
	virtual bool isEnemy() const = 0;
	virtual bool isPlayer() const = 0;

		
};


#pragma once
#include <SFML/Graphics.hpp>

class Damageable {
public:

	virtual void takeDamage(float damage) = 0;
	virtual sf::FloatRect getBounds() const = 0;
	virtual ~Damageable() = default;
};
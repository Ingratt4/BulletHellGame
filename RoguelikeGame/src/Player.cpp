#include "Headers/Player.h"
#include "iostream";

Player::Player() : body(sf::Vector2f(20.f, 80.f)), parryArea(80), health(100) {
    body.setFillColor(sf::Color::Blue);
    body.setOrigin(sf::Vector2f(body.getSize().x / 2.f, body.getSize().y / 2.f));
    body.setPosition(sf::Vector2f(100.f, 100.f));

    hitbox = body.getGlobalBounds();

    redHealth.setSize(sf::Vector2f(50, 20));
    redHealth.setOrigin(sf::Vector2f(redHealth.getSize().x / 2, redHealth.getSize().y / 2));
    redHealth.setFillColor(sf::Color::Red);

    greenHealth.setSize(sf::Vector2f(50, 20));
    greenHealth.setOrigin(sf::Vector2f(greenHealth.getSize().x / 2, greenHealth.getSize().y / 2));
    greenHealth.setFillColor(sf::Color::Green);


    parryArea.setOrigin(sf::Vector2f(parryArea.getRadius(), parryArea.getRadius()));
	parryArea.setFillColor(sf::Color::Magenta);
	parryArea.setPosition(body.getPosition());  // now it's truly centered

    updateHealthbarLocation();
    updateParryAreaLocation();
}



    void Player::move(float dx, float dy) {
        body.move(sf::Vector2(dx,dy));
        hitbox = body.getGlobalBounds();
        updateHealthbarLocation();
		updateParryAreaLocation();

    }

    void Player::draw(sf::RenderWindow& window) {
        window.draw(parryArea);
        window.draw(body);
        window.draw(redHealth);
        window.draw(greenHealth);
    }

    const sf::Vector2f Player::getPosition() {
        return sf::Vector2f(body.getPosition().x, body.getPosition().y);
    }
    void Player::setPosition(sf::Vector2f pos) {
        body.setPosition(pos);
    }

    void Player::updateHealth() {

    }

    void Player::updateHealthbarLocation() {
        redHealth.setPosition(body.getPosition() + (sf::Vector2f(0, -70)));
        greenHealth.setPosition(body.getPosition() + (sf::Vector2f(0, -70)));
    }

    sf::FloatRect Player::getBounds() const
    {
        return hitbox;
    }
    void Player::update(float dt) {
		updateHealthbarLocation();
		updateParryAreaLocation();
        if (health <= 0 && !dead) {
            dead = true;
        }

        float healthPercent = static_cast<float>(health) / 100.f;
        greenHealth.setSize(sf::Vector2f(50.f * healthPercent, 20.f));
    }

    void Player::updateParryAreaLocation() {
        parryArea.setPosition(body.getPosition());
    }

	void Player::parry(float dt)
	{
      
		if (isParrying) {
            std::cout << "Parrying!" << "\n";
			parryDuration += dt;
			parryArea.setFillColor(sf::Color::Red);

			if (parryDuration >= 0.5f) {
				isParrying = false;
				canParry = false;
				parryDuration = 0.f;  // reset for next time
				parryArea.setFillColor(sf::Color::Magenta);
			}
		}

		if (!canParry) {
			parryCooldown += dt;
			if (parryCooldown >= 1.f) {
				canParry = true;
				parryCooldown = 0.f;
			}
		}
	}

    void Player::dash(float dx, float dy)
    {
        body.move(sf::Vector2f(dx, dy));

    }


	void Player::tryStartParry() {
		if (canParry && !isParrying) {
			isParrying = true;
			parryDuration = 0.f;
            parryCooldown = 0.f;
		}
	}


	bool Player::isEnemy() const
	{
        return false;
	}
    bool Player::isPlayer() const
    {
        return true;
    }

	bool Player::isDead()
    {
        return dead;
    }
    void Player::takeDamage(float damage) {
        health -= damage;

        if (health < 0) {
            health = 0;
            dead = true;
        }
        std::cout << "Player health: " << health << "\n";
    }

    
	bool Player::isParryActive() const
	{
        return isParrying;

	}

	std::optional<sf::FloatRect> Player::getParryBounds() const
	{
        return parryArea.getGlobalBounds();
	}










#include "Headers/Player.h"
#include "iostream";

Player::Player() : body(sf::Vector2f(20.f, 80.f)), health(100) {
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

    updateHealthbarLocation();
}



    void Player::move(float dx, float dy) {
        body.move(sf::Vector2(dx,dy));
        hitbox = body.getGlobalBounds();
        updateHealthbarLocation();
    }

    void Player::draw(sf::RenderWindow& window) {
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
    void Player::takeDamage(float damage) {
        health -= damage;

        if (health < 0) {
            health = 0;
        }
        std::cout << "Player health: " << health << "\n";
    }

    



#include "Headers/Player.h"

Player::Player() : body(sf::Vector2f(50.f, 50.f)), health(100) {
    body.setFillColor(sf::Color::Green);
    body.setPosition(sf::Vector2f(100.f, 100.f));
    body.setOrigin(sf::Vector2f(body.getSize().x / 2.f, body.getSize().y / 2.f)); // Correctly access x and y
}


    void Player::move(float dx, float dy) {
        body.move(sf::Vector2(dx,dy));
    }

    void Player::draw(sf::RenderWindow& window) {
        window.draw(body);
    }
    const sf::Vector2f Player::getPosition() {
        return sf::Vector2f(body.getPosition().x, body.getPosition().y);
    }



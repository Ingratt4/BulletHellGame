#include "Headers/Gun.h"

Gun::Gun() : bullet(5.f) {
    bulletSpeed = 2000;
    bullet.setFillColor(sf::Color::Red);
    //body.setPosition(sf::Vector2(10.f, 10.f));
    bullet.setOrigin(sf::Vector2f(10 / 2, 10 / 2)); //hardcoded value, should be changed.
}

void Gun::draw(sf::RenderWindow& window) {
    window.draw(bullet);
}
float Gun::getSpeed() {
    return bulletSpeed;
}
#include "Headers/Button.h"

Button::Button() {
    shape.setSize({ 0.f, 0.f });
    shape.setFillColor(sf::Color::Transparent);
}

Button::Button(sf::Vector2f size, sf::Vector2f position) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Blue);
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

bool Button::isHovered(sf::RenderWindow& window) const {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return shape.getGlobalBounds().contains(mousePos);
}

bool Button::isClicked(sf::RenderWindow& window, const sf::Event& event) const {
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return shape.getGlobalBounds().contains(mousePos);
    }
    return false;
}

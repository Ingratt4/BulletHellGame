#ifndef BUTTON_H
#define BUTTON_H

#pragma once
#include <SFML/Graphics.hpp>

class Button {
public:
    Button();
    Button(sf::Vector2f size, sf::Vector2f position);

    void draw(sf::RenderWindow& window) const;
    bool isHovered(sf::RenderWindow& window) const;
    bool isClicked(sf::RenderWindow& window, const sf::Event& event) const;

private:
    sf::RectangleShape shape;
};












#endif

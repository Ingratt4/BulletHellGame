#include <SFML/Graphics.hpp>


struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity);
       
};

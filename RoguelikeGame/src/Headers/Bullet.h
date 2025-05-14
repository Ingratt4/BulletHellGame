#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

enum class BulletOwner { Player, Enemy };

struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float bulletDamage;
    BulletOwner owner;

    Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity, float bulletDamage, BulletOwner owner);
       
};

#endif // BULLET_H
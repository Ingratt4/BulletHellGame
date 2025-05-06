#include "Headers\Enemy.h"

Enemy::Enemy() : body(sf::Vector2f(30.f, 30.f)), attackRange(200.f) {
    body.setFillColor(sf::Color::Magenta);
    attackRange.setFillColor(sf::Color(255, 0, 0, 100));
    attackRange.setOrigin(sf::Vector2f(attackRange.getRadius(), attackRange.getRadius()));
    health = 100;
    speed = 50;
}

void Enemy::moveTowardsPlayer(sf::Vector2f playerPos, float dt)
{
    if (!isPlayerInAttackRange(playerPos)) {
        sf::Vector2f direction = playerPos - body.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
            direction /= length; // Now direction is unit vector

        sf::Vector2f velocity = direction * speed;
        body.move(velocity * dt);
        attackRange.setPosition(body.getPosition());
    }
    else {
        attack(playerPos,dt);
    }


}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(attackRange);
    window.draw(body);
    
}

const sf::Vector2f Enemy::getPosition()
{
    return body.getPosition();
}

void Enemy::setPosition(sf::Vector2f pos) {
	body.setPosition(pos);

   
}

void Enemy::attack(sf::Vector2f playerPos, float dt)
{
    sf::Vector2f direction = playerPos - body.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    sf::Vector2f velocity = direction * speed;
    
}



bool Enemy::isPlayerInAttackRange(sf::Vector2f playerPos)
{
    if (attackRange.contains(playerPos)) {
        return true;
    }
    return false;
}


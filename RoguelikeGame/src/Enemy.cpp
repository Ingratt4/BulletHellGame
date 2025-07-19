#include "Headers\Enemy.h"
#include <iostream>

Enemy::Enemy() : Damageable(), body(sf::Vector2f(30.f, 30.f)), attackRange(200.f) {
    body.setFillColor(sf::Color::Magenta);
    attackRange.setFillColor(sf::Color(255, 0, 0, 100));
    attackRange.setOrigin(sf::Vector2f(attackRange.getRadius(), attackRange.getRadius()));
    health = 100;
    speed = 50;
    attackCooldown = 1;

    redHealth.setSize(sf::Vector2f(50, 20));
    redHealth.setOrigin(sf::Vector2f(redHealth.getSize().x / 2, redHealth.getSize().y / 2));
    redHealth.setFillColor(sf::Color::Red);

    greenHealth.setSize(sf::Vector2f(50, 20));
    greenHealth.setOrigin(sf::Vector2f(greenHealth.getSize().x / 2, greenHealth.getSize().y / 2));
    greenHealth.setFillColor(sf::Color::Green);

    updateHealthbarLocation();

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

void Enemy::updateHealthbarLocation() {
    redHealth.setPosition(body.getPosition() + (sf::Vector2f(0, -70)));
    greenHealth.setPosition(body.getPosition() + (sf::Vector2f(0, -70)));
}




sf::FloatRect Enemy::getBounds() const
{
    return body.getGlobalBounds();

}


bool Enemy::isDead()
{
    return dead;
}

void Enemy::draw(sf::RenderWindow& window) const
{
    window.draw(attackRange);
    window.draw(body);
    window.draw(redHealth);
    window.draw(greenHealth);
    
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
  
    
}



bool Enemy::isPlayerInAttackRange(sf::Vector2f playerPos)
{
    if (attackRange.contains(playerPos)) {
        return true;
    }
    return false;
}

float Enemy::getAttackCooldown()
{
    return attackCooldown;
}

void Enemy::setAttackCooldown(float cooldown)
{
    attackCooldown = cooldown;
}

void Enemy::takeDamage(float damage)
{
    health -= damage;
    float healthPercent = static_cast<float>(health) / 100.f;
    greenHealth.setSize(sf::Vector2f(50.f * healthPercent, 20.f));
    if (health < 0) {
        health = 0;
        dead = true;
    }
    std::cout << "Damage taken... Health: " << getHealth() << "\n";
}

int Enemy::getHealth() const {
    return health;
}

bool Enemy::isPlayer() const
{
    return false;
}
bool Enemy::isEnemy() const
{
    return true;
}


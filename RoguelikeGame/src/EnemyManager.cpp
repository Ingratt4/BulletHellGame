#include "Headers\EnemyManager.h";
#include <iostream>



void EnemyManager::spawnEnemy(const sf::Vector2f& position)
{
    Enemy enemy;
    enemy.setPosition(position);
    enemies.push_back(enemy);
}

void EnemyManager::update(const sf::Vector2f& playerPos, BulletManager& enemyBulletManager, float dt) {
    for (auto& enemy : enemies) {
        enemy.moveTowardsPlayer(playerPos, dt);

        
        if (enemy.isPlayerInAttackRange(playerPos)) {
            if (enemy.getAttackCooldown() <= 0.f) {
                enemyBulletManager.spawnBullet(enemy.getPosition(), playerPos, BulletOwner::Enemy, 5);
                enemy.setAttackCooldown(1.0f); // Cooldown duration
            }
        }

        // Decrement cooldown
        float newCooldown = std::max(0.f, enemy.getAttackCooldown() - dt);
        enemy.setAttackCooldown(newCooldown);
    }
}

void EnemyManager::draw(sf::RenderWindow& window) const {
    for (auto& enemy : enemies) {
        enemy.draw(window);  // Call Enemy's draw method
    }
}

std::vector<Enemy>& EnemyManager::getEnemies()
{
    return enemies;
}



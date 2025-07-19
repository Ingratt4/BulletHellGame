#include "Headers\EnemyManager.h";
#include <iostream>



void EnemyManager::removeDeadEnemies() {
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if ((*it)->isDead()) {
            it = enemies.erase(it); // safely delete and continue
        }
        else {
            ++it;
        }
    }
}


void EnemyManager::spawnEnemy(const sf::Vector2f& position)
{
    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
    enemy->setPosition(position);
    enemies.push_back(std::move(enemy));
}

void EnemyManager::update(const sf::Vector2f& playerPos, BulletManager& enemyBulletManager, float dt) {
    for (auto& enemy : enemies) {

        
        enemy->moveTowardsPlayer(playerPos, dt);
        enemy->updateHealthbarLocation();

        
        if (enemy->isPlayerInAttackRange(playerPos)) {

            if (enemy->getAttackCooldown() <= 0.f) {
                enemyBulletManager.spawnBullet(enemy->getPosition(), playerPos, BulletOwner::Enemy, 25);
                enemy->setAttackCooldown(1.0f); // Cooldown duration
            }
        }

        // Decrement cooldown
        float newCooldown = std::max(0.f, enemy->getAttackCooldown() - dt);
        enemy->setAttackCooldown(newCooldown);
    }
    removeDeadEnemies();
}

void EnemyManager::draw(sf::RenderWindow& window) const {
    for (auto& enemy : enemies) {
        enemy->draw(window);  // Call Enemy's draw method
    }
}

std::vector<std::unique_ptr<Enemy>>& EnemyManager::getEnemies()
{
    return enemies;
}



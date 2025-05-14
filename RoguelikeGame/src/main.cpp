#include <SFML/Graphics.hpp>
#include "Headers/Player.h"
#include <iostream>
#include <fstream>
#include "Headers/TileMap.h";
#include "Headers/BulletManager.h";
#include "Headers/Enemy.h";
#include "Headers/EnemyManager.h";

bool checkBounds(Player& player);
bool checkNextBounds(Player& player, float dx, float dy);
void handleEvents(sf::RenderWindow& window, Player& player, BulletManager& bulletManager);
void handleMovement(Player& player, int speed, float dt);


int MAX_HEIGHT = 1080;
int MAX_WIDTH = 1920;
int main()
{

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Roguelike");
    window.setFramerateLimit(144);
    sf::Clock clock;
    Player player;
    std::vector<Damageable*> e_targets;

    EnemyManager enemyManager;
    BulletManager playerBulletManager;
    BulletManager enemyBulletManager;
    sf::RectangleShape background(sf::Vector2f(MAX_WIDTH, MAX_HEIGHT));
    background.setFillColor(sf::Color::White);
    sf::Vector2 movement(0, 0);
    int speed = 300;
    sf::View player_view;
    player_view.setSize(sf::Vector2(1000.f, 1000.f));
    player.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

    sf::Vector2u tileSize(128, 128);
    const unsigned int width = 10;
    const unsigned int height = 10;
    TileMap tileMap;
  

    int tiles[width * height] = {
        0, 1, 2, 0, 1, 2, 0, 1, 2, 0,
        1, 2, 0, 1, 2, 0, 1, 2, 0, 1,
        2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
        0, 1, 2, 0, 1, 2, 0, 1, 2, 0,
        1, 2, 0, 1, 2, 0, 1, 2, 0, 1,
        2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
        0, 1, 2, 0, 1, 2, 0, 1, 2, 0,
        1, 2, 0, 1, 2, 0, 1, 2, 0, 1,
        2, 0, 1, 2, 0, 1, 2, 0, 1, 2,
        0, 1, 2, 0, 1, 2, 0, 1, 2, 0
    };

    if (!tileMap.load(tileSize, tiles, width, height))
        return -1; // Exit if loading fails

    clock.start();
    enemyManager.spawnEnemy(sf::Vector2f(10, 10));
    
    enemyManager.spawnEnemy(sf::Vector2f(1000, -50));
    std::vector<Damageable*> p_targets = { &player };


    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        sf::Vector2f playerPos = player.getPosition();

        // --- Handle input & movement ---
        handleEvents(window, player, playerBulletManager);
        handleMovement(player, speed, dt);
        player_view.setCenter(playerPos);

        // --- Update game objects ---
        for (Enemy& e : enemyManager.getEnemies()) {
            e_targets.push_back(&e);
        }
        playerBulletManager.update(dt ,e_targets);
        enemyBulletManager.update(dt, p_targets);
        enemyManager.update(playerPos, enemyBulletManager, dt);

        // --- Render ---
        window.clear();
        window.setView(player_view);

        window.draw(background);
        enemyManager.draw(window);
        player.draw(window);
        playerBulletManager.draw(window);
        enemyBulletManager.draw(window);

        window.display();
    }

   
}



void handleEvents(sf::RenderWindow& window, Player& player, BulletManager& bulletManager) {
    while (const std::optional event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if (event->is<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f playerPos = player.getPosition();
            bulletManager.spawnBullet(playerPos, mousePos, BulletOwner::Player, 5 );
            std::cout << "Mouse location: " << "x: " << mousePos.x << " y: " << mousePos.y << "\n";
            std::cout << "Player position: " << "x: " << player.getPosition().x << " y: " << player.getPosition().y << "\n";
     
        }
    }
}

void handleMovement(Player& player, int speed, float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        if (checkNextBounds(player, -speed * dt, 0)) {
            player.move(-speed * dt, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        if (checkNextBounds(player, speed * dt, 0)) {
            player.move(speed * dt, 0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        if (checkNextBounds(player, 0, -speed * dt)) {
            player.move(0, -speed * dt);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        if (checkNextBounds(player, 0, speed * dt)) {
            player.move(0, speed * dt);
        }
    }
}


void loadTileMap(const std::string& filename, std::vector<std::string>& tilemap) {     
    //moves .txt file data to a vector.
    std::ifstream file(filename);
    if (!file.is_open( )) {
        throw std::runtime_error("Failed to open tilemap file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        tilemap.push_back(line);
    }

}

bool checkBounds(Player& player) {
    if (player.getPosition().x > 0 && player.getPosition().y > 0 && player.getPosition().x < 1920 && player.getPosition().y < 1080) {
        return true;
    }
    return false;
   
}

bool checkNextBounds(Player& player, float dx, float dy) {
    if (player.getPosition().x + dx < 1920 && player.getPosition().x + dx > 0 && player.getPosition().y + dy < 1080 && player.getPosition().y + dy > 0) {
        return true;
    }
    return false;
    
}




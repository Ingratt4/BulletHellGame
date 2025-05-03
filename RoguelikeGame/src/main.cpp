#include <SFML/Graphics.hpp>
#include "Headers/Player.h"
#include "Headers/Gun.h"
#include <iostream>
#include <fstream>
#include "Headers/TileMap.h";
#include "Headers/BulletManager.h";

void rangedAttack(Gun& gun, sf::Vector2f playerPos, sf::Vector2f targetPos, std::vector<std::pair<sf::CircleShape, sf::Vector2f>>& bullets);
bool checkBounds(Player& player);
bool checkNextBounds(Player& player, float dx, float dy);
void handleEvents(sf::RenderWindow& window, Player& player, BulletManager& bulletManager);
void handleMovement(Player& player, int speed, float dt);
void handlePlayerGun(std::vector<std::pair<sf::CircleShape, sf::Vector2f>>& bullets, float dt);

int MAX_HEIGHT = 1080;
int MAX_WIDTH = 1920;
int main()
{

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Roguelike");
    window.setFramerateLimit(144);
    sf::Clock clock;
    Player player;
    BulletManager bulletManager;
    Gun gun;
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
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		handleEvents(window, player, bulletManager);

		handleMovement(player, speed, dt);

		player_view.setCenter(sf::Vector2(player.getPosition()));
        bulletManager.update(dt);
        /*handlePlayerGun(bullets, dt);*/

		
		window.clear();
		window.setView(player_view);
		window.draw(background);
		/*window.draw(tileMap);*/
		player.draw(window);
        bulletManager.draw(window);



		


		window.display();
	}
   
}


void handlePlayerGun(std::vector<std::pair<sf::CircleShape, sf::Vector2f>>& bullets, float dt) {
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        // Move the bullet
        it->first.move(it->second * dt);

        // Remove bullets that go off-screen
        sf::Vector2f pos = it->first.getPosition();
        if (pos.x < 0 || pos.x > MAX_WIDTH || pos.y < 0 || pos.y > MAX_HEIGHT)
        {
            it = bullets.erase(it); // Remove bullet and get next iterator
        }
        else
        {
            ++it;
        }
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
            bulletManager.spawnBullet(playerPos, mousePos);
            std::cout << "Mouse location: " << "x: " << mousePos.x << " y: " << mousePos.y << "\n";
            std::cout << "Player position: " << "x: " << player.getPosition().x << " y: " << player.getPosition().y << "\n";
            /*rangedAttack(gun, playerPos, mousePos, bullets);*/
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



void rangedAttack(Gun& gun, sf::Vector2f playerPos, sf::Vector2f targetPos, std::vector<std::pair<sf::CircleShape, sf::Vector2f>>& bullets) {
    // Calculate the direction vector
    sf::Vector2f d_vec(targetPos.x - playerPos.x, targetPos.y - playerPos.y); 
    float magnitude = std::sqrt(d_vec.x * d_vec.x + d_vec.y * d_vec.y);

    // Normalize the direction vector
    if (magnitude != 0) {
        d_vec.x /= magnitude;
        d_vec.y /= magnitude;
    }

    // Create the bullet
    sf::CircleShape bullet = gun.bullet;
    bullet.setPosition(playerPos); // Set initial position to the player

    // Calculate the velocity
    sf::Vector2f velocity = d_vec * gun.getSpeed();
    std::cout << "Bullet velocity: " << velocity.x << velocity.y << "\n";

    // Add the bullet and its velocity to the bullets container
    bullets.emplace_back(bullet, velocity);

    std::cout << "New bullet added at position: " << playerPos.x << ", " << playerPos.y << "\n";
    std::cout << "Velocity: " << velocity.x << ", " << velocity.y << "\n";
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





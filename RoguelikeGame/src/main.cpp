#include <SFML/Graphics.hpp>
#include "Headers/Player.h"
#include "Headers/Gun.h"
#include <iostream>
#include <fstream>

void rangedAttack(Gun& gun, sf::Vector2f playerPos, sf::Vector2f targetPos, std::vector<std::pair<sf::CircleShape, sf::Vector2f>>& bullets);


int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Roguelike");
    window.setFramerateLimit(144);
    sf::Clock clock;
    Player player;
    Gun gun;
    std::vector<std::pair<sf::CircleShape, sf::Vector2f>> bullets; // Active bullets (shape + velocity)
    sf::Vector2 movement(0, 0);
    int speed = 300;
    sf::View player_view;
    player_view.setSize(sf::Vector2(1000.f, 1000.f));

    clock.start();
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();


        while (const std::optional event = window.pollEvent()){
     
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                sf::Vector2f playerPos = player.getPosition();
                std::cout <<"Mouse location: " << "x: " << mousePos.x << " y: " << mousePos.y << "\n";
                std::cout << "Player position: " << "x: " << player.getPosition().x << " y: " << player.getPosition().y << "\n";
                rangedAttack(gun, playerPos, mousePos, bullets);
            }
        }
       
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                player.move(-speed * dt, 0);
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                player.move(speed * dt, 0);
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                player.move(0, -speed * dt);
            }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                player.move(0, speed * dt);
            }
             player_view.setCenter(sf::Vector2(player.getPosition()));

             for (auto it = bullets.begin(); it != bullets.end();)
             {
                 // Move the bullet
                 it->first.move(it->second * dt);

                 // Remove bullets that go off-screen
                 sf::Vector2f pos = it->first.getPosition();
                 if (pos.x < 0 || pos.x > 1920 || pos.y < 0 || pos.y > 1080)
                 {
                     it = bullets.erase(it); // Remove bullet and get next iterator
                 }
                 else
                 {
                     ++it;
                 }
             }
        window.clear();
        window.setView(player_view);

        player.draw(window);

        for (const auto& bullet : bullets)
        {
            window.draw(bullet.first);
        }

        window.display();
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



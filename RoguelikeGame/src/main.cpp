#include <SFML/Graphics.hpp>
#include "Headers/Player.h"
#include <iostream>
#include <fstream>
#include "Headers/TileMap.h";
#include "Headers/BulletManager.h";
#include "Headers/Enemy.h";
#include "Headers/EnemyManager.h";
#include "Headers/Button.h";


// ====== PLAYER MECHANICS ======
 // TODO: Player dash logic + hotkey
 // TODO: Dash attack enemy
 // TODO: Player parry (block at first, reflect later)
 // TODO: Charged shot attack enemy
 // TODO: Burst shot enemy

// ====== ENEMY BEHAVIOR ======
 // TODO: Enemy healthbars [almost done]
 // TODO: Currency + Currency reward for enemy kill
 // TODO: AOE healer enemy

// ====== GAME STRUCTURE ======
 // TODO: Round system
 // TODO: Shop interface + shop system between rounds

int MAX_HEIGHT = 1080;
int MAX_WIDTH = 1920;



enum class GameState {
    Playing,
    GameOver
};
struct GameStateData {


    GameState state;
    sf::Clock clock;
    float dt;

    Player player;
    std::vector<Damageable*> p_targets;
    std::vector<Damageable*> e_targets;

    sf::View playerView;
    int speed;

    EnemyManager enemyManager;
    BulletManager playerBulletManager;
    BulletManager enemyBulletManager;

    sf::RectangleShape background;
    sf::RectangleShape overlay;
    Button restartButton;

    //TileMap tileMap;
};
GameStateData setupGame(sf::RenderWindow& window);
bool checkBounds(Player& player);
bool checkNextBounds(Player& player, float dx, float dy);
void handleEvents(sf::RenderWindow& window, Player& player, BulletManager& bulletManager, GameState& gameState);
void handleMovement(Player& player, int speed, float dt);
void restartGame(sf::RenderWindow& window);







int main()
{

    auto window = sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), "Roguelike");
    window.setFramerateLimit(144);

    GameStateData game = setupGame(window);
    game.p_targets = { &game.player };



 
    std::cout << std::filesystem::current_path() << std::endl;





    while (window.isOpen()) {
    float dt = game.clock.restart().asSeconds();
    handleEvents(window, game.player, game.playerBulletManager, game.state);

    window.clear();

    switch (game.state) {
        case GameState::Playing: {
            sf::Vector2f playerPos = game.player.getPosition();

            if (game.player.isDead()) {
                game.state = GameState::GameOver;
                break;
            }

            // --- Input & Movement ---
            handleMovement(game.player, game.speed, dt);
            game.playerView.setCenter(playerPos);


            // --- Game Updates ---
            auto q = game.enemyBulletManager.bulletTransferCheck();
            while (q.size() >= 1) {
                game.playerBulletManager.insertBullet(std::move(q.front()));
                q.pop();
            }
            game.enemyManager.update(playerPos, game.enemyBulletManager, dt);
			game.player.parry(dt);

            game.e_targets.clear();
            for (const auto& enemyPtr : game.enemyManager.getEnemies()) {
                if (!enemyPtr->isDead()) {
                    game.e_targets.push_back(enemyPtr.get());
                }
            }
         

            game.playerBulletManager.update(dt, game.e_targets);
            if (!game.p_targets.empty() && game.p_targets[0] == nullptr) {
                std::cout << "Null pointer in p_targets!\n";
            }

            game.enemyBulletManager.update(dt, game.p_targets);
            
          
            game.enemyManager.removeDeadEnemies();
            game.player.update(dt);

            // --- Rendering ---
            window.setView(game.playerView);
            window.draw(game.background);
            game.enemyManager.draw(window);
            game.player.draw(window);
            game.playerBulletManager.draw(window);
            game.enemyBulletManager.draw(window);
            break;
        }

        case GameState::GameOver: {
            // Handle events first
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (game.restartButton.isClicked(window, *event)) {
                    std::cout << "Button Clicked!" << "\n";
                    restartGame(window);
            
                    
                }
            }

            // Draw everything *after* polling events
            window.setView(window.getDefaultView());
            window.draw(game.overlay);
            //window.draw(game.gameOverText);
            game.restartButton.draw(window);
            break;
        }

        
    }

    window.display();
}




}

GameStateData setupGame(sf::RenderWindow& window) {
    // -------------------------------
    // === Game State & Window Setup ===
    // -------------------------------
    GameStateData game;


    // -------------------------------
    // === UI / Fonts / Overlay ===
    // -------------------------------
   
    sf::Font font("D:/Visual Studio Repos/RoguelikeGame/src/Assets/Fonts/Pixel-Regular.ttf");

    game.overlay = sf::RectangleShape(sf::Vector2f(window.getSize()));
    game.overlay.setFillColor(sf::Color(10, 10, 10));  // Dark background overlay for Game Over screen

    game.restartButton=Button(sf::Vector2f(400, 100), sf::Vector2f(window.getSize().x / 2, 200 + (window.getSize().y / 2)));

    // -------------------------------
    // === Timing ===
    // -------------------------------
    
    game.clock = sf::Clock();
    game.clock.start();

   

    // -------------------------------
    // === Player Setup ===
    // -------------------------------
    game.player.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
    //game.p_targets =  { &game.player };
    game.e_targets = {};
    
  

    // -------------------------------
    // === View / Camera Setup ===
    // -------------------------------
    game.playerView.setSize(sf::Vector2f(1000.f, 1000.f));
    sf::Vector2 movement(0, 0);
    game.speed = 300;

    // -------------------------------
    // === Enemy & Bullet Managers ===
    // -------------------------------


    game.enemyManager.spawnEnemy(sf::Vector2f(10, 10));
    game.enemyManager.spawnEnemy(sf::Vector2f(1000, -50));

    

    // -------------------------------
    // === Background ===
    // -------------------------------
    game.background= sf::RectangleShape(sf::Vector2f(MAX_WIDTH, MAX_HEIGHT));
    game.background.setFillColor(sf::Color::White);

    // -------------------------------
    // === Tilemap Setup ===
    // -------------------------------
    sf::Vector2u tileSize(128, 128);
    const unsigned int width = 10;
    const unsigned int height = 10;

 /*   int tiles[width * height] = {
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

    TileMap tileMap;*/

    game.state = GameState::Playing;


    return game;
    
}

void restartGame(sf::RenderWindow& window) {

    setupGame(window);
}

void handleEvents(sf::RenderWindow& window, Player& player, BulletManager& bulletManager, GameState& state) {
    while (const std::optional event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if (state != GameState::Playing) return;

        if (event->is<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::Vector2f playerPos = player.getPosition();
            bulletManager.spawnBullet(playerPos, mousePos, BulletOwner::Player, 5 ); //number is damage (temporary)
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        player.tryStartParry();
    }
    };
    


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




#include "Enemy.h";

Enemy::Enemy() {
	attackBox(100.f);
	body(sf::Vector2f(30.f, 30.f));
	body.setFillColor(sf::Color::Magenta);
	
}
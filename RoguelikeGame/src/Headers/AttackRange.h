#include "SFML/Graphics.hpp";
class AttackRange : public sf::CircleShape {
public:
	using sf::CircleShape::CircleShape;

	bool contains(const sf::Vector2f& point) const {
		sf::Vector2f center = getPosition();
		float dx = point.x - center.x;
		float dy = point.y - center.y;
		return(dx * dx + dy * dy) <= (getRadius() * getRadius());
	}
};
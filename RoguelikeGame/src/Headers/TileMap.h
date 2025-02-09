#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <filesystem>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    bool load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif // TILEMAP_H

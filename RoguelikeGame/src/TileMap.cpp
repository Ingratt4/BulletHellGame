#include "Headers\TileMap.h"
// This code was taken directly from the SFML 3.0 documentation

    bool TileMap::load(sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // load the tileset texture
        //if (!m_tileset.loadFromFile(tileset))
        //    return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
        m_vertices.resize(width * height * 6);

        // populate the vertex array, with two triangles per tile
        for (unsigned int i = 0; i < width; ++i)
        {
            for (unsigned int j = 0; j < height; ++j)
            {
                // get the current tile number
                const int tileNumber = tiles[i + j * width];

                // find its position in the tileset texture
                //const int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                //const int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // get a pointer to the triangles' vertices of the current tile
                sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];

                sf::Color tileColor;
                switch (tileNumber)
                {
                case 0: tileColor = sf::Color::Magenta; break;
                case 1: tileColor = sf::Color::Black; break;
                case 2: tileColor = sf::Color::Black; break;
                default: tileColor = sf::Color::Black; break;
                }

                // define the 6 corners of the two triangles
                triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
                triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

                //assign colour
                for (int k = 0; k < 6; ++k)
                    triangles[k].color = tileColor;

                // define the 6 matching texture coordinates
                //triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                //triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                //triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                //triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
                //triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                //triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            }
        }

        return true;
    }

    void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        // apply the transform
        states.transform *= getTransform();


        states.texture = nullptr;

        // apply the tileset texture
        /*states.texture = &m_tileset;*/

        // draw the vertex array
        target.draw(m_vertices, states);
    }


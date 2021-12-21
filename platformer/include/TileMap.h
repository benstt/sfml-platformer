//
// Created by benja on 20/12/2021.
//

#ifndef PLATFORMER_TILEMAP_H
#define PLATFORMER_TILEMAP_H


#include <SFML/Graphics.hpp>
#include <memory>
#include "Entity.h"

enum TileType {
    Decorator = 0,
    BigPlaformSimple,
    BigPlatformFactory,
    BigPlatformRounded,
    BigPlatformGrasslike,
    BigPlatformBricks,
    BigPlatformTinyBricks,
};

const int TILE_SIZE = 16;

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap() = default;
    TileMap(unsigned int amountX, unsigned int amountY, const int* tiles);
    TileMap(const std::string& texturePath, unsigned int amountX, unsigned int amountY, const sf::Image& source);
    TileMap(unsigned int amountX, unsigned int amountY, std::shared_ptr<sf::Texture> texture); // maybe shared_ptr
    ~TileMap() = default;

    void putTile(unsigned int i, unsigned int j, TileType tile, const sf::Image& source);
    void removeTile(float x, float y);

    int getPixelColor(unsigned int i, unsigned int j, const sf::Image& source);
    float getAutotileOffsetX(unsigned int i, unsigned int j, const sf::Image& source);
    float getAutotileOffsetY(unsigned int i, unsigned int j, const sf::Image& source);
private:
    unsigned int m_TilesX, m_TilesY;
    sf::VertexArray m_Vertices;
    std::vector<Collider> m_Colliders;
    std::shared_ptr<sf::Texture> m_Texture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif //PLATFORMER_TILEMAP_H

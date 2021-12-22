//
// Created by benja on 20/12/2021.
//

#ifndef PLATFORMER_TILEMAP_H
#define PLATFORMER_TILEMAP_H


#include <SFML/Graphics.hpp>
#include "Entity.h"

enum TileType {
    Decorator = 0,
    BigPlaformSimple,
    BigPlatformFactory,
    BigPlatformRounded,
    BigPlatformGrasslike,
    BigPlatformBricks,
    BigPlatformTinyBricks,
    FlowerSmall,
    FlowerBig,
    WeedSmall,
    WeedBig,
    Grass,
    GrassWindy,
};

const int TILE_SIZE = 16;

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap() = default;
    TileMap(uint32_t amountX, uint32_t amountY, const int* tiles);
    TileMap(const std::string& texturePath, uint32_t amountX, uint32_t amountY, const sf::Image& source);
    ~TileMap() override = default;

    void putTile(uint32_t i, uint32_t j, TileType tile, const sf::Image& source);
private:
    uint32_t m_TilesX, m_TilesY;
    sf::VertexArray m_Vertices;
    std::vector<Collider> m_Colliders;
    std::shared_ptr<sf::Texture> m_Texture;

    static uint32_t getPixelColor(uint32_t i, uint32_t j, const sf::Image& source) ;
    bool sameColorX(uint32_t i, uint32_t j, uint32_t offset, const sf::Image& source);
    bool sameColorY(uint32_t i, uint32_t j, uint32_t offset, const sf::Image& source);
    float getAutotileOffsetX(uint32_t i, uint32_t j, const sf::Image& source);
    float getAutotileOffsetY(uint32_t i, uint32_t j, const sf::Image& source);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif //PLATFORMER_TILEMAP_H

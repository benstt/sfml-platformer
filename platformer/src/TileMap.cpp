//
// Created by benja on 20/12/2021.
//

#include "TileMap.h"
#include "Entity.h"
#include <iostream>

TileMap::TileMap(uint32_t amountX, uint32_t amountY, const int* tiles) : m_TilesX(amountX), m_TilesY(amountY) {
    /*
     * - try to load texture from path
     * - set VertexArray
     * - loop through all tiles of the image and put a tile according to the tiles array
     */

    this->m_Texture = std::make_unique<sf::Texture>();
    m_Texture->loadFromFile("../res/tileset.png");

    // the sprite consists of 4 vertices, thus a quad
    this->m_Vertices.setPrimitiveType(sf::Quads);
    this->m_Vertices.resize(amountX * amountY * 4);

    for (uint32_t i = 0; i < amountX; ++i) {
        for (uint32_t j = 0; j < amountY; ++j) {
            // https://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php#example-tile-map
            // get current tile number
            int tileNumber = tiles[i + j * amountX];

            // find its position in the tileset texture
            int tu = tileNumber % (m_Texture->getSize().x / 16);
            int tv = tileNumber / (m_Texture->getSize().x / 16);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &this->m_Vertices[(i + j * amountX) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
            quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
            quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * TILE_SIZE, tv * TILE_SIZE);
            quad[1].texCoords = sf::Vector2f((tu + 1) * 16, tv * TILE_SIZE);
            quad[2].texCoords = sf::Vector2f((tu + 1) * 16, (tv + 1) * TILE_SIZE);
            quad[3].texCoords = sf::Vector2f(tu * TILE_SIZE, (tv + 1) * TILE_SIZE);
        }
    }
}

TileMap::TileMap(const std::string& texturePath, uint32_t amountX, uint32_t amountY, const sf::Image& source)
    : m_TilesX(amountX), m_TilesY(amountY) {
    /*
     * - try to load texture from path
     * - set VertexArray
     * - loop through all tiles of the image, get its color and put a tile accordingly
     */

    this->m_Texture = std::make_unique<sf::Texture>();
    if (!this->m_Texture->loadFromFile(texturePath)) {
        std::cout << "ERROR::TILEMAP::TILEMAP::Failed to load texture!" << std::endl;
        return;
    }

    // the sprite consists of 4 vertices, thus a quad
    this->m_Vertices.setPrimitiveType(sf::Quads);
    this->m_Vertices.resize(amountX * amountY * 4);

    // check every pixel color on the image
    for (uint32_t i = 0; i < amountX; ++i) {
        for (uint32_t j = 0; j < amountY; ++j) {
            uint32_t r = source.getPixel(i, j).r;
            uint32_t g = source.getPixel(i, j).g;
            uint32_t b = source.getPixel(i, j).b;

            // put tiles depending on the color
            switch (r, g, b) {
                // blueish - platforms
                case (34, 32, 52):
                    this->putTile(i, j, TileType::BigPlaformSimple, source);
                    break;
                case (31, 60, 65):
                    this->putTile(i, j, TileType::BigPlatformFactory, source);
                    break;
                case (153, 229, 80):
                    this->putTile(i, j, TileType::FlowerSmall, source);
                    break;
                case (55, 148, 110):
                    this->putTile(i, j, TileType::FlowerBig, source);
                    break;
                case (75, 105, 47):
                    this->putTile(i, j, TileType::WeedSmall, source);
                    break;
                case (81, 93, 61):
                    this->putTile(i, j, TileType::WeedBig, source);
                    break;
            }
        }
    }
}

void TileMap::putTile(uint32_t i, uint32_t j, TileType tile, const sf::Image& source) {
    /*
     * @return void
     * - update quad position's and texture
     * - autotile if tile neighbors exist
     * - put a collider on a tile if it is collidable
     *
     * Puts a tile at the given i and j index.
     */

    int vertsAmount = 4;

    // https://www.sfml-dev.org/tutorials/2.1/graphics-vertex-array.php#example-tile-map
    // get a pointer to the current tile's quad
    sf::Vertex* quad = &this->m_Vertices[(i + j * this->m_TilesX) * vertsAmount];

    // get texture that should be drawn based on neighbors
    float tu = this->getAutotileOffsetX(i, j, source);
    float tv = this->getAutotileOffsetY(i, j, source);

    // set texture coordinates
    switch (tile) {
        case TileType::Decorator:
            break;
        case TileType::FlowerSmall:
            tu = 256;
            tv = 0;
            break;
        case TileType::FlowerBig:
            tu = 272;
            tv = 0;
            break;
        case TileType::WeedSmall:
            tu = 256;
            tv = 16;
            break;
        case TileType::WeedBig:
            tu = 272;
            tv = 16;
            break;
        case TileType::BigPlaformSimple:
            tu += 176;
            tv += 96;
            break;
        case TileType::BigPlatformFactory:
            tu += 176;
            tv += 160;
            break;
        case TileType::BigPlatformRounded:
            tu += 176;
            tv += 224;
            break;
        case TileType::BigPlatformGrasslike:
            tu += 256;
            tv += 96;
            break;
        case TileType::BigPlatformBricks:
            tu += 256;
            tv += 160;
            break;
        case TileType::BigPlatformTinyBricks:
            tu += 256;
            tv += 224;
            break;
    }

    // decide what to do with each tile
    switch (tile) {
        case TileType::Decorator:
            break;
        case TileType::BigPlaformSimple:
        case TileType::BigPlatformFactory:
        case TileType::BigPlatformRounded:
        case TileType::BigPlatformGrasslike:
        case TileType::BigPlatformBricks:
        case TileType::BigPlatformTinyBricks:
            // instance entity to check colliders and stuff
            auto* newTile = new Entity(i * TILE_SIZE, j * TILE_SIZE);
            this->m_Colliders.push_back(newTile->getCollider());
            break;
    }

    // define its 4 corners
    quad[0].position = sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE);
    quad[1].position = sf::Vector2f((i + 1) * TILE_SIZE, j * TILE_SIZE);
    quad[2].position = sf::Vector2f((i + 1) * TILE_SIZE, (j + 1) * TILE_SIZE);
    quad[3].position = sf::Vector2f(i * TILE_SIZE, (j + 1) * TILE_SIZE);

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(tu, tv);
    quad[1].texCoords = sf::Vector2f((tu + TILE_SIZE), tv);
    quad[2].texCoords = sf::Vector2f((tu + TILE_SIZE), (tv + TILE_SIZE));
    quad[3].texCoords = sf::Vector2f(tu, (tv + TILE_SIZE));
}

uint32_t TileMap::getPixelColor(uint32_t i, uint32_t j, const sf::Image &source) {
    /*
     * @return the color mapped to a pixel
     * Returns the pixel color of the image at the given pixel.
     */

    return source.getPixel(i, j).toInteger();
}

bool TileMap::sameColorX(uint32_t i, uint32_t j, uint32_t offset, const sf::Image &source) {
    /*
     * @return if the pixel at i, j has the same color as offset, j
     * Returns if the pixel has the same color as the given offset.
     */

    // check for adjacent tile
    if (this->getPixelColor(i, j, source) == this->getPixelColor(offset, j, source)) {
        return true;
    }

    return false;
}

bool TileMap::sameColorY(uint32_t i, uint32_t j, uint32_t offset, const sf::Image &source) {
    /*
     * @return if the pixel at i, j has the same color as i, offset
     * Returns if the pixel has the same color as the given offset.
     */

    // check for adjacent tile
    if (this->getPixelColor(i, j, source) == this->getPixelColor(i, offset, source)) {
        return true;
    }

    return false;
}

float TileMap::getAutotileOffsetX(uint32_t i, uint32_t j, const sf::Image& source) {
    /*
     * @return the X offset of the tile that should be placed
     * relative to the middle tile of the block
     * - check for both left and right for possibles tiles
     * - return the offset
     *
     * Gets the X offset of the tile on the source image.
     * A return of 0 means that it will be placed the same texture (the middle one of the 3x3 block).
     */

    // check if the adjacent cell has the same color
    // left
    if (i > 0 && this->sameColorX(i, j, i-1, source)) {
        // right
        if (i < this->m_TilesX && this->sameColorX(i, j, i+1, source)) {
            // middle, get same texture
            return 0;
        }

        return TILE_SIZE;
    } else if (i < this->m_TilesX && this->sameColorX(i, j, i+1, source)) {
        // get right
        return -TILE_SIZE;
    }

    // if the tile does not belong to the square,
    // it must be either vertical or the single block,
    // so adding TILE_SIZE * 2 (32 in this case) to it will work on both cases
    return TILE_SIZE * 2;
}

float TileMap::getAutotileOffsetY(uint32_t i, uint32_t j, const sf::Image& source) {
    /*
     * @return the Y offset of the tile that should be placed
     * relative to the middle tile of the block
     * - check for both bottom and top for possibles tiles
     * - return the offset
     *
     * Gets the Y offset of the tile on the source image.
     * A return of 0 means that it will be placed the same texture (the middle one of the 3x3 block).
     */

    // check if the adjacent cell has the same color
    // top
    if (j > 0 && sameColorY(i, j, j-1, source)) {
        // bottom
        if (j < this->m_TilesY && sameColorY(i, j, j+1, source)) {
            // middle, get same texture
            return 0;
        }

        return TILE_SIZE;
    } else if (j < this->m_TilesY && sameColorY(i, j, j+1, source)) {
        // get top
        return -TILE_SIZE;
    }

    // if the tile does not belong to the square,
    // it must be either horizontal or the single block,
    // so adding TILE_SIZE * 2 (32 in this case) to it will work on both cases
    return TILE_SIZE * 2;
}

void TileMap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    /*
     * @return void
     * Draws the tilemap to the target.
     */

    // apply transform
    states.transform *= this->getTransform();

    // apply texture
    states.texture = &(*this->m_Texture);

    // only for debug
    bool debug = false;
    if (debug) {
        for (auto& c : this->m_Colliders) {
            c.render(target);
        }
    }

    // draw the vertex array
    target.draw(this->m_Vertices, states);
}

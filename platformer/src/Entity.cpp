//
// Created by benja on 20/12/2021.
//

#include <iostream>
#include <utility>
#include "Entity.h"
#include "EntityTracker.h"

Entity::Entity(float x, float y) : x(x), y(y) {
    /*
     * - create collider
     * - set position
     * - add entity to tracker
     */

    this->m_Collider = Collider(x, y);
    this->setPosition(x, y);

    EntityTracker::addEntity(*this);
    this->ID = EntityTracker::entityAmount();
}

Entity::Entity(float x, float y, const std::string& texturePath) : x(x), y(y) {
    /*
     * - create texture
     * - create sprite
     * - set sprite origin
     * - create collider
     * - set position
     * - add entity to tracker
     */

    this->m_Texture = std::make_shared<sf::Texture>();
    if (!this->m_Texture->loadFromFile(texturePath)) {
        std::cout << "ERROR::ENTITY::ENTITY::Failed to load texture!" << std::endl;
    }
    this->m_Sprite = sf::Sprite(*m_Texture);

    // set the origin of the sprite to the middle (16 * 0.5)
    // to be able to flip the sprite, etc
    this->m_Sprite.setOrigin(8.f, 8.f);
    this->m_Collider = Collider(x, y);
    this->setPosition(x, y);

    EntityTracker::addEntity(*this);
    this->ID = EntityTracker::entityAmount();
}

Entity::Entity(float x, float y, sf::Sprite sprite) : x(x), y(y), m_Sprite(std::move(sprite)) {
    /*
     * - set sprite origin
     * - create collider
     * - set position
     * - add entity to tracker
     */

    // set the origin of the sprite to the middle (16 * 0.5)
    // to be able to flip the sprite, etc
    this->m_Sprite.setOrigin(8.f, 8.f);
    this->m_Collider = Collider(x, y);
    this->setPosition(x, y);

    EntityTracker::addEntity(*this);
    this->ID = EntityTracker::entityAmount();
}

float Entity::X() const {
    /*
     * @return X coordinate
     * Returns the X coordinate.
     */

    return this->x;
}

float Entity::Y() const {
    /*
     * @return Y coordinate
     * Returns the Y coordinate.
     */

    return this->y;
}

void Entity::setPosition(float _x, float _y) {
    /*
     * @return void
     * - update x and y
     * - update positions of collider and sprite
     *
     * Sets the position of the entity.
     */

    this->x = _x;
    this->y = _y;
    this->m_Collider.setPosition(_x, _y);
    sf::Vector2f spriteOrigin = this->m_Sprite.getOrigin();
    this->m_Sprite.setPosition(_x + spriteOrigin.x, _y + spriteOrigin.y);
}

sf::Vector2f Entity::getPosition() const {
    /*
     * @return the position of the entity
     * Returns the position of the entity.
     */

    return { this->x, this->y };
}

const Collider& Entity::getCollider() const {
    /*
     * @return a reference to the collider
     * Returns the entity's collider.
     */

    return this->m_Collider;
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    /*
     * @return void
     * - draw collider
     * - draw sprite
     *
     * Draws the entity to the target.
     */

    bool debug = false;
    if (debug) this->m_Collider.render(target);
    target.draw(this->m_Sprite);
}

void Entity::update(float delta) {
}

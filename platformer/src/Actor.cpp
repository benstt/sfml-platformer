//
// Created by benja on 18/12/2021.
//

#include "Actor.h"
#include "EntityTracker.h"

Actor::Actor(float x, float y) : Entity(x, y), m_MovementSpeed(1), m_Alive(true) {
}

Actor::Actor(float x, float y, const std::string& texturePath) : Entity(x, y, texturePath), m_MovementSpeed(1), m_Alive(true) {
}

Actor::Actor(float x, float y, const sf::Sprite& sprite) : Entity(x, y, sprite), m_MovementSpeed(1), m_Alive(true) {
}

void Actor::move(float _x, float _y) {
    /*
     * @return void
     * - sum parameter values to x and y
     * - move the sprite
     *
     * Moves the actor's sprite.
     */

    // check if it will collide any entity
    for (auto e : EntityTracker::entities()) {
        if (this->ID != e.get().ID && this->collides(e.get())) {
            // move the actor a bit so it could move again
            this->correctPosition(e.get());
        }
    }

    // update the actor
    float nextX = this->X() + _x * m_MovementSpeed;
    float nextY = this->Y() + _y * m_MovementSpeed;

    this->m_Collider.setPosition(nextX, nextY);
    this->setPosition(nextX, nextY);
}

bool Actor::collides(const Entity& entity) const {
    /*
     * @return if the actor is colliding with the entity
     * Checks if the actor collides with the entity.
     */

    return this->m_Collider.isColliding(entity.getCollider());
}

void Actor::correctPosition(const Entity& entity) {
    /*
     * @return void
     * - check if positioned on the edge of the entity's collider
     *
     * Corrects the position of the actor based on the entity's collider.
     */

    float nextX = this->X();
    float nextY = this->Y();
    const Collider& col = entity.getCollider();

    // check for bounds                                   // set new coords
    if (this->X() + this->getCollider().W() == col.X())   nextX = this->X() - 1;
    if (this->Y() + this->getCollider().H() == col.Y())   nextY = this->Y() - 1;
    if (this->X() == col.X() + col.W())                   nextX = this->X() + 1;
    if (this->Y() == col.Y() + col.H())                   nextY = this->Y() + 1;

    // update position
    this->setPosition(nextX, nextY);
}

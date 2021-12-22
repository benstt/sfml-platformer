//
// Created by benja on 18/12/2021.
//

#include "Actor.h"
#include "EntityTracker.h"
#include "KeyboardManager.h"
#include <iostream>

Actor::Actor(float x, float y) :
    Entity(x, y),
    m_Velocity(sf::Vector2f(0.f, 0.f)),
    m_MovementSpeed(1),
    m_Alive(true) {
}

Actor::Actor(float x, float y, const std::string& texturePath) :
    Entity(x, y, texturePath),
    m_Velocity(sf::Vector2f(0.f, 0.f)),
    m_MovementSpeed(1),
    m_Alive(true) {

    // 0.1f is the time between frames of the animation
    this->m_AnimationPlayer = AnimationPlayer(&this->m_Sprite, 0.1f);
}

Actor::Actor(float x, float y, const sf::Sprite& sprite) :
    Entity(x, y, sprite),
    m_Velocity(sf::Vector2f(0.f, 0.f)),
    m_MovementSpeed(1),
    m_Alive(true) {

    // 0.1f is the time between frames of the animation
    this->m_AnimationPlayer = AnimationPlayer(&this->m_Sprite, 0.1f);
}

void Actor::move(float _x, float _y) {
    /*
     * @return void
     * - sum parameter values to x and y
     * - move the sprite
     *
     * Moves the actor's sprite.
     */

    // keep track of movement direction
    this->m_Velocity = sf::Vector2f(_x * m_MovementSpeed, _y * m_MovementSpeed);

    sf::Vector2f desiredMovePosition = sf::Vector2f(this->X() + _x * this->m_MovementSpeed,
                                                    this->Y() + _y * this->m_MovementSpeed);

    // check if it collides any entity
    for (auto& e : EntityTracker::entities()) {
        if (this->ID != e.get().ID && this->collidesAtPosition(desiredMovePosition, e)) {
            // will collide, don't move
            return;
        }
    }

    // update the actor
    float nextX = this->X() + _x * this->m_MovementSpeed;
    float nextY = this->Y() + _y * this->m_MovementSpeed;

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

bool Actor::collidesAtPosition(sf::Vector2f position, const Entity& entity) const {
    /*
     * @return if the actor collides at position
     * Returns if the actor will collide at the given position.
     */

    const Collider& col = entity.getCollider();

    return this->getCollider().isColliderInsideAt(position, col);
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

void Actor::update(float delta) {
    // play animations
    this->m_AnimationPlayer.update(delta);

    // TODO: put all of this into a player class
    // flip sprite
    if (this->m_Velocity.x < 0 && !this->m_Flipped) {
        this->m_Sprite.setScale(-1.f, 1.f);
        this->m_Flipped = true;
    }

    if (this->m_Velocity.x > 0 && this->m_Flipped) {
        this->m_Sprite.setScale(1.f, 1.f);
        this->m_Flipped = false;
    }

    // "gravity"
    this->move(0.f, 1.f);

    // check for keyboard presses
    if (KeyboardManager::isBeingPressed(sf::Keyboard::A)) {
        this->m_AnimationPlayer.play(); // start animation
        this->move(-1.f, 0.f);
    }

    if (KeyboardManager::isBeingPressed(sf::Keyboard::D)) {
        this->m_AnimationPlayer.play(); // start animation
        this->move(1.f, 0.f);
    }

    if (KeyboardManager::released(sf::Keyboard::A) || KeyboardManager::released(sf::Keyboard::D))
        this->m_AnimationPlayer.stop(); // stop animation
}

//
// Created by benja on 19/12/2021.
//

#include "Collider.h"

Collider::Collider(float x, float y) : x(x), y(y), w(16), h(16) {
    /*
     * - set position
     * - set size
     * - set fill color
     * - set outline
     */

    this->m_Rect.setPosition(x, y);
    this->m_Rect.setSize(sf::Vector2f(w, h));
    this->m_Rect.setFillColor(sf::Color::Transparent);
    this->m_Rect.setOutlineColor(sf::Color::Green);
    this->m_Rect.setOutlineThickness(1.5f);
}

Collider::Collider(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {
    /*
     * - set position
     * - set size
     * - set fill color
     * - set outline
     */

    this->m_Rect.setPosition(x, y);
    this->m_Rect.setSize(sf::Vector2f(w, h));
    this->m_Rect.setFillColor(sf::Color::Transparent);
    this->m_Rect.setOutlineColor(sf::Color::Green);
    this->m_Rect.setOutlineThickness(3.f);
}

bool Collider::isColliding(const Collider& col) const{
    /*
     * @return if the collider is colliding with other
     * - check bounds for collision
     *
     * Checks if the collider is colliding with other (AABB).
     */

    if (this->x + this->w < col.X()
        || this->x > col.X() + col.W()
        || this->y + this->h < col.Y()
        || this->y > col.Y() + col.H())
    {
        return false;
    }

    return true;
}

bool Collider::isCollidingX(float x) const {
    /*
     * @return if the collider is colliding on the X
     * - check x0 and x1 for collision
     *
     * Checks if there are any collision on any x or x + w.
     */

    return (x < this->x) ? this->x - x == 1 : x - this->x + this->w == 1;
}

bool Collider::isCollidingY(float y) const {
    /*
     * @return if the collider is colliding on the Y
     * - check y0 and y1 for collision
     *
     * Checks if there are any collision on any y or y + h.
     */

    return (y < this->y) ? this->y - y == 1 : y - this->y + this->h == 1;
}

float Collider::X() const {
    /*
     * @return X coordinate
     * Returns the X coordinate.
     */

    return this->x;
}

float Collider::Y() const {
    /*
     * @return Y coordinate
     * Returns the Y coordinate.
     */

    return this->y;
}

float Collider::W() const {
    /*
     * @return W coordinate
     * Returns the W coordinate.
     */

    return this->w;
}

float Collider::H() const {
    /*
     * @return H coordinate
     * Returns the H coordinate.
     */

    return this->h;
}

void Collider::setPosition(float x, float y) {
    /*
     * @return void
     * - set x, y
     * - set position of rectangle shape
     *
     * Sets the position of the collider.
     */

    this->x = x;
    this->y = y;
    this->m_Rect.setPosition(x, y);
}

sf::Vector2f Collider::getPosition() const {
    /*
     * @return the position of the collider
     * Gets the position of the collider.
     */

    return {this->x, this->y};
}

void Collider::setScale(float x, float y) {
    /*
     * @return void
     * Sets the scale of the collider.
     */

    this->m_Rect.setScale(x, y);
}

void Collider::render(sf::RenderTarget& target) const {
    /*
     * @return void
     * Renders the collider to the target.
     */

    target.draw(this->m_Rect);
}
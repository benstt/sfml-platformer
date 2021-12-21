//
// Created by benja on 19/12/2021.
//

#ifndef PLATFORMER_COLLIDER_H
#define PLATFORMER_COLLIDER_H

#include <SFML/Graphics.hpp>

class Collider {
public:
    Collider() = default;
    Collider(float x, float y);
    Collider(float x, float y, float w, float h);
    ~Collider() = default;

    bool isColliding(const Collider& col) const;
    bool isCollidingX(float x) const;
    bool isCollidingY(float y) const;
    bool isPointInside(sf::Vector2f point) const;

    float X() const;
    float Y() const;
    float W() const;
    float H() const;

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void setScale(float x, float y);

    void render(sf::RenderTarget& target) const;
private:
    float x, y, w, h;
    sf::RectangleShape m_Rect;
};

#endif //PLATFORMER_COLLIDER_H

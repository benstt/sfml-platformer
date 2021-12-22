//
// Created by benja on 20/12/2021.
//

#ifndef PLATFORMER_ENTITY_H
#define PLATFORMER_ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Collider.h"

class Entity : public sf::Drawable {
public:
    Entity() = default;
    Entity(float x, float y);
    Entity(float x, float y, const std::string& texturePath);
    Entity(float x, float y, sf::Sprite  sprite);
    ~Entity() = default;

    uint64_t ID;

    float X() const;
    float Y() const;
    void setPosition(float _x, float _y);
    sf::Vector2f getPosition() const;
    const Collider& getCollider() const;

    virtual void update(float delta);
protected:
    float x, y;
    std::shared_ptr<sf::Texture> m_Texture;
    sf::Sprite m_Sprite;
    Collider m_Collider;
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //PLATFORMER_ENTITY_H

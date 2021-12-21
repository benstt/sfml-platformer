//
// Created by benja on 18/12/2021.
//

#ifndef PLATFORMER_ACTOR_H
#define PLATFORMER_ACTOR_H


#include <SFML/Graphics.hpp>
#include "Entity.h"


class Actor : public Entity {
public:
    Actor() = default;
    Actor(float x, float y);
    Actor(float x, float y, const std::string& texturePath);
    Actor(float x, float y, const sf::Sprite& sprite);
    ~Actor() override = default;

    void move(float x, float y);
    bool collides(const Entity& entity) const;
    void correctPosition(const Entity& entity);
private:
    float m_MovementSpeed;
    bool m_Alive;
};


#endif //PLATFORMER_ACTOR_H

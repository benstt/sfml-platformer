//
// Created by benja on 18/12/2021.
//

#ifndef PLATFORMER_ACTOR_H
#define PLATFORMER_ACTOR_H


#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AnimationPlayer.h"

class Actor : public Entity {
public:
    Actor() = default;
    Actor(float x, float y);
    Actor(float x, float y, const std::string& texturePath);
    Actor(float x, float y, const sf::Sprite& sprite);
    ~Actor() override = default;

    void move(float x, float y);

    void update(float delta) override;
private:
    float m_MovementSpeed;
    sf::Vector2f m_Velocity;
    bool m_Alive;
    bool m_Flipped;
    AnimationPlayer m_AnimationPlayer;

    bool collides(const Entity& entity) const;
    bool collidesAtPosition(sf::Vector2f position, const Entity& entity) const;
    void correctPosition(const Entity& entity);
};


#endif //PLATFORMER_ACTOR_H

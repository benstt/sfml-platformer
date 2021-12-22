//
// Created by benja on 21/12/2021.
//

#ifndef PLATFORMER_ANIMATIONPLAYER_H
#define PLATFORMER_ANIMATIONPLAYER_H

#include <SFML/Graphics.hpp>

class AnimationPlayer {
public:
    AnimationPlayer() = default;
    AnimationPlayer(sf::Sprite* sprite, float switchTime);
    ~AnimationPlayer() = default;

    void update(float delta);
    void play();
    void stop();
private:
    bool m_IsPlaying;
    uint32_t m_Frame;
    uint32_t m_ImageCount;
    float m_SwitchTime;
    float m_TotalTime;
    sf::IntRect m_Rect;
    sf::Sprite* m_Sprite;
};

#endif //PLATFORMER_ANIMATIONPLAYER_H

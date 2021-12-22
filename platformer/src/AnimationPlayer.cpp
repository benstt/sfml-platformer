//
// Created by benja on 21/12/2021.
//

#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(sf::Sprite* sprite, float switchTime) :
    m_IsPlaying(false),
    m_Frame(0),
    m_SwitchTime(switchTime),
    m_TotalTime(0.f),
    m_Sprite(sprite) {

    // 16 is the width of the tiles in the game
    this->m_ImageCount = this->m_Sprite->getTexture()->getSize().x / 16;
    this->m_Rect.width  = 16.f;
    this->m_Rect.height = 16.f;
}

void AnimationPlayer::update(float delta) {
    /*
     * @return void
     * - check if it is playing
     * - sum delta to total time
     * - change frames
     * - set frame back to 0 if end of animation
     * - change sprite
     *
     * Changes frames every m_SwitchTime seconds.
     */

    if (this->m_IsPlaying) {
        // https://youtu.be/Aa8bXSq5LDE
        this->m_TotalTime += delta;

        // set max waiting time for next frame
        if (this->m_TotalTime >= this->m_SwitchTime) {
            this->m_TotalTime -= this->m_SwitchTime;
            this->m_Frame++;

            // reset frame
            if (this->m_Frame >= this->m_ImageCount) {
                this->m_Frame = 0;
            }
        }
    }

    // change rect and update sprite
    this->m_Rect.left = this->m_Frame * this->m_Rect.width;
    this->m_Sprite->setTextureRect(m_Rect);
}

void AnimationPlayer::play() {
    /*
     * @return void
     * Sets the animator to play.
     */

    this->m_IsPlaying = true;
}

void AnimationPlayer::stop() {
    /*
     * @return void
     * Stops the animation and changes the frame back to the start.
     */

    this->m_IsPlaying = false;
    this->m_Frame = 0;
}


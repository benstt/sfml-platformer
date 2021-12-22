//
// Created by benja on 18/12/2021.
//

#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "KeyboardManager.h"
#include "TileMap.h"

class Game {
public:
    Game();
    ~Game() = default;

    bool isRunning() const;

    void update(float delta);
    void render();
private:
    std::unique_ptr<sf::RenderWindow> m_Window;
    std::unique_ptr<Actor> m_Player;
    std::unique_ptr<Actor> m_Enemy;
    TileMap m_TileMap;

    void pollEvents();
    void createWindow(float w, float h, std::string name);
};

#endif //PLATFORMER_GAME_H

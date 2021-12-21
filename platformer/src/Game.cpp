//
// Created by benja on 18/12/2021.
//

#include <iostream>
#include "Game.h"
#include "Collider.h"

const float WINDOW_WIDTH = 384.f;
const float WINDOW_HEIGHT = 224.f;

Game::Game() {
    /*
     * - create a window
     * - create the player
     * - create tilemap
     * - set fps max
     */

    this->createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Platformer");
    this->m_Player = std::make_unique<Actor>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "../res/sprite.png");
    this->m_Enemy = std::make_unique<Actor>(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, "../res/sprite.png");

    sf::Image map;
    map.loadFromFile("../res/test.png");
    this->m_TileMap = TileMap("../res/tileset.png", WINDOW_WIDTH / 16, WINDOW_HEIGHT / 16, map);
    this->m_Window->setFramerateLimit(60);
}

bool Game::isRunning() const {
    /*
     * @return if the game is running
     *
     * Checks if the game is running.
     */

    return this->m_Window->isOpen();
}

void Game::update() {
    /*
     * @return void
     * - poll events
     * - update the player
     * - update the enemy
     * - check for keyboard inputs
     *
     * Updates the game.
     */

    this->pollEvents();
    // this->m_Player->update();
    // this->m_Enemy->update();

    // check for keyboard presses
    if (KeyboardManager::isBeingPressed(sf::Keyboard::A)) {
        this->m_Player->move(-1.f, 0.f);
    }

    if (KeyboardManager::isBeingPressed(sf::Keyboard::D)) {
        this->m_Player->move(1.f, 0.f);
    }

    if (KeyboardManager::isBeingPressed(sf::Keyboard::W)) {
        this->m_Player->move(0.f, -1.f);
    }

    if (KeyboardManager::isBeingPressed(sf::Keyboard::S)) {
        this->m_Player->move(0.f, 1.f);
    }
}

void Game::render() {
    /*
     * @return void
     * - clear the screen
     * - render the player
     * - render the enemy
     * - render the tilemap
     * - display to the window
     *
     * Render the game to the window.
     */

    this->m_Window->clear();
    this->m_Window->draw(m_TileMap);
    this->m_Window->draw(*this->m_Player);
    this->m_Window->draw(*this->m_Enemy);
    this->m_Window->display();
}

void Game::pollEvents() {
    /*
     * @return void
     * - poll events
     * - close on clicking X button
     * - close on pressing the escape key
     *
     * Polls events in the game.
     */

    sf::Event e {};
    while (this->m_Window->pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                this->m_Window->close();
                break;
            case sf::Event::KeyPressed:
                if (e.key.code == sf::Keyboard::Escape) {
                this->m_Window->close();
                break;
            }
        }
    }
}

void Game::createWindow(float w, float h, std::string name) {
    /*
     * @return void
     * - create a window with the given values
     *
     * Creates a window.
     */

    this->m_Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(w, h), name);
}
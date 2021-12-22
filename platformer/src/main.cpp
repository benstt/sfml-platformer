#include "Game.h"

int main() {
    Game game;

    // get delta to stay consistent between frames
    float delta = 0.f;
    sf::Clock clock;

    while (game.isRunning()) {
        delta = clock.restart().asSeconds();

        game.update(delta);
        game.render();
    }
}

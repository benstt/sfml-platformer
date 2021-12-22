//
// Created by benja on 18/12/2021.
//

#ifndef PLATFORMER_KEYBOARDMANAGER_H
#define PLATFORMER_KEYBOARDMANAGER_H

#include <SFML/Window/Keyboard.hpp>
#include <set>

class KeyboardManager {
public:
    static bool isBeingPressed(sf::Keyboard::Key key);
    static bool justPressed(sf::Keyboard::Key key);
    static bool released(sf::Keyboard::Key key);
private:
    static std::set<sf::Keyboard::Key> s_KeysPressed;
};

#endif //PLATFORMER_KEYBOARDMANAGER_H

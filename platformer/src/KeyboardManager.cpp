//
// Created by benja on 18/12/2021.
//

#include "KeyboardManager.h"

std::set<sf::Keyboard::Key> KeyboardManager::s_KeysPressed {};

bool KeyboardManager::isBeingPressed(sf::Keyboard::Key key) {
    /*
     * @return if the given key is being pressed
     * - check if the user presses the key
     * - add the key to the collection
     *
     * Checks if the user is holding the given key.
     */

    // delete the key from the collection if exists
    if (KeyboardManager::s_KeysPressed.contains(key))
        KeyboardManager::s_KeysPressed.erase(key);

    if (sf::Keyboard::isKeyPressed(key)) {
        KeyboardManager::s_KeysPressed.insert(key);
        return true;
    }

    return false;
}

bool KeyboardManager::justPressed(sf::Keyboard::Key key) {
    /*
     * @return if a key was just pressed
     * - check if the user presses the key once
     * - add the key to the collection
     *
     * Checks if the user has just pressed the given key.
     */

    // key released from last frame, erase it
    if (!sf::Keyboard::isKeyPressed(key))
        KeyboardManager::s_KeysPressed.erase(key);

    if (sf::Keyboard::isKeyPressed(key) && !KeyboardManager::s_KeysPressed.contains(key)) {
        s_KeysPressed.insert(key);
        return true;
    }

    return false;
}

bool KeyboardManager::released(sf::Keyboard::Key key) {
    /*
     * @return if a given key was released
     * - check if the user presses the given key
     * - check if the key exists in the collection
     * - erase the key in the collection
     *
     * Checks if the user has released the given key.
     */

    if (!sf::Keyboard::isKeyPressed(key) && KeyboardManager::s_KeysPressed.contains(key)) {
        KeyboardManager::s_KeysPressed.erase(key);
        return true;
    }

    return false;
}
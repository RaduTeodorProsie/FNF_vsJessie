#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <vector>

class pause_menu {
    std::vector<sf::String> options;

public:
    pause_menu() {
        options = {}
    }
};

#endif // PAUSE_MENU_H

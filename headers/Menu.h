#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

class Menu {
    std::vector<sf::String> options;
    const int px_sz;

public:
    explicit Menu(const std::vector<sf::String> &options, const int px_sz = 128) : options(options), px_sz(px_sz) {}
    explicit Menu() : px_sz(128) { options = {"Exit game"}; }

    sf::String getOption() const;
};

#endif // MENU_H

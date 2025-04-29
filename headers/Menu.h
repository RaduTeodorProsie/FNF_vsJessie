#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

class Menu {
    std::vector<sf::String> options;
    const int px_sz;

public:
    explicit Menu(const std::vector<sf::String> &options, const int px_sz = 128) : options(options), px_sz(px_sz) {}
    explicit Menu() : options({"Exit Game"}), px_sz(128){}

    std::optional<sf::String> getOption() const;
};

#endif // MENU_H

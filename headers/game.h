#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "track.h"

class game {
    std::vector<std::unique_ptr<track>> tracks;

public:
    game();
    void start();
    static sf::RenderWindow &getWindow();
};

#endif // GAME_H

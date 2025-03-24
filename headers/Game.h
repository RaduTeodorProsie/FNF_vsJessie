#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Track.h"

class Game {
    std::vector<std::unique_ptr<Track>> tracks;

public:
    Game();
    void start();
    static sf::RenderWindow &getWindow();
};

#endif // GAME_H

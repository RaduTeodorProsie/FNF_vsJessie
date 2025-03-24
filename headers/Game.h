#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Track.h"
// #include "InputHandler.h"

class Game {
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Track>> tracks;

public:
    Game();
    void start();
};

#endif // GAME_H

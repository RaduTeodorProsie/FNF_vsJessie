#ifndef GAME_H
#define GAME_H

#include <map>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "track.h"
#include "spriteData.h"


class game {
    std::vector<std::unique_ptr<track>> tracks;

public:
    game();
    void start();
    static sf::RenderWindow &getWindow();
    static std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> &getSpriteData();
};

#endif // GAME_H

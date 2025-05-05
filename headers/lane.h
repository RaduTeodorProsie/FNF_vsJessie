#ifndef LANE_H
#define LANE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include <map>

#include <memory>
#include "../headers/heartNote.h"
#include "../headers/poisonNote.h"
#include "../headers/simpleNote.h"
#include "../headers/spriteData.h"

#include "game.h"

class lane {
    std::deque<std::shared_ptr<note>> currentNotes;
    std::string name;
    simpleNote judge;

public:
    lane(const std::string& name, int X);
    static inline std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> &getSpriteData();

    void draw() const;
};

#endif // LANE_H

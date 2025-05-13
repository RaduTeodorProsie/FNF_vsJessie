#ifndef LANE_H
#define LANE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include <map>

#include <memory>
#include "../headers/heartNote.h"
#include "../headers/poisonNote.h"
#include "../headers/simpleNote.h"
#include "../headers/spriteData.h"

#include "game.h"

class lane {
    std::deque<std::shared_ptr<note>> currentNotes, unreachableNotes;
    std::string name;
    simpleNote judge;

    const double pxPerMsec = 1.5;
    const std::vector<int> cat = {14, 30, 60, 120};

public:
    lane(const std::string &name, int X);
    static inline std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> &getSpriteData();

    void draw() const;
    double whenNext() const;
    void update(const sf::Time &dt);
    void press();
    void release();
    template<class T>
    void addNote() {
        T note(judge.getTexture());
        note.setTextureRect(getSpriteData()[0].second[name + "0000"].get_texture_rect());
        note.setPosition({judge.getPosition().x, -100});
        currentNotes.emplace_back(std::make_shared<T>(note));
    }
};

#endif // LANE_H

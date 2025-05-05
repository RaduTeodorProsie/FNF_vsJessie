#include <utility>

#include "../headers/lane.h"



std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> &lane::getSpriteData() {
    static std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> notes;
    return notes;
}

lane::lane(const std::string& name, const int X) : name(name),judge(getSpriteData()[0].first) {
    judge.setTextureRect(getSpriteData()[0].second["arrow_" + name + "0000"].get_texture_rect());
    judge.setPosition({static_cast<float>(X), 850});
}
void lane::draw() const {
    sf::RenderWindow &window = game::getWindow();
    for (const auto &note: currentNotes) window.draw(*note);
    window.draw(judge);
}



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

double lane::whenNext() const {
    return (judge.getPosition().y - currentNotes.front()->getPosition().y) / pxPerMsec;
}

void lane::update(const sf::Time &dt) {
    for (const auto &note : currentNotes) {
        note->move({0, static_cast<float>(dt.asMilliseconds() * pxPerMsec)});
    }

    while (!currentNotes.empty() && currentNotes.front()->getPosition().y > 1920) {
        std::cout << "popped" << std::endl;
        currentNotes.pop_front();
    }
}

void lane::press() {
    judge.setTextureRect(getSpriteData()[0].second[name + " confirm0001"].get_texture_rect());
    if (!currentNotes.empty()) {
        if (abs(whenNext()) <= cat.back()) {
            std::shared_ptr<poisonNote> ptr = std::dynamic_pointer_cast<poisonNote>(currentNotes.front());
            if (ptr) {
                static sf::SoundBuffer acid;
                if (!acid.loadFromFile("assets/shared/notes/acid.ogg"))
                    throw AssetException("Could not load acid");
                static sf::Sound acidSound(acid); acidSound.play();
                std::cout << "Acid!" << std::endl;
            }

            currentNotes.pop_front();
        }
    }
}

void lane::release() {
    judge.setTextureRect(getSpriteData()[0].second["arrow_" + name + "0000"].get_texture_rect());
}




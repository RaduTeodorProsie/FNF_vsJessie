#include <utility>

#include "../headers/lane.h"


inline std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> &lane::getSpriteData() {
    static std::vector<std::pair<sf::Texture, std::map<std::string, spriteData>>> xmlInfo;
    return xmlInfo;
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

    while (!currentNotes.empty() && currentNotes.front()->getPosition().y > 1080) {
        currentNotes.pop_front();
    }
}

void lane::press() {
    const spriteData &data = getSpriteData()[0].second[name + " press0001"];
    judge.setTextureRect(data.get_texture_rect());
    //judge.move({static_cast<float>(data.get_frame_x()), 2 * static_cast<float>(data.get_frame_y())});
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

            if (currentNotes.front()->midAnimation())
                currentNotes.pop_front();
            else {
                currentNotes.front()->hit();
            }
        }
    }
}

void lane::release() {
    const spriteData &data = getSpriteData()[0].second[name + " press0001"];
    //judge.move({2 * -static_cast<float>(data.get_frame_x()), 2 * -static_cast<float>(data.get_frame_y())});
    judge.setTextureRect(getSpriteData()[0].second["arrow_" + name + "0000"].get_texture_rect());
}




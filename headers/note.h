#ifndef NOTE_H
#define NOTE_H

#include <SFML/Graphics.hpp>

class note : public sf::Sprite {
public:
    ~note() override = default;
    explicit note(const sf::Texture& texture) : Sprite(texture) {}
    virtual void hit() const = 0;
};

#endif //NOTE_H

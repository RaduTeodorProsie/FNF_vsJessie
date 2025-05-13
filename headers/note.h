#ifndef NOTE_H
#define NOTE_H

#include <SFML/Graphics.hpp>

class note : public sf::Sprite {
    bool inAnimation = false;
public:
    ~note() override = default;
    explicit note(const sf::Texture& texture) : Sprite(texture) {}
    virtual void hit() const = 0;
    bool midAnimation() const {return inAnimation;}
};

#endif //NOTE_H

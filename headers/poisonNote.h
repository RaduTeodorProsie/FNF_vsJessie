#ifndef POISONNOTE_H
#define POISONNOTE_H

#include "note.h"
#include "SFML/Audio/Sound.hpp"

class poisonNote : public note{
    static sf::Sound hitSound;
public:
    explicit poisonNote(const sf::Texture &texture) : note{texture} {}
    void hit() const override{
        hitSound.play();
    }

    static sf::Sound &getHitSound() {
        return hitSound;
    }

};



#endif //POISONNOTE_H

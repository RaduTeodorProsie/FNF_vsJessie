#ifndef HEARTNOTE_H
#define HEARTNOTE_H
#include "note.h"
#include "SFML/Audio/Sound.hpp"

class heartNote : public note{
    static sf::Sound hitSound;
public:
    explicit heartNote(const sf::Texture &texture) : note(texture){}
    void hit() const override{
        hitSound.play();
    }

    static sf::Sound &getHitSound() {
        return hitSound;
    }

};



#endif //HEARTNOTE_H

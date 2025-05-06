#ifndef POISONNOTE_H
#define POISONNOTE_H

#include "note.h"
#include "SFML/Audio/Sound.hpp"
#include "exceptions.h"

class poisonNote : public note{
public:
    explicit poisonNote(const sf::Texture &texture) : note{texture} {}

    void hit() const override{

    }

};



#endif //POISONNOTE_H

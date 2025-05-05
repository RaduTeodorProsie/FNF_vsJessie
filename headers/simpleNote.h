//
// Created by Radu Prosie on 5/5/2025.
//

#ifndef SIMPLENOTE_H
#define SIMPLENOTE_H

#include "note.h"

class simpleNote : public note {
public:
    explicit simpleNote (const sf::Texture& texture) : note(texture) {}
    void hit() const override {}
};

#endif //SIMPLENOTE_H

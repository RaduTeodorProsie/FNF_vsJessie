#ifndef ENTITY_H
#define ENTITY_H

#include "animatable.h"
class Entity : public Animatable{
    std::unordered_map<std::string, std::vector<sf::IntRect>> animations;
public:

};

#endif //ENTITY_H

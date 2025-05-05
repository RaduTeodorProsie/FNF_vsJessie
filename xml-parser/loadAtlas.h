#ifndef LOADATLAS_H
#define LOADATLAS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "../headers/SpriteData.h"
#include "pugixml.hpp"

std::pair<std::map<std::string, SpriteData>, std::string> parseTextureAtlasPugi(const std::string &xmlPath);

#endif //LOADATLAS_H

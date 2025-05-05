#ifndef LOADATLAS_H
#define LOADATLAS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "../headers/spriteData.h"
#include "pugixml.hpp"

std::map<std::string, spriteData> parseTextureAtlasPugi(const std::string &xmlPath);

#endif //LOADATLAS_H

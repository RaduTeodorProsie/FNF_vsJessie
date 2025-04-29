#include <utility>

#include "../headers/exceptions.h"

GameException::GameException(std::string msg) : msg(std::move(msg)) {}
const char *GameException::what() const noexcept { return msg.c_str(); }

AssetException::AssetException(std::string msg) : GameException(std::move(msg)) {}


#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

class GameException : std::exception {
    std::string msg;

public:
    explicit GameException(std::string msg);
    const char *what() const noexcept override;
};

class AssetException : public GameException {
public:
    explicit AssetException(std::string msg);
};

#endif // EXCEPTIONS_H

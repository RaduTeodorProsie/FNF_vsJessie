#ifndef SPRITEDATA_H
#define SPRITEDATA_H

#include <SFML/Graphics.hpp>

class spriteData {
    sf::IntRect textureRect;
    int frameX{}, frameY{}, frameWidth{}, frameHeight{};

public:
    spriteData() = default;
    spriteData(const int x, const int y, const int width, const int height, const int frameX, const int frameY,
               const int frameWidth, const int frameHeight)
        : textureRect(sf::IntRect({x, y}, {width, height})), frameX(frameX), frameY(frameY), frameWidth(frameWidth),
          frameHeight(frameHeight) {}
    [[nodiscard]] int get_frame_x() const { return frameX; }
    [[nodiscard]] int get_frame_y() const { return frameY; }
    [[nodiscard]] int get_frame_width() const { return frameWidth; }
    [[nodiscard]] int get_frame_height() const { return frameHeight; }
    [[nodiscard]]sf::IntRect get_texture_rect() const {return textureRect;}
    void set_texture_rect(const sf::IntRect &texture_rect) { textureRect = texture_rect; }
};

#endif // SPRITEDATA_H

#include "../headers/Track.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
Track::Track(const std::string &_title, const bool empty) : title(_title) {
    if (!empty) {
        bool open1 = instrumental.openFromFile("../assets/music/" + _title + "/Inst.ogg");
        bool open2 = voices.openFromFile("../assets/music/" + _title + "/Voices.ogg");

        if (!open1 || !open2) {
            throw std::runtime_error("Failed to load audio files for track: " + _title);
        }
    }
}

sf::String Track::get_title() const { return title; }

void Track::start(sf::RenderWindow &window) {
    window.clear();
    instrumental.play();
    voices.play();
}

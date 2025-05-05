#ifndef TRACK_H
#define TRACK_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class track {
    sf::String title;
    sf::Music instrumental, voices;

    void pause();
    void restart();
    void game_loop();

public:
    explicit track(const std::string &title);

    void start();
    static void play_intro();

    [[nodiscard]] sf::String get_title() const;

    /// SFML music is not copyable so we ought to make this class not copyable as well
    track(const track &) = delete;
    track &operator=(const track &) = delete;
};

#endif // TRACK_H

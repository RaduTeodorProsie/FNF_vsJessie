#include "../headers/Track.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../headers/Game.h"
#include "../headers/Menu.h"

void Track::restart() {
    instrumental.stop();
    voices.stop();
    instrumental.setPlayingOffset(sf::Time::Zero);
    voices.setPlayingOffset(sf::Time::Zero);
    instrumental.play();
    voices.play();
}

Track::Track(const std::string &title, const bool empty) : title(title) {
    if (!empty) {
        bool open1 = instrumental.openFromFile("../assets/music/" + title + "/Inst.mp3");
        bool open2 = voices.openFromFile("../assets/music/" + title + "/Voices.mp3");
/*
        if (!open1 || !open2) {
            throw std::runtime_error("Failed to load audio files for track: " + title);
        }
    }*/
}

sf::String Track::get_title() const { return title; }

void Track::start() {
    sf::RenderWindow &window = Game::getWindow();
    instrumental.play();
    voices.play();
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) voices.setVolume(0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) voices.setVolume(100);

            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                    voices.pause();
                    instrumental.pause();

                    Menu pause_menu({"Resume", "Restart", "Main Menu", "Exit Game"});

                    if (const sf::String want = pause_menu.getOption(); want == "Resume") {
                        voices.play();
                        instrumental.play();
                    }

                    else if (want == "Restart")
                        restart();

                    else if (want == "Exit Game")
                        window.close();

                    else if (want == "Main Menu") {
                        voices.stop();
                        instrumental.stop();

                        return;
                    }
                }
            }
        }

        if (!window.isOpen()) continue;

        window.clear();
        window.display();
    }
}

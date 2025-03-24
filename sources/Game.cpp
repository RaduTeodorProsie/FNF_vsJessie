#include "../headers/Game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/Track.h"

Game::Game() {
    window.create(sf::VideoMode({1920u, 1080u}), "FNF", sf::Style::None, sf::State::Fullscreen);
    window.setFramerateLimit(540);

    tracks.push_back(std::make_unique<Track>("VsMaria"));
    tracks.push_back(std::make_unique<Track>("VsBeatrice"));
    tracks.push_back(std::make_unique<Track>("VsJessie"));
    tracks.push_back(std::make_unique<Track>("Exit Game", true));
}

void Game::start() {
    sf::Font playful("../assets/fonts/playful.ttf");
    std::vector<sf::Text> track_names;
    const int px_sz = 128;
    for (const auto &track: tracks) {
        track_names.emplace_back(playful, track->get_title());
        track_names.back().setCharacterSize(px_sz);
        track_names.back().setFillColor(sf::Color::White);
        track_names.back().setPosition({0, static_cast<float>(px_sz * (track_names.size() - 1))});
    }

    int current_track = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) tracks[current_track]->start(window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                current_track = (current_track - 1 + track_names.size()) % track_names.size();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                current_track = (current_track + 1) % track_names.size();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) &&
                 track_names[current_track].getString() == "Exit Game"))
                window.close();

            window.clear();
            for (auto &track_name: track_names) {
                track_name.setFillColor(sf::Color::White);
            }
            track_names[current_track].setFillColor(sf::Color::Red);
            for (auto &track_name: track_names) window.draw(track_name);
            window.display();
        }
    }
}

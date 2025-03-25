#include "../headers/Game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../headers/Menu.h"
#include "../headers/Track.h"

sf::RenderWindow &Game::getWindow() {
    static sf::RenderWindow window;
    return window;
}

Game::Game() {
    sf::RenderWindow &window = Game::getWindow();
    window.create(sf::VideoMode({1920u, 1080u}), "FNF", sf::Style::None, sf::State::Fullscreen);
    window.setFramerateLimit(540);

    tracks.push_back(std::make_unique<Track>("Vs Maria"));
    tracks.push_back(std::make_unique<Track>("Vs Beatrice"));
    tracks.push_back(std::make_unique<Track>("Vs Jessie"));
}

void Game::start() {
    std::vector<sf::String> track_names; track_names.reserve(tracks.size() + 1);
    for (const auto &track: tracks) {
        track_names.emplace_back(track->get_title());
    }

    track_names.emplace_back("Exit Game");
    while (getWindow().isOpen()) {
        Menu main_menu(track_names);
        const sf::String want = main_menu.getOption();

        if (want == "Exit Game") {
            getWindow().close();
            return;
        }

        auto trackp = std::find_if(tracks.begin(), tracks.end(),
                                   [&want](const std::unique_ptr<Track> &track) { return track->get_title() == want; });
        (*trackp)->start();
    }
}

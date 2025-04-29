#include "../headers/Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../headers/Menu.h"
#include "../headers/Track.h"
#include "../headers/exceptions.h"
#include "../headers/exit_codes.h"

sf::RenderWindow &Game::getWindow() {
    static sf::RenderWindow window;
    return window;
}

Game::Game() {
    sf::RenderWindow &window = Game::getWindow();
    window.create(sf::VideoMode({1920u, 1080u}), "FNF", sf::Style::None, sf::State::Fullscreen);
    window.setFramerateLimit(540);
    try {
        tracks.push_back(std::make_unique<Track>("Vs Maria"));
        tracks.push_back(std::make_unique<Track>("Vs Beatrice"));
        tracks.push_back(std::make_unique<Track>("Vs Jessie"));
    }
    catch (const AssetException &e) {
        std::cerr << e.what();
        std::exit(static_cast<int>(ExitCode::ASSET_ERROR));
    }

    catch (const GameException &e) {
        std::cerr << e.what();
        std::exit(static_cast<int>(ExitCode::UNKNOWN_ERROR));
    }
}

void Game::start() {
    std::vector<sf::String> track_names;
    track_names.reserve(tracks.size() + 1);
    for (const auto &track: tracks) {
        track_names.emplace_back(track->get_title());
    }

    track_names.emplace_back("Exit Game");
    while (getWindow().isOpen()) {
        Menu main_menu(track_names);
        const std::optional<sf::String> want = main_menu.getOption();

        if (!want.has_value()) return;
        if (*want == "Exit Game") {
            getWindow().close();
            return;
        }

        auto trackp = std::ranges::find_if(
                tracks, [&want](const std::unique_ptr<Track> &track) { return *want == track->get_title(); });
        (*trackp)->start();
    }
}

#include "../headers/game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../headers/Menu.h"
#include "../headers/exceptions.h"
#include "../headers/exit_codes.h"
#include "../headers/lane.h"
#include "../headers/track.h"
#include "../xml-parser/loadAtlas.h"

sf::RenderWindow &game::getWindow() {
    static sf::RenderWindow window;
    return window;
}

game::game() {
    sf::RenderWindow &window = game::getWindow();
    window.create(sf::VideoMode({1920u, 1080u}), "FNF", sf::Style::None, sf::State::Fullscreen);
    window.setFramerateLimit(540);
    try {
        tracks.push_back(std::make_unique<track>("Vs Maria"));
        tracks.push_back(std::make_unique<track>("Vs Beatrice"));
        tracks.push_back(std::make_unique<track>("Vs Jessie"));
    }
    catch (const AssetException &e) {
        std::cerr << e.what();
        std::exit(static_cast<int>(ExitCode::ASSET_ERROR));
    }

    catch (const GameException &e) {
        std::cerr << e.what();
        std::exit(static_cast<int>(ExitCode::UNKNOWN_ERROR));
    }

    catch (...) {
        std::cerr << "Unknown error!";
        std::exit(static_cast<int>(ExitCode::UNKNOWN_ERROR));
    }
}

void game::start() {
    try {
        auto &notes = lane::getSpriteData();
        for (const std::string &name: {"notes", "poison_notes", "heart_note"})
            notes.emplace_back(sf::Texture("assets/shared/notes/" + name + ".png"),
                               parseTextureAtlasPugi("assets/shared/notes/" + name + ".xml"));

        if (sf::SoundBuffer loveNote; !loveNote.loadFromFile("assets/shared/notes/loveNote.ogg"))
            throw AssetException("Failed to load love note");
        if (sf::SoundBuffer poisonNote; !poisonNote.loadFromFile("assets/shared/notes/acid.ogg"))
            throw AssetException("Failed to load poison note");
    }
    catch (const AssetException &e) {
        std::cerr << e.what();
        std::exit(static_cast<int>(ExitCode::ASSET_ERROR));
    }
    catch (...) {
        std::cerr << "Unknown error!";
        std::exit(static_cast<int>(ExitCode::UNKNOWN_ERROR));
    }

    std::cout << lane::getSpriteData().size() << std::endl;
    std::vector<sf::String> track_names;
    track_names.reserve(tracks.size() + 1);
    for (const auto &track: tracks) {
        track_names.emplace_back(track->get_title());
    }

    track_names.emplace_back("Exit game");
    while (getWindow().isOpen()) {
        menu main_menu(track_names);
        const std::optional<sf::String> want = main_menu.getOption();

        if (!want.has_value()) return;
        if (*want == "Exit game") {
            getWindow().close();
            return;
        }

        auto trackp = std::ranges::find_if(
                tracks, [&want](const std::unique_ptr<track> &track) { return *want == track->get_title(); });
        (*trackp)->start();
    }
}

#include "../headers/Track.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../headers/Game.h"
#include "../headers/Menu.h"
#include "../headers/exceptions.h"
#include "../xml-parser/loadAtlas.h"

Track::Track(const std::string &title) : title(title) {
    const bool open1 = instrumental.openFromFile("assets/music/" + title + "/Inst.ogg");

    if (const bool open2 = voices.openFromFile("assets/music/" + title + "/Voices.ogg"); !open1 || !open2) {
        if (!open1) throw AssetException("Failed to load audio files for track instrumentals: " + title);
        throw AssetException("Failed to load audio files for track voices: " + title);
    }
}

sf::String Track::get_title() const { return title; }

void Track::play_intro() {

    std::vector<sf::SoundBuffer> buffers;
    buffers.resize(3);
    for (int i = 3; i >= 1; --i) {
        std::string filename = "assets/shared/intro/intro" + std::to_string(i) + ".ogg";
        if (!buffers[buffers.size() - i].loadFromFile(filename)) {
            throw AssetException("Failed to load audio file for track intro: " + filename);
        }
    }

    buffers.emplace_back();
    std::string goFilename = "assets/shared/intro/introGo.ogg";
    if (!buffers.back().loadFromFile(goFilename)) {
        throw AssetException("Failed to load GO for the track intro: " + goFilename);
    }

    std::vector<sf::Sound> sounds;
    sounds.reserve(buffers.size());
    for (const auto &buffer : buffers) {
        sounds.emplace_back(buffer);
    }

    std::vector<sf::Texture> textures;
    std::vector<std::string> names = {"ready.png", "set.png", "go.png"};
    try {
        for (const auto &name : names) {
            textures.emplace_back();
            if (!textures.back().loadFromFile("assets/shared/intro/" + name)) {
                throw AssetException("Failed to load texture: " + name);
            }
        }
    } catch (const AssetException &e) {
        std::cerr << e.what() << std::endl;
        throw ;
    }

    std::vector<sf::Sprite> sprites;
    for (const auto &texture : textures) {
        sprites.emplace_back(texture);
    }

    sf::RenderWindow &window = Game::getWindow();
    const sf::Vector2u windowSize = window.getSize();
    float windowCenterX = static_cast<float>(windowSize.x) / 2.0f;
    float windowCenterY = static_cast<float>(windowSize.y) / 2.0f;

    for (auto &sprite : sprites) {
        const auto poz = sf::Vector2f(sprite.getTextureRect().size);
        const float originX = poz.x / 2.0f;
        const float originY = poz.y / 2.0f;
        sprite.setOrigin(sf::Vector2f(originX, originY));
        sprite.setPosition(sf::Vector2f(windowCenterX, windowCenterY));
    }

    sf::Clock timer;
    constexpr sf::Time delay = sf::milliseconds(300);
    size_t currentPlayIndex = 0;

    sounds[0].play();
    timer.restart();

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return;
            }
        }

        if (!window.isOpen()) break;

        if (timer.getElapsedTime() >= delay) {
            currentPlayIndex++;

            if (currentPlayIndex < sounds.size()) {
                sounds[currentPlayIndex].play();
                timer.restart();
            } else {
                break;
            }
        }

        window.clear();
        if (currentPlayIndex >= 1) {
            window.draw(sprites[currentPlayIndex - 1]);
        }
        window.display();
    }
}

void Track::restart() {
    play_intro();
    instrumental.stop();
    voices.stop();
    instrumental.setPlayingOffset(sf::Time::Zero);
    voices.setPlayingOffset(sf::Time::Zero);
    instrumental.play();
    voices.play();
}

void Track::start() {
    sf::RenderWindow &window = Game::getWindow();

    /*auto [test, path] = parseTextureAtlasPugi("assets/shared/notes/notes.xml");
    path = "assets/shared/notes/" + path;
    sf::Texture notes(path);
    sf::Sprite down(notes, test["down confirm0001"].get_texture_rect());*/

    restart();
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
                    const std::optional<sf::String> want = pause_menu.getOption();
                    if (!want.has_value()) return;
                    if (want == "Resume") {
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

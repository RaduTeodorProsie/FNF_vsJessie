#include "../headers/Menu.h"
#include <SFML/Graphics.hpp>
#include "../headers/Game.h"
sf::String Menu::getOption() const {
    std::vector<sf::Text> opt;
    const sf::Font playful("assets/fonts/playful.ttf");
    for (const auto &option: options) {
        opt.emplace_back(playful, option);
        opt.back().setCharacterSize(px_sz);
        opt.back().setFillColor(sf::Color::White);
        opt.back().setPosition({0, static_cast<float>(px_sz * (opt.size() - 1))});
    }

    sf::RenderWindow &window = Game::getWindow();
    std::vector<sf::Text>::size_type current_option = 0;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto *keyEvent = event->getIf<sf::Event::KeyPressed>())
                if (keyEvent->scancode == sf::Keyboard::Scan::Enter) return options[current_option];

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
                current_option = (current_option - 1 + options.size()) % options.size();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) current_option = (current_option + 1) % opt.size();

            window.clear();

            for (auto &option: opt) {
                option.setFillColor(sf::Color::White);
            }

            opt[current_option].setFillColor(sf::Color::Red);
            for (auto &track_name: opt) window.draw(track_name);

            window.display();
        }
    }
    return {};
}

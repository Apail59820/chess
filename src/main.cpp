#include <SFML/Graphics.hpp>

#include "../include/GameContext.h"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "Chess");
    window.setFramerateLimit(144);

    GameContext game(&window);

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game.Update();

        window.clear(sf::Color(120, 89, 66));

        game.Render();

        window.display();
    }
}

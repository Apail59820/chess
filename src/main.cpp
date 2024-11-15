#include <SFML/Graphics.hpp>

#include "../include/Context.h"
#include "../include/GameContext.h"

int main() {
    auto window = sf::RenderWindow({1920u, 1080u}, "Chess");
    window.setFramerateLimit(144);

    auto game = std::make_unique<GameContext>(&window);
    Context::GlobalContext = &game;

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            game->HandleMouseEvents(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game->Update();

        window.clear(sf::Color(120, 89, 66));

        game->Render();

        window.display();
    }
}

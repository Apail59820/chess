//
// Created by Amaury Paillard on 08/11/2024.
//

#include "../include/GameContext.h"

GameContext::GameContext(sf::RenderWindow *window) {
    m_window = window;

    const sf::Vector2u windowSize = window->getSize();
    m_board.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2,
                                     static_cast<float>(windowSize.y) / 2));
}

GameContext::~GameContext() = default;

void GameContext::Update() {
}

void GameContext::Render() {
    m_window->draw(m_board);
}

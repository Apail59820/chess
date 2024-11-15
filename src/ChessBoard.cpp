//
// Created by Amaury Paillard on 08/11/2024.
//

#include "../include/ChessBoard.h"

#include <iostream>
#include <ostream>

#include "SFML/Graphics/RenderTarget.hpp"

ChessBoard::ChessBoard() {
    if (!m_texture.loadFromFile("../../assets/Boards/Board.png")) {
        std::cerr << "Failed to load board texture" << std::endl;
        return;
    }

    if (!m_borders_texture.loadFromFile("../../assets/Boards/ChessBoard.png")) {
        std::cerr << "Failed to load board borders texture" << std::endl;
        return;
    }

    m_texture.setSmooth(true);
    m_borders_texture.setSmooth(true);

    m_sprite.setTexture(m_texture);
    m_borders_sprite.setTexture(m_borders_texture);

    m_sprite.setScale(2.f, 2.f);
    m_borders_sprite.setScale(2.f, 2.f);

    const sf::FloatRect spriteBounds = m_sprite.getLocalBounds();
    m_sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);

    const sf::FloatRect bordersBounds = m_borders_sprite.getLocalBounds();
    m_borders_sprite.setOrigin(bordersBounds.width / 2, bordersBounds.height / 2);
}

ChessBoard::~ChessBoard() = default;

void ChessBoard::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_borders_sprite, states);
    target.draw(m_sprite, states);
}

sf::Vector2f ChessBoard::getPosition() const {
    return m_position;
}

void ChessBoard::setPosition(const sf::Vector2f &position) {
    m_position = position;
    m_sprite.setPosition(m_position.x, m_position.y);
    m_borders_sprite.setPosition(m_position.x, m_position.y);
}

sf::Vector2f ChessBoard::getSize() const {
    const sf::FloatRect bounds = m_borders_sprite.getGlobalBounds();
    return {bounds.width, bounds.height};
}

//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Queen.h"

#include "SFML/Graphics/RenderTarget.hpp"

Queen::Queen(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Queen::~Queen() = default;

void Queen::Update() {
}

void Queen::GetAvailableMoves() {
}

void Queen::SetTexture(sf::Texture& texture) {
    m_Sprite.setTexture(texture);
}

void Queen::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void Queen::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

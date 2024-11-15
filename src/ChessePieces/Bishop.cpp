//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Bishop.h"

#include "SFML/Graphics/RenderTarget.hpp"

Bishop::Bishop(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Bishop::~Bishop() = default;

void Bishop::Update() {
}

void Bishop::GetAvailableMoves() {
}

void Bishop::SetTexture(const sf::Texture& texture) {
    m_Sprite.setTexture(texture);
}

void Bishop::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
    if (m_bIsHoverActive) {
        target.draw(m_hoverRectangle, states);
    }
}

void Bishop::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

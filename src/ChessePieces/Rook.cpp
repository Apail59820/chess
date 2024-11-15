//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Rook.h"

#include "SFML/Graphics/RenderTarget.hpp"

Rook::Rook(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Rook::~Rook() = default;

void Rook::Update() {
}

void Rook::GetAvailableMoves() {
}

void Rook::SetTexture(const sf::Texture& texture) {
    m_Sprite.setTexture(texture);
}

void Rook::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
    if (m_bIsHoverActive) {
        target.draw(m_hoverRectangle, states);
    }
}

void Rook::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

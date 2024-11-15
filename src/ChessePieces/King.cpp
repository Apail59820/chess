//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/King.h"

#include "SFML/Graphics/RenderTarget.hpp"

King::King(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

King::~King() = default;

void King::Update() {
}

void King::GetAvailableMoves() {
}

void King::SetTexture(const sf::Texture &texture) {
    m_Sprite.setTexture(texture);
}

void King::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
    if (m_bIsHoverActive) {
        target.draw(m_hoverRectangle, states);
    }
}

void King::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

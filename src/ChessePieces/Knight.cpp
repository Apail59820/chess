//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Knight.h"
#include "SFML/Graphics/RenderTarget.hpp"

Knight::Knight(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Knight::~Knight() = default;

void Knight::Update() {
}

void Knight::GetAvailableMoves() {
}

void Knight::SetTexture(const sf::Texture& texture) {
    m_Sprite.setTexture(texture);
}

void Knight::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void Knight::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

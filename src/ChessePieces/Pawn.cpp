//
// Created by Amaury Paillard on 08/11/2024.
//

#include "../../include/ChessPieces/Pawn.h"

#include <ostream>

#include "SFML/Graphics/RenderTarget.hpp"

Pawn::Pawn(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Pawn::~Pawn() = default;

void Pawn::Update() {
}

void Pawn::GetAvailableMoves() {
}

void Pawn::SetTexture(sf::Texture& texture) {
    m_Sprite.setTexture(texture);
}

void Pawn::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void Pawn::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

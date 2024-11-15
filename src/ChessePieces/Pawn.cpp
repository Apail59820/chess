//
// Created by Amaury Paillard on 08/11/2024.
//

#include "../../include/ChessPieces/Pawn.h"

#include <iostream>
#include <ostream>

#include "../../include/Context.h"
#include "SFML/Graphics/RenderTarget.hpp"

Pawn::Pawn(const bool white) : m_bIsFirstMove(true) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Pawn::~Pawn() = default;

void Pawn::Update() {
    if (m_bIsHoverActive) {
        GetAvailableMoves();
    }
}

void Pawn::GetAvailableMoves() {
    if (m_bIsHoverActive) {
        const sf::Vector2i currentTile = GetCurrentTile();
        const int moveDirection = m_bIsWhite ? -1 : 1;

        std::vector<sf::Vector2i> availableMoves;

        if (!Context::GlobalContext) return;

        if (const sf::Vector2i forwardTile = currentTile + sf::Vector2i(0, moveDirection); !Context::GlobalContext->
            get()->IsPieceOnTile(forwardTile)) {
            availableMoves.push_back(forwardTile);
        }

        if ((m_bIsWhite && currentTile.y == 6) || (!m_bIsWhite && currentTile.y == 1)) {
            if (const sf::Vector2i doubleForwardTile = currentTile + sf::Vector2i(0, 2 * moveDirection); !
                Context::GlobalContext->get()->IsPieceOnTile(doubleForwardTile)) {
                availableMoves.push_back(doubleForwardTile);
            }
        }

        for (int dx = -1; dx <= 1; dx += 2) {
            if (sf::Vector2i attackTile = currentTile + sf::Vector2i(dx, moveDirection); Context::GlobalContext->get()->IsPieceOnTile(attackTile)) {
                //std::cout << "Capture available on: " << attackTile.x << ", " << attackTile.y << std::endl;
            }
        }

        m_legalMovesOverlay.updateLegalMoves(availableMoves);
    }
}

void Pawn::SetTexture(const sf::Texture &texture) {
    m_Sprite.setTexture(texture);
}

void Pawn::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
    if (m_bIsHoverActive) {
        target.draw(m_hoverRectangle, states);
        target.draw(m_legalMovesOverlay, states);
    }
}

void Pawn::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

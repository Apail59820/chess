//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Knight.h"

#include <iostream>

#include "../../include/Context.h"
#include "SFML/Graphics/RenderTarget.hpp"

Knight::Knight(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Knight::~Knight() = default;

void Knight::Update() {
    if (m_bIsHoverActive) {
        GetAvailableMoves();
    }
}

void Knight::GetAvailableMoves() {
    if (m_bIsHoverActive && !m_bIsBeingDragged) {
        const sf::Vector2i currentTile = GetCurrentTile();

        std::vector<sf::Vector2i> availableMoves;

        if (!Context::GlobalContext) return;

        const std::vector<sf::Vector2i> knightMoves = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };

        for (const auto &move: knightMoves) {
            if (sf::Vector2i targetTile = currentTile + move;
                GameContext::IsWithinBounds(targetTile) &&
                (!Context::GlobalContext->get()->IsPieceOnTile(targetTile) ||
                 Context::GlobalContext->get()->IsOpponentPiece(targetTile, m_bIsWhite))) {
                if (Context::GlobalContext->get()->IsOpponentPiece(targetTile, m_bIsWhite)) {
                    //std::cout << "Capture available on: " << attackTile.x << ", " << attackTile.y << std::endl;
                } else {
                    availableMoves.push_back(targetTile);
                }
            }
        }

        m_legalMovesOverlay.updateLegalMoves(availableMoves);
        m_availableMoves.clear();
        m_availableMoves = availableMoves;
    }
}

void Knight::DebugLog() {
    std::cout << "Knight::DebugLog()" << std::endl;
    std::cout << "Type : Knight" << std::endl;
    std::cout << "Position : x=" << GetPosition().x << ", y=" << GetPosition().y << std::endl;
    std::cout << "Is white : " << (m_bIsWhite ? "yes" : "no") << std::endl;
    std::cout << "Tile : x=" << GetCurrentTile().x << ", y=" << GetCurrentTile().y << std::endl;
}

Globals::PieceType Knight::GetType() const {
    return Globals::KNIGHT;
}


void Knight::SetTexture(const sf::Texture &texture) {
    m_Sprite.setTexture(texture);
}

void Knight::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void Knight::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

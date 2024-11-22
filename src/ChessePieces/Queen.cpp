//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Queen.h"

#include <iostream>

#include "../../include/Context.h"
#include "SFML/Graphics/RenderTarget.hpp"

Queen::Queen(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Queen::~Queen() = default;

void Queen::Update() {
    if (m_bIsHoverActive) {
        GetAvailableMoves();
    }
}

void Queen::GetAvailableMoves() {
    if (m_bIsHoverActive && !m_bIsBeingDragged) {
        const sf::Vector2i currentTile = GetCurrentTile();


        std::vector<sf::Vector2i> availableMoves;
        std::vector<sf::Vector2i> attackMoves;

        if (!Context::GlobalContext) return;

        const std::vector<sf::Vector2i> directions = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1},
            {1, 1},
            {1, -1},
            {-1, 1},
            {-1, -1}
        };

        for (const auto &direction: directions) {
            sf::Vector2i nextTile = currentTile;

            while (true) {
                nextTile += direction;

                if (!GameContext::IsWithinBounds(nextTile))
                    break;

                if (Context::GlobalContext->get()->IsPieceOnTile(nextTile)) {
                    if (Context::GlobalContext->get()->IsOpponentPiece(nextTile, m_bIsWhite)) {
                        attackMoves.push_back(nextTile);
                    }
                    break;
                }

                availableMoves.push_back(nextTile);
            }
        }

        m_legalMovesOverlay.updateLegalMoves(availableMoves);
        m_legalMovesOverlay.updateAttackMoves(attackMoves);

        m_availableMoves.clear();
        m_availableMoves = availableMoves;

        m_attackMoves.clear();
        m_attackMoves = attackMoves;
    }
}

Globals::PieceType Queen::GetType() const {
    return Globals::QUEEN;
}

void Queen::DebugLog() {
    std::cout << "Queen::DebugLog()" << std::endl;
    std::cout << "Type : Queen" << std::endl;
    std::cout << "Position : x=" << GetPosition().x << ", y=" << GetPosition().y << std::endl;
    std::cout << "Is white : " << (m_bIsWhite ? "yes" : "no") << std::endl;
    std::cout << "Tile : x=" << GetCurrentTile().x << ", y=" << GetCurrentTile().y << std::endl;
}


void Queen::SetTexture(const sf::Texture &texture) {
    m_Sprite.setTexture(texture);
}

void Queen::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void Queen::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

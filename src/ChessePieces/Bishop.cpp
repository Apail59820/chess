//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/Bishop.h"

#include "../../include/Context.h"
#include "SFML/Graphics/RenderTarget.hpp"

Bishop::Bishop(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

Bishop::~Bishop() = default;

void Bishop::Update() {
    if (m_bIsHoverActive) {
        GetAvailableMoves();
    }
}

void Bishop::GetAvailableMoves() {
    if (m_bIsHoverActive && !m_bIsBeingDragged) {
        const sf::Vector2i currentTile = GetCurrentTile();

        std::vector<sf::Vector2i> availableMoves;
        if (!Context::GlobalContext) return;

        const std::vector<sf::Vector2i> directions = {
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
                        //std::cout << "Capture available on: " << attackTile.x << ", " << attackTile.y << std::endl;
                    }
                    break;
                }

                availableMoves.push_back(nextTile);
            }
        }

        m_legalMovesOverlay.updateLegalMoves(availableMoves);
        m_availableMoves.clear();
        m_availableMoves = availableMoves;
    }
}


void Bishop::SetTexture(const sf::Texture &texture) {
    m_Sprite.setTexture(texture);
}

void Bishop::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void Bishop::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

Globals::PieceType Bishop::GetType() const {
    return Globals::BISHOP;
}

//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../../include/ChessPieces/King.h"

#include "../../include/Context.h"
#include "SFML/Graphics/RenderTarget.hpp"

King::King(const bool white) {
    m_bIsWhite = white;

    m_Sprite.setScale(2.0f, 2.0f);
}

King::~King() = default;

void King::Update() {
    if (m_bIsHoverActive) {
        GetAvailableMoves();
    }
}

void King::GetAvailableMoves() {
    if (!Context::GlobalContext) return;

    if (m_bIsHoverActive && !m_bIsBeingDragged) {
        const sf::Vector2i currentTile = GetCurrentTile();
        std::vector<sf::Vector2i> availableMoves;

        const std::vector<sf::Vector2i> directions = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1},
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
        };

        for (const auto &direction: directions) {
            if (const sf::Vector2i targetTile = currentTile + direction; GameContext::IsWithinBounds(targetTile)) {
                if (!Context::GlobalContext->get()->IsPieceOnTile(targetTile) ||
                    Context::GlobalContext->get()->IsOpponentPiece(targetTile, IsWhite())) {
                    availableMoves.push_back(targetTile);
                }
            }
        }

        AddCastlingMoves(availableMoves);

        m_legalMovesOverlay.updateLegalMoves(availableMoves);
        m_availableMoves.clear();
        m_availableMoves = availableMoves;
    }
}


void King::AddCastlingMoves(std::vector<sf::Vector2i> &moves) const {
    if (!Context::GlobalContext || m_bHasMoved) return;

    const sf::Vector2i currentTile = GetCurrentTile();

    if (CanCastle(currentTile, {7, currentTile.y}, {{5, currentTile.y}, {6, currentTile.y}})) {
        moves.emplace_back(6, currentTile.y);
    }

    if (CanCastle(currentTile, {0, currentTile.y}, {{1, currentTile.y}, {2, currentTile.y}, {3, currentTile.y}})) {
        moves.emplace_back(2, currentTile.y);
    }
}

bool King::CanCastle(const sf::Vector2i &kingTile, const sf::Vector2i &rookTile,
                     const std::initializer_list<sf::Vector2i> &pathToCheck) const {
    if (const auto *rook = Context::GlobalContext->get()->GetPieceAt(rookTile);
        !rook || rook->HasMoved() || rook->GetType() != Globals::PieceType::ROOK || rook->IsWhite() != IsWhite()) {
        return false;
    }

    for (const auto &tile: pathToCheck) {
        if (Context::GlobalContext->get()->IsPieceOnTile(tile) ||
            Context::GlobalContext->get()->IsTileAttacked(tile, !IsWhite())) {
            return false;
        }
    }

    if (Context::GlobalContext->get()->IsTileAttacked(kingTile, !IsWhite())) {
        return false;
    }

    return true;
}

Globals::PieceType King::GetType() const {
    return Globals::KING;
}

void King::SetTexture(const sf::Texture &texture) {
    m_Sprite.setTexture(texture);
}

void King::draw(sf::RenderTarget &target, const sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

void King::SetPosition(const sf::Vector2i position) {
    m_position = position;
    m_Sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
}

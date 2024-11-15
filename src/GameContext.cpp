//
// Created by Amaury Paillard on 08/11/2024.
//

#include "../include/GameContext.h"

#include <iostream>

#include "../include/Globals.h"
#include "../include/ChessPieces/Bishop.h"
#include "../include/ChessPieces/King.h"
#include "../include/ChessPieces/Knight.h"
#include "../include/ChessPieces/Pawn.h"
#include "../include/ChessPieces/Queen.h"
#include "../include/ChessPieces/Rook.h"

using namespace Globals::PiecesOffsets;
using namespace Globals;

GameContext::GameContext(sf::RenderWindow *window) {
    m_window = window;

    const sf::Vector2u windowSize = window->getSize();
    m_board.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2,
                                     static_cast<float>(windowSize.y) / 2));


    m_textureManager.LoadTextures();
    StartNewGame();
}

GameContext::~GameContext() = default;

void GameContext::Update() {
}

void GameContext::StartNewGame() {
    constexpr int squareSize = 64;
    constexpr int boardSize = 8 * squareSize;

    const sf::Vector2f boardCenterPosition = m_board.getPosition();

    const int TopLeftX = static_cast<int>(boardCenterPosition.x - static_cast<float>(boardSize) / 2);
    const int TopLeftY = static_cast<int>(boardCenterPosition.y - static_cast<float>(boardSize) / 2);

    const int whitePawnsStartY = TopLeftY + 6 * squareSize - PawnOffset;

    const int blackPawnsStartY = TopLeftY + squareSize - PawnOffset;


    InitializePawnRow(TopLeftX, whitePawnsStartY, true, m_textureManager.GetTexture(PAWN, true));
    InitializePawnRow(TopLeftX, blackPawnsStartY, false, m_textureManager.GetTexture(PAWN, false));

    InitializeMajorPiecesRow(TopLeftX, TopLeftY + 7 * 64, true);
    InitializeMajorPiecesRow(TopLeftX, TopLeftY, false);
}


void GameContext::Render() const {
    m_window->draw(m_board);

    for (const auto &piece: m_pieces) {
        m_window->draw(*piece);
    }
}


std::unique_ptr<ChessPiece> GameContext::CreatePiece(const PieceType type, bool isWhite, const sf::Texture &texture,
                                                     const sf::Vector2i &position) {
    std::unique_ptr<ChessPiece> piece;
    switch (type) {
        case PAWN:
            piece = std::make_unique<Pawn>(isWhite);
            break;
        case ROOK:
            piece = std::make_unique<Rook>(isWhite);
            break;
        case KNIGHT:
            piece = std::make_unique<Knight>(isWhite);
            break;
        case BISHOP:
            piece = std::make_unique<Bishop>(isWhite);
            break;
        case QUEEN:
            piece = std::make_unique<Queen>(isWhite);
            break;
        case KING:
            piece = std::make_unique<King>(isWhite);
            break;
    }
    piece->SetTexture(texture);
    piece->SetPosition(position);
    return piece;
}

void GameContext::InitializePawnRow(const int startX, int startY, const bool isWhite, const sf::Texture &texture) {
    for (int i = 0; i < 8; i++) {
        m_pieces.push_back(CreatePiece(PAWN, isWhite, texture, {startX + i * 64, startY}));
    }
}

void GameContext::InitializeMajorPiecesRow(const int startX, const int startY, const bool isWhite) {
    constexpr PieceType piecesOrder[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};

    for (int i = 0; i < 8; ++i) {
        sf::Vector2i position = {startX + i * 64, startY};
        m_pieces.push_back(CreatePiece(piecesOrder[i], isWhite, m_textureManager.GetTexture(piecesOrder[i], isWhite), position));
    }
}
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

GameContext::GameContext(sf::RenderWindow *window) {
    m_window = window;

    const sf::Vector2u windowSize = window->getSize();
    m_board.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2,
                                     static_cast<float>(windowSize.y) / 2));


    LoadTextures();
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

    InitializePawnRow(TopLeftX, whitePawnsStartY, true, whitePawnTexture);
    InitializePawnRow(TopLeftX, blackPawnsStartY, false, blackPawnTexture);

    InitializeMajorPiecesRow(TopLeftX, TopLeftY + 7 * 64, true);
    InitializeMajorPiecesRow(TopLeftX, TopLeftY, false);
}


void GameContext::Render() const {
    m_window->draw(m_board);

    for (const auto &piece: m_pieces) {
        m_window->draw(*piece);
    }
}

void GameContext::LoadTextures() {
    if (!whitePawnTexture.loadFromFile("../../assets/Pieces/PawnWhite.png")) {
        std::cerr << "Error : unable to load PawnWhite.png" << std::endl;
    }
    if (!blackPawnTexture.loadFromFile("../../assets/Pieces/PawnBlack.png")) {
        std::cerr << "Error : unable to load PawnBlack.png" << std::endl;
    }
    if (!whiteRookTexture.loadFromFile("../../assets/Pieces/RookWhite.png")) {
        std::cerr << "Error : unable to load RookWhite.png" << std::endl;
    }
    if (!blackRookTexture.loadFromFile("../../assets/Pieces/RookBlack.png")) {
        std::cerr << "Error : unable to load RookBlack.png" << std::endl;
    }
    if (!whiteKnightTexture.loadFromFile("../../assets/Pieces/NightWhite.png")) {
        std::cerr << "Error : unable to load KnightWhite.png" << std::endl;
    }
    if (!blackKnightTexture.loadFromFile("../../assets/Pieces/NightBlack.png")) {
        std::cerr << "Error : unable to load KnightBlack.png" << std::endl;
    }
    if (!whiteBishopTexture.loadFromFile("../../assets/Pieces/BishopWhite.png")) {
        std::cerr << "Error : unable to load BishopWhite.png" << std::endl;
    }
    if (!blackBishopTexture.loadFromFile("../../assets/Pieces/BishopBlack.png")) {
        std::cerr << "Error : unable to load BishopBlack.png" << std::endl;
    }
    if (!whiteQueenTexture.loadFromFile("../../assets/Pieces/QueenWhite.png")) {
        std::cerr << "Error : unable to load QueenWhite.png" << std::endl;
    }
    if (!blackQueenTexture.loadFromFile("../../assets/Pieces/QueenBlack.png")) {
        std::cerr << "Error : unable to load QueenBlack.png" << std::endl;
    }
    if (!blackKingTexture.loadFromFile("../../assets/Pieces/KingBlack.png")) {
        std::cerr << "Error : unable to load KingBlack.png" << std::endl;
    }
    if (!whiteKingTexture.loadFromFile("../../assets/Pieces/KingWhite.png")) {
        std::cerr << "Error : unable to load KingWhite.png" << std::endl;
    }
}

std::unique_ptr<ChessPiece> GameContext::CreatePiece(const PieceType type, bool isWhite, sf::Texture &texture,
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

void GameContext::InitializePawnRow(const int startX, int startY, const bool isWhite, sf::Texture &texture) {
    for (int i = 0; i < 8; i++) {
        m_pieces.push_back(CreatePiece(PAWN, isWhite, texture, {startX + i * 64, startY}));
    }
}

void GameContext::InitializeMajorPiecesRow(int startX, int startY, const bool isWhite) {
    m_pieces.push_back(CreatePiece(ROOK, isWhite, isWhite ? whiteRookTexture : blackRookTexture, {startX, startY}));
    m_pieces.push_back(CreatePiece(KNIGHT, isWhite, isWhite ? whiteKnightTexture : blackKnightTexture, {startX + 64, startY}));
    m_pieces.push_back(CreatePiece(BISHOP, isWhite, isWhite ? whiteBishopTexture : blackBishopTexture, {startX + 128, startY}));
    m_pieces.push_back(CreatePiece(QUEEN, isWhite, isWhite ? whiteQueenTexture : blackQueenTexture, {startX + 192, startY}));
    m_pieces.push_back(CreatePiece(KING, isWhite, isWhite ? whiteKingTexture : blackKingTexture, {startX + 256, startY}));
    m_pieces.push_back(CreatePiece(BISHOP, isWhite, isWhite ? whiteBishopTexture : blackBishopTexture, {startX + 320, startY}));
    m_pieces.push_back(CreatePiece(KNIGHT, isWhite, isWhite ? whiteKnightTexture : blackKnightTexture, {startX + 384, startY}));
    m_pieces.push_back(CreatePiece(ROOK, isWhite, isWhite ? whiteRookTexture : blackRookTexture, {startX + 448, startY}));
}
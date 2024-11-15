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

    // Init White Pawns
    for (int i = 0; i < 8; i++) {
        auto newPawn = std::make_unique<Pawn>(true);
        newPawn->SetTexture(whitePawnTexture);

        const int pawnX = TopLeftX + i * squareSize;
        newPawn->SetPosition(sf::Vector2i(pawnX, whitePawnsStartY));

        m_pieces.push_back(std::move(newPawn));
    }

    const int blackPawnsStartY = TopLeftY + squareSize - PawnOffset;

    // Init Black Pawns
    for (int i = 0; i < 8; i++) {
        auto newPawn = std::make_unique<Pawn>(false);
        newPawn->SetTexture(blackPawnTexture);

        const int pawnX = TopLeftX + i * squareSize;
        newPawn->SetPosition(sf::Vector2i(pawnX, blackPawnsStartY));

        m_pieces.push_back(std::move(newPawn));
    }

    auto BlackRookTopLeft = std::make_unique<Rook>(false);
    BlackRookTopLeft->SetTexture(blackRookTexture);
    auto BlackRookTopRight = std::make_unique<Rook>(false);
    BlackRookTopRight->SetTexture(blackRookTexture);

    auto WhiteRookBottomLeft = std::make_unique<Rook>(true);
    WhiteRookBottomLeft->SetTexture(whiteRookTexture);
    auto WhiteRookBottomRight = std::make_unique<Rook>(true);
    WhiteRookBottomRight->SetTexture(whiteRookTexture);

    // Init Rooks
    BlackRookTopLeft->SetPosition(sf::Vector2i(TopLeftX, TopLeftY));
    m_pieces.push_back(std::move(BlackRookTopLeft));

    BlackRookTopRight->SetPosition(sf::Vector2i(TopLeftX + 7 * squareSize, TopLeftY));
    m_pieces.push_back(std::move(BlackRookTopRight));

    WhiteRookBottomLeft->SetPosition(sf::Vector2i(TopLeftX, TopLeftY + squareSize * 7));
    m_pieces.push_back(std::move(WhiteRookBottomLeft));

    WhiteRookBottomRight->SetPosition(sf::Vector2i(TopLeftX + squareSize * 7, TopLeftY + squareSize * 7));
    m_pieces.push_back(std::move(WhiteRookBottomRight));

    auto BlackKnightTopLeft = std::make_unique<Knight>(false);
    BlackKnightTopLeft->SetTexture(blackKnightTexture);
    auto BlackKnightTopRight = std::make_unique<Knight>(false);
    BlackKnightTopRight->SetTexture(blackKnightTexture);

    auto WhiteKnightBottomLeft = std::make_unique<Knight>(true);
    WhiteKnightBottomLeft->SetTexture(whiteKnightTexture);
    auto WhiteKnightBottomRight = std::make_unique<Knight>(true);
    WhiteKnightBottomRight->SetTexture(whiteKnightTexture);

    // Init Knights

    BlackKnightTopLeft->SetPosition(sf::Vector2i(TopLeftX + squareSize, TopLeftY - KnightOffset));
    m_pieces.push_back(std::move(BlackKnightTopLeft));

    BlackKnightTopRight->SetPosition(sf::Vector2i(TopLeftX + 6 * squareSize, TopLeftY - KnightOffset));
    m_pieces.push_back(std::move(BlackKnightTopRight));

    WhiteKnightBottomLeft->SetPosition(sf::Vector2i(TopLeftX + squareSize, TopLeftY + squareSize * 7 - KnightOffset));
    m_pieces.push_back(std::move(WhiteKnightBottomLeft));

    WhiteKnightBottomRight->SetPosition(sf::Vector2i(TopLeftX + squareSize * 6,
                                                     TopLeftY + squareSize * 7 - KnightOffset));
    m_pieces.push_back(std::move(WhiteKnightBottomRight));

    auto BlackBishopTopLeft = std::make_unique<Bishop>(false);
    BlackBishopTopLeft->SetTexture(blackBishopTexture);
    auto BlackBishopTopRight = std::make_unique<Bishop>(false);
    BlackBishopTopRight->SetTexture(blackBishopTexture);

    auto WhiteBishopBottomLeft = std::make_unique<Bishop>(true);
    WhiteBishopBottomLeft->SetTexture(whiteBishopTexture);
    auto WhiteBishopBottomRight = std::make_unique<Bishop>(true);
    WhiteBishopBottomRight->SetTexture(whiteBishopTexture);

    // Init Bishops

    BlackBishopTopLeft->SetPosition(sf::Vector2i(TopLeftX + squareSize * 2, TopLeftY - BishopOffset));
    m_pieces.push_back(std::move(BlackBishopTopLeft));

    BlackBishopTopRight->SetPosition(sf::Vector2i(TopLeftX + 5 * squareSize, TopLeftY - BishopOffset));
    m_pieces.push_back(std::move(BlackBishopTopRight));

    WhiteBishopBottomLeft->SetPosition(
        sf::Vector2i(TopLeftX + squareSize * 2, TopLeftY + squareSize * 7 - BishopOffset));
    m_pieces.push_back(std::move(WhiteBishopBottomLeft));

    WhiteBishopBottomRight->SetPosition(sf::Vector2i(TopLeftX + squareSize * 5,
                                                     TopLeftY + squareSize * 7 - BishopOffset));
    m_pieces.push_back(std::move(WhiteBishopBottomRight));

    // Init Queens
    auto BlackQueen = std::make_unique<Queen>(false);
    BlackQueen->SetTexture(blackQueenTexture);
    BlackQueen->SetPosition(sf::Vector2i(TopLeftX + squareSize * 3, TopLeftY - QueenOffset));
    m_pieces.push_back(std::move(BlackQueen));

    auto WhiteQueen = std::make_unique<Queen>(true);
    WhiteQueen->SetTexture(whiteQueenTexture);
    WhiteQueen->SetPosition(sf::Vector2i(TopLeftX + squareSize * 3, TopLeftY + squareSize * 7 - QueenOffset));
    m_pieces.push_back(std::move(WhiteQueen));

    // Init Kings
    auto BlackKing = std::make_unique<King>(false);
    BlackKing->SetTexture(blackKingTexture);
    BlackKing->SetPosition(sf::Vector2i(TopLeftX + squareSize * 4, TopLeftY));
    m_pieces.push_back(std::move(BlackKing));

    auto WhiteKing = std::make_unique<King>(true);
    WhiteKing->SetTexture(whiteKingTexture);
    WhiteKing->SetPosition(sf::Vector2i(TopLeftX + squareSize * 4, TopLeftY + squareSize * 7));
    m_pieces.push_back(std::move(WhiteKing));

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
    if(!blackKingTexture.loadFromFile("../../assets/Pieces/KingBlack.png")) {
        std::cerr << "Error : unable to load KingBlack.png" << std::endl;
    }
    if(!whiteKingTexture.loadFromFile("../../assets/Pieces/KingWhite.png")) {
        std::cerr << "Error : unable to load KingWhite.png" << std::endl;
    }
}

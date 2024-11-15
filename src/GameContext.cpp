//
// Created by Amaury Paillard on 08/11/2024.
//

#include "../include/GameContext.h"

#include <iostream>

#include "../include/ChessPieces/Pawn.h"

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

    const int whitePawnsTopLeftX = static_cast<int>(boardCenterPosition.x - static_cast<float>(boardSize) / 2);
    const int whitePawnsTopLeftY = static_cast<int>(boardCenterPosition.y - static_cast<float>(boardSize) / 2);

    const int whitePawnsStartY = whitePawnsTopLeftY + 6 * squareSize - 12;

    // Init White Pawns
    for (int i = 0; i < 8; i++) {
        auto newPawn = std::make_unique<Pawn>(true);
        newPawn->SetTexture(whitePawnTexture);

        const int pawnX = whitePawnsTopLeftX + i * squareSize;
        newPawn->SetPosition(sf::Vector2i(pawnX, whitePawnsStartY));

        m_pieces.push_back(std::move(newPawn));
    }


    const int blackPawnsTopLeftX = static_cast<int>(boardCenterPosition.x - static_cast<float>(boardSize) / 2);
    const int blackPawnsTopLeftY = static_cast<int>(boardCenterPosition.y - static_cast<float>(boardSize) / 2);

    const int blackPawnsStartY = blackPawnsTopLeftY + squareSize - 12;

    // Init Black Pawns
    for (int i = 0; i < 8; i++) {
        auto newPawn = std::make_unique<Pawn>(false);
        newPawn->SetTexture(blackPawnTexture);

        const int pawnX = blackPawnsTopLeftX + i * squareSize;
        newPawn->SetPosition(sf::Vector2i(pawnX, blackPawnsStartY));

        m_pieces.push_back(std::move(newPawn));
    }
}



void GameContext::Render() {
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
}

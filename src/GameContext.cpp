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
#include "SFML/Window/Mouse.hpp"

using namespace Globals;

GameContext::GameContext(sf::RenderWindow *window): m_black_timer(sf::seconds(60 * 15)),
                                                    m_white_timer(sf::seconds(60 * 15)) {
    m_window = window;

    const sf::Vector2u windowSize = window->getSize();
    m_board.setPosition(sf::Vector2f(static_cast<float>(windowSize.x) / 2,
                                     static_cast<float>(windowSize.y) / 2));


    m_textureManager.LoadTextures();

    m_black_timer.SetPosition(sf::Vector2i(static_cast<int>(windowSize.x) / 2 + 245,
                                           static_cast<int>(windowSize.y) / 2 - 310));
    m_white_timer.SetPosition(sf::Vector2i(static_cast<int>(windowSize.x) / 2 + 245,
                                           static_cast<int>(windowSize.y) / 2 + 270));

    StartNewGame();
}

GameContext::~GameContext() = default;

void GameContext::Update() {
    m_mouse_pos = sf::Mouse::getPosition(*m_window);

    m_black_timer.Update();
    m_white_timer.Update();

    for (const auto &piece: m_pieces) {
        piece->Update();
        if (!isDragging) {
            piece->Hover(m_mouse_pos);
        }
    }
}

void GameContext::StartNewGame() {
    constexpr int squareSize = 64;
    constexpr int boardSize = 8 * squareSize;

    const sf::Vector2f boardCenterPosition = m_board.getPosition();

    const int TopLeftX = static_cast<int>(boardCenterPosition.x - static_cast<float>(boardSize) / 2);
    const int TopLeftY = static_cast<int>(boardCenterPosition.y - static_cast<float>(boardSize) / 2);

    const int whitePawnsStartY = TopLeftY + 6 * squareSize;

    const int blackPawnsStartY = TopLeftY + squareSize;


    InitializePawnRow(TopLeftX, whitePawnsStartY, true, m_textureManager.GetTexture(PAWN, true));
    InitializePawnRow(TopLeftX, blackPawnsStartY, false, m_textureManager.GetTexture(PAWN, false));

    InitializeMajorPiecesRow(TopLeftX, TopLeftY + 7 * 64, true);
    InitializeMajorPiecesRow(TopLeftX, TopLeftY, false);

    m_white_timer.Start();
}


void GameContext::Render() const {
    m_window->draw(m_board);

    for (const auto &piece: m_pieces) {
        m_window->draw(*piece);
    }

    m_window->draw(m_white_timer);
    m_window->draw(m_black_timer);
}

void GameContext::HandleMouseEvents(const sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        for (auto &piece: m_pieces) {
            if (piece->GetBounds().contains(mousePos)) {
                selectedPiece = &piece;
                originalDragPosition = selectedPiece->get()->GetPosition();
                isDragging = true;
                selectedPiece->get()->setIsDragged(true);
                break;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && isDragging) {
        const sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        if (selectedPiece) {
            const sf::Vector2i targetCell = GetMouseTile(mousePos);

            if (const std::vector<sf::Vector2i> legalMoves = selectedPiece->get()->GetLegalMoves(); isMoveLegal(
                targetCell, legalMoves)) {
                const sf::Vector2f newPosition = TileToCoords(targetCell);
                selectedPiece->get()->SetPosition(newPosition);
            } else {
                selectedPiece->get()->SetPosition(originalDragPosition);
            }

            selectedPiece->get()->setIsDragged(false);
        }

        selectedPiece = nullptr;
        isDragging = false;
    }

    if (event.type == sf::Event::MouseMoved && isDragging && selectedPiece) {
        const sf::Vector2f mousePos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
        selectedPiece->get()->SetPosition(sf::Vector2f(mousePos.x - 32.f, mousePos.y - 32.f));
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

bool GameContext::IsPieceOnTile(const sf::Vector2i &targetSquare) const {
    for (const auto &piece: m_pieces) {
        if (sf::Vector2i pieceGridPosition = piece->GetCurrentTile(); pieceGridPosition == targetSquare) {
            return true;
        }
    }
    return false;
}

sf::Vector2i GameContext::GetMouseTile(const sf::Vector2f mousePos) {
    auto boardPosition = sf::Vector2i(
        static_cast<int>(ChessBoardSprite->getPosition().x),
        static_cast<int>(ChessBoardSprite->getPosition().y)
    );

    boardPosition.x -= static_cast<int>(ChessBoardSprite->getGlobalBounds().width / 2);
    boardPosition.y -= static_cast<int>(ChessBoardSprite->getGlobalBounds().height / 2);

    const int offsetX = static_cast<int>(mousePos.x) - boardPosition.x;
    const int offsetY = static_cast<int>(mousePos.y) - boardPosition.y;

    const int tileX = offsetX / 64;
    const int tileY = offsetY / 64;


    return {tileX, tileY};
}

sf::Vector2f GameContext::TileToCoords(const sf::Vector2i tile) {
    auto boardPosition = sf::Vector2i(
        static_cast<int>(ChessBoardSprite->getPosition().x),
        static_cast<int>(ChessBoardSprite->getPosition().y)
    );

    boardPosition.x -= static_cast<int>(ChessBoardSprite->getGlobalBounds().width / 2);
    boardPosition.y -= static_cast<int>(ChessBoardSprite->getGlobalBounds().height / 2);

    boardPosition.x += tile.x * 64;
    boardPosition.y += tile.y * 64;

    return {static_cast<float>(boardPosition.x), static_cast<float>(boardPosition.y)};
}

bool GameContext::isMoveLegal(const sf::Vector2i &targetCell, const std::vector<sf::Vector2i> &legalMoves) {
    return std::any_of(legalMoves.begin(), legalMoves.end(), [&](const sf::Vector2i &move) {
        return move == targetCell;
    });
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
        m_pieces.push_back(CreatePiece(piecesOrder[i], isWhite, m_textureManager.GetTexture(piecesOrder[i], isWhite),
                                       position));
    }
}

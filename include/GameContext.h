//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Timer.h"
#include "SFML/Graphics/RenderWindow.hpp"

class GameContext {
public:
    explicit GameContext(sf::RenderWindow *window);

    ~GameContext();

    void StartNewGame();

    void Update();

    void Render() const;

    void HandleMouseEvents(const sf::Event &event);

    bool IsPieceOnTile(const sf::Vector2i &targetSquare) const;
    bool IsOpponentPiece(sf::Vector2i targetTile, bool isWhite) const;
    static bool IsWithinBounds(sf::Vector2i targetTile) ;

    ChessPiece* GetPieceAt(const sf::Vector2i& targetTile) const;
    bool IsTileAttacked(const sf::Vector2i& targetTile, bool attackerIsWhite) const;

    std::unique_ptr<ChessPiece> GetKing(bool white) const;

private:

    static std::unique_ptr<ChessPiece> CreatePiece(Globals::PieceType type, bool isWhite, const sf::Texture &texture, const sf::Vector2i &position);

    void InitializePawnRow(int startX, int startY, bool isWhite, const sf::Texture &texture);
    void InitializeMajorPiecesRow(int startX, int startY, bool isWhite);
    static sf::Vector2i GetMouseTile(sf::Vector2f mousePos);

    static sf::Vector2f TileToCoords(sf::Vector2i tile);

    static bool isMoveLegal(const sf::Vector2i& targetCell, const std::vector<sf::Vector2i>& legalMoves);

    sf::Vector2i m_mouse_pos;

    ChessBoard m_board;
    sf::RenderWindow *m_window;

    Timer m_black_timer, m_white_timer;

    std::vector<std::unique_ptr<ChessPiece>> m_pieces;
    TextureManager m_textureManager;

    sf::Vector2f originalDragPosition;
    std::unique_ptr<ChessPiece> *selectedPiece = nullptr;
    bool isDragging = false;

    bool whiteTurn = true;
};

#endif //GAMECONTEXT_H

//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "SFML/Graphics/RenderWindow.hpp"

class GameContext {
public:
    explicit GameContext(sf::RenderWindow *window);

    ~GameContext();

    void StartNewGame();

    void Update();

    void Render() const;


private:

    enum PieceType {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};

    static std::unique_ptr<ChessPiece> CreatePiece(PieceType type, bool isWhite, sf::Texture &texture, const sf::Vector2i &position);
    void InitializePawnRow(int startX, int startY, bool isWhite, sf::Texture &texture);
    void InitializeMajorPiecesRow(int startX, int startY, bool isWhite);

    void LoadTextures();

    ChessBoard m_board;
    sf::RenderWindow *m_window;

    std::vector<std::unique_ptr<ChessPiece>> m_pieces;

    sf::Texture whitePawnTexture;
    sf::Texture blackPawnTexture;

    sf::Texture whiteRookTexture;
    sf::Texture blackRookTexture;

    sf::Texture whiteKnightTexture;
    sf::Texture blackKnightTexture;

    sf::Texture whiteBishopTexture;
    sf::Texture blackBishopTexture;

    sf::Texture whiteQueenTexture;
    sf::Texture blackQueenTexture;

    sf::Texture whiteKingTexture;
    sf::Texture blackKingTexture;
};

#endif //GAMECONTEXT_H

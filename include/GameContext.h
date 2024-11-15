//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef GAMECONTEXT_H
#define GAMECONTEXT_H

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Globals.h"
#include "TextureManager.h"
#include "SFML/Graphics/RenderWindow.hpp"

class GameContext {
public:
    explicit GameContext(sf::RenderWindow *window);

    ~GameContext();

    void StartNewGame();

    void Update();

    void Render() const;


private:

    static std::unique_ptr<ChessPiece> CreatePiece(Globals::PieceType type, bool isWhite, const sf::Texture &texture, const sf::Vector2i &position);
    void InitializePawnRow(int startX, int startY, bool isWhite, const sf::Texture &texture);
    void InitializeMajorPiecesRow(int startX, int startY, bool isWhite);

    ChessBoard m_board;
    sf::RenderWindow *m_window;

    std::vector<std::unique_ptr<ChessPiece>> m_pieces;
    TextureManager m_textureManager;
};

#endif //GAMECONTEXT_H

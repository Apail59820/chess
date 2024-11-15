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

    void LoadTextures();

    ChessBoard m_board;
    sf::RenderWindow *m_window;

    std::vector<std::unique_ptr<ChessPiece>> m_pieces;

    sf::Texture whitePawnTexture;
    sf::Texture blackPawnTexture;
};

#endif //GAMECONTEXT_H

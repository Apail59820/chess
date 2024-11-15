//
// Created by Amaury Paillard on 15/11/2024.
//

#pragma once

#ifndef GLOBALS_H
#define GLOBALS_H


#include "SFML/Graphics.hpp"

namespace Globals {
    enum PieceType {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};

    inline sf::Sprite* ChessBoardSprite;
}


#endif //GLOBALS_H

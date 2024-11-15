//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef GLOBALS_H
#define GLOBALS_H

namespace Globals::PiecesOffsets {
    constexpr int PawnOffset = 12;
    constexpr int KnightOffset = 5;
    constexpr int BishopOffset = 5;
    constexpr int QueenOffset = 4;
}

namespace Globals {
    enum PieceType {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
}

#endif //GLOBALS_H

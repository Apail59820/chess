//
// Created by Amaury Paillard on 15/11/2024.
//

#include "../include/TextureManager.h"

#include <iostream>

using namespace Globals;

void TextureManager::LoadTextures() {
    LoadTexture(whitePawnTexture, "PawnWhite.png");
    LoadTexture(blackPawnTexture, "PawnBlack.png");

    LoadTexture(whiteRookTexture, "RookWhite.png");
    LoadTexture(blackRookTexture, "RookBlack.png");

    LoadTexture(whiteKnightTexture, "KnightWhite.png");
    LoadTexture(blackKnightTexture, "KnightBlack.png");

    LoadTexture(whiteBishopTexture, "BishopWhite.png");
    LoadTexture(blackBishopTexture, "BishopBlack.png");

    LoadTexture(whiteQueenTexture, "QueenWhite.png");
    LoadTexture(blackQueenTexture, "QueenBlack.png");

    LoadTexture(whiteKingTexture, "KingWhite.png");
    LoadTexture(blackKingTexture, "KingBlack.png");
}

const sf::Texture &TextureManager::GetTexture(const PieceType type, const bool isWhite) const {
    switch (type) {
        case PAWN:
            return isWhite ? whitePawnTexture : blackPawnTexture;
        case ROOK:
            return isWhite ? whiteRookTexture : blackRookTexture;
        case KNIGHT:
            return isWhite ? whiteKnightTexture : blackKnightTexture;
        case BISHOP:
            return isWhite ? whiteBishopTexture : blackBishopTexture;
        case QUEEN:
            return isWhite ? whiteQueenTexture : blackQueenTexture;
        case KING:
            return isWhite ? whiteKingTexture : blackKingTexture;
        default:
            std::cerr << "Unknown texture type" << std::endl;
            throw std::runtime_error("[FATAL ERROR] : Texture not found.");
    }
}

void TextureManager::LoadTexture(sf::Texture &texture, const std::string &fileName) {
    if (!texture.loadFromFile("../../assets/Pieces/" + fileName)) {
        std::cerr << "Error : unable to load " << fileName << std::endl;
    }
}

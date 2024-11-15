//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "Globals.h"
#include "SFML/Graphics/Texture.hpp"

class TextureManager {
public:
    void LoadTextures();

    const sf::Texture &GetTexture(Globals::PieceType type, bool isWhite) const;

private:
    sf::Texture whitePawnTexture, blackPawnTexture;
    sf::Texture whiteRookTexture, blackRookTexture;

    sf::Texture whiteKnightTexture, blackKnightTexture;
    sf::Texture whiteBishopTexture, blackBishopTexture;

    sf::Texture whiteQueenTexture, blackQueenTexture;
    sf::Texture whiteKingTexture, blackKingTexture;

    static void LoadTexture(sf::Texture &texture, const std::string &fileName);
};

#endif //TEXTUREMANAGER_H

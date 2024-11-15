//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class ChessPiece : public sf::Drawable {
public:
    ChessPiece() = default;

    ~ChessPiece() override = default;

    virtual void Update() = 0;

    virtual void GetAvailableMoves() = 0;

    virtual void SetPosition(sf::Vector2i position) = 0;

    virtual void SetTexture(sf::Texture& texture) = 0;

    void SetIsWhite(const bool isWhite) {
        m_bIsWhite = isWhite;
    }

protected:

    sf::Sprite m_Sprite;

    sf::Vector2i m_position;
    bool m_bIsWhite = false;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif //CHESSPIECE_H

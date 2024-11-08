//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class ChessBoard final : public sf::Drawable {
public:
    ChessBoard();

    ~ChessBoard() override;

    sf::Vector2f getPosition() const;

    void setPosition(const sf::Vector2f &position);

    sf::Vector2f getSize() const;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Sprite m_sprite, m_borders_sprite;
    sf::Texture m_texture, m_borders_texture;

    sf::Vector2f m_position;
};

#endif //CHESSBOARD_H

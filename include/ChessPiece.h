//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class ChessPiece : public sf::Drawable {
public:
    ChessPiece() {
        m_hoverRectangle.setSize({64.f, 64.f});
        m_hoverRectangle.setFillColor(sf::Color::Transparent);
        m_hoverRectangle.setOutlineColor(sf::Color::Green);
        m_hoverRectangle.setOutlineThickness(2.f);
    };

    ~ChessPiece() override = default;

    virtual void Update() = 0;

    virtual void GetAvailableMoves() = 0;

    virtual void SetPosition(sf::Vector2i position) = 0;

    virtual void SetTexture(const sf::Texture &texture) = 0;

    void Hover(const sf::Vector2i &mousePosition) {
        if (const sf::FloatRect bounds = m_Sprite.getGlobalBounds(); bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
            m_bIsHoverActive = true;

            m_hoverRectangle.setPosition(
                m_Sprite.getPosition().x + m_Sprite.getGlobalBounds().width / 2 - m_hoverRectangle.getSize().x / 2,
                m_Sprite.getPosition().y + m_Sprite.getGlobalBounds().height / 2 - m_hoverRectangle.getSize().y / 2);
        } else {
            m_bIsHoverActive = false;
        }
    }

    void SetIsWhite(const bool isWhite) {
        m_bIsWhite = isWhite;
    }

protected:
    sf::Sprite m_Sprite;
    sf::RectangleShape m_hoverRectangle;

    sf::Vector2i m_position;
    bool m_bIsWhite = false;
    bool m_bIsHoverActive = false;
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};

#endif //CHESSPIECE_H

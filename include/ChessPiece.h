//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "Globals.h"
#include "LegalMovesOverlay.h"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"

class ChessPiece : public sf::Drawable {
public:
    ChessPiece() : m_legalMovesOverlay(10.0f) {
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
        if (const sf::FloatRect bounds = m_Sprite.getGlobalBounds(); bounds.contains(
            static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
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

    sf::Vector2i GetCurrentTile() const {
        auto boardPosition = sf::Vector2i(
            static_cast<int>(Globals::ChessBoardSprite->getPosition().x),
            static_cast<int>(Globals::ChessBoardSprite->getPosition().y)
        );

        boardPosition.x -= static_cast<int>(Globals::ChessBoardSprite->getGlobalBounds().width / 2);
        boardPosition.y -= static_cast<int>(Globals::ChessBoardSprite->getGlobalBounds().height / 2);

        const int offsetX = m_position.x - boardPosition.x;
        const int offsetY = m_position.y - boardPosition.y;

        const int tileX = offsetX / 64;
        const int tileY = offsetY / 64;


        return {tileX, tileY};
    }

    sf::FloatRect GetBounds() const {
        return m_Sprite.getGlobalBounds();
    }

    sf::Vector2f GetPosition() const {
        return m_Sprite.getPosition();
    }

    void SetPosition(const sf::Vector2f position) {
        m_Sprite.setPosition(position);
        m_position = sf::Vector2i(static_cast<int>(position.x), static_cast<int>(position.y));
    }

    void setIsDragged(const bool bState) {
        m_bIsBeingDragged = bState;
    }

    std::vector<sf::Vector2i> GetLegalMoves() const {
        return m_availableMoves;
    }

    bool IsWhite() const {
        return m_bIsWhite;
    }

    bool HasMoved() const {
        return m_bHasMoved;
    }

    void SetHasMoved() {
        m_bHasMoved = true;
    }

    virtual Globals::PieceType GetType() const = 0;

protected:
    sf::Sprite m_Sprite;
    sf::RectangleShape m_hoverRectangle;

    sf::Vector2i m_position;
    bool m_bIsWhite = false;
    bool m_bIsHoverActive = false;
    bool m_bIsBeingDragged = false;
    bool m_bHasMoved = false;

    LegalMovesOverlay m_legalMovesOverlay;

    std::vector<sf::Vector2i> m_availableMoves;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

};

#endif //CHESSPIECE_H

//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef LEGALMOVESOVERLAY_H
#define LEGALMOVESOVERLAY_H
#include <vector>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

class LegalMovesOverlay final : public sf::Drawable {
public:
    explicit LegalMovesOverlay(const float radius) : m_circleRadius(radius) {
        // CTOR
    }

    void updateLegalMoves(const std::vector<sf::Vector2i> &legalMoves) {
        m_legalMovesCircles.clear();

        auto boardPosition = sf::Vector2i(
            static_cast<int>(Globals::ChessBoardSprite->getPosition().x),
            static_cast<int>(Globals::ChessBoardSprite->getPosition().y)
        );

        boardPosition.x -= static_cast<int>(Globals::ChessBoardSprite->getGlobalBounds().width / 2);
        boardPosition.y -= static_cast<int>(Globals::ChessBoardSprite->getGlobalBounds().height / 2);

        for (const auto &move: legalMoves) {
            sf::CircleShape circle(m_circleRadius);
            circle.setOrigin(m_circleRadius, m_circleRadius);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition(static_cast<float>(move.x * 64 + boardPosition.x + 32),
                               static_cast<float>(move.y * 64 + boardPosition.y + 32));
            m_legalMovesCircles.push_back(circle);
        }
    }

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        for (const auto &circle: m_legalMovesCircles) {
            target.draw(circle);
        }
    }

    std::vector<sf::CircleShape> m_legalMovesCircles;
    float m_circleRadius;
};

#endif //LEGALMOVESOVERLAY_H

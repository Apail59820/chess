//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef QUEEN_H
#define QUEEN_H

#include "../ChessPiece.h"

class Queen final : public ChessPiece {
public:
    explicit Queen(bool white);

    ~Queen() override;

    void Update() override;

    void GetAvailableMoves() override;

    void SetPosition(sf::Vector2i position) override;

    void SetTexture(const sf::Texture &texture) override;

    Globals::PieceType GetType() const override;

    void DebugLog() override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //QUEEN_H

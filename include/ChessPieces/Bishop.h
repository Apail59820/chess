//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef BISHOP_H
#define BISHOP_H

#include "../ChessPiece.h"

class Bishop final : public ChessPiece {
public:

    explicit Bishop(bool white);
    ~Bishop() override;

    void Update() override;
    void GetAvailableMoves() override;

    void SetPosition(sf::Vector2i position) override;

    void SetTexture(const sf::Texture &texture) override;

    Globals::PieceType GetType() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //BISHOP_H

//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "../ChessPiece.h"

class Knight final : public ChessPiece {
public:

    explicit Knight(bool white);
    ~Knight() override;

    void Update() override;
    void GetAvailableMoves() override;

    void SetPosition(sf::Vector2i position) override;

    void SetTexture(const sf::Texture &texture) override;

    void DebugLog() override;

    Globals::PieceType GetType() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif //KNIGHT_H

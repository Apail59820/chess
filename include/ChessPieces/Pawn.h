//
// Created by Amaury Paillard on 08/11/2024.
//

#ifndef PAWN_H
#define PAWN_H
#include "../ChessPiece.h"

class Pawn final : public ChessPiece {
public:

    explicit Pawn(bool white);
    ~Pawn() override;

    void Update() override;
    void GetAvailableMoves() override;

    void SetPosition(sf::Vector2i position) override;

    void SetTexture(const sf::Texture &texture) override;

    Globals::PieceType GetType() const override;

    void DebugLog() override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool m_bIsFirstMove;
};

#endif //PAWN_H

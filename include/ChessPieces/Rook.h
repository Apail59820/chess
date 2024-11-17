//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef ROOK_H
#define ROOK_H
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

#include "../ChessPiece.h"

class Rook final : public ChessPiece {
public:
    explicit Rook(bool white);

    ~Rook() override;

    void Update() override;

    void GetAvailableMoves() override;

    void SetPosition(sf::Vector2i position) override;

    void SetTexture(const sf::Texture &texture) override;

    Globals::PieceType GetType() const override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //ROOK_H

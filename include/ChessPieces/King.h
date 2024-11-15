//
// Created by Amaury Paillard on 15/11/2024.
//

#ifndef KING_H
#define KING_H

#include "../ChessPiece.h"

class King final : public ChessPiece {
public:
    explicit King(bool white);

    ~King() override;

    void Update() override;

    void GetAvailableMoves() override;

    void SetPosition(sf::Vector2i position) override;

    void SetTexture(sf::Texture &texture) override;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //KING_H

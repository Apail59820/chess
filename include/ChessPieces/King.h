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

    void SetTexture(const sf::Texture &texture) override;

    void AddCastlingMoves(std::vector<sf::Vector2i> &moves) const;

    Globals::PieceType GetType() const override;

private:
    bool CanCastle(
        const sf::Vector2i &kingTile,
        const sf::Vector2i &rookTile,
        const std::initializer_list<sf::Vector2i> &pathToCheck) const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif //KING_H

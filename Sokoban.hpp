// Copyright 2025 <Mark Daoud>
#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
    static const int TILE_SIZE = 64;

    Sokoban();

    unsigned int height() const {
        return _height;
    }
    unsigned int width() const {
        return _width;
    }

    sf::Vector2u playerLoc() const {
        return _playerLoc;
    }

    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();

    friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
    friend std::istream& operator>>(std::istream& in, Sokoban& s);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int _height;
    unsigned int _width;

    std::vector<std::vector<char>> _board;
    std::vector<std::vector<char>> _initialBoard;
    sf::Vector2u _playerLoc;
    sf::Vector2u _initialPlayerLoc;
    sf::Texture wallTexture, boxTexture, storageTexture, groundTexture,
                playerDown, playerUp, playerLeft, playerRight;
    sf::Sprite wallSprite, boxSprite, playerSprite, storageSprite, groundSprite;
};


}  // namespace SB

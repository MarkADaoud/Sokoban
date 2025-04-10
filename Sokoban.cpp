// Copyright 2025 <Mark Daoud>

#include "Sokoban.hpp"
#include <iostream>
#include <algorithm>

namespace SB {
Sokoban::Sokoban() : _height(0), _width(0) {
    if (!wallTexture.loadFromFile("block_06.png")) {
      std::cerr << "Error loading wall texture" << std::endl;
    }
    if (!boxTexture.loadFromFile("crate_03.png")) {
      std::cerr << "Error loading box texture" << std::endl;
    }
    if (!playerDown.loadFromFile("player_05.png")) {
      std::cerr << "Error loading player texture" << std::endl;
    }
    if (!playerUp.loadFromFile("player_08.png")) {
      std::cerr << "Error loading player texture" << std::endl;
    }
    if (!playerRight.loadFromFile("player_17.png")) {
      std::cerr << "Error loading player texture" << std::endl;
    }
    if (!playerLeft.loadFromFile("player_20.png")) {
      std::cerr << "Error loading player texture" << std::endl;
    }
    if (!storageTexture.loadFromFile("ground_04.png")) {
      std::cerr << "Error loading storage texture" << std::endl;
    }
    if (!groundTexture.loadFromFile("ground_01.png")) {
      std::cerr << "Error loading ground texture" << std::endl;
    }
    wallSprite.setTexture(wallTexture);
    boxSprite.setTexture(boxTexture);
    playerSprite.setTexture(playerDown);
    storageSprite.setTexture(storageTexture);
    groundSprite.setTexture(groundTexture);
}

void Sokoban::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (unsigned int y = 0; y < _height; y++) {
    for (unsigned int x = 0; x < _width; x++) {
        sf::Sprite ground = groundSprite;
        ground.setPosition(x * TILE_SIZE, y * TILE_SIZE);
        target.draw(ground, states);

        sf::Sprite sprite;
        switch (_board[y][x]) {
        case '#':
          sprite = wallSprite;
          break;
        case 'A':
        case '1':
          sprite = boxSprite;
          break;
        case 'a':
          sprite = storageSprite;
          break;
        case '@':
          sprite = playerSprite;
          break;
        }
        if (_board[y][x] != '.') {
          sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
          target.draw(sprite, states);
        }
      }
    }
}

void Sokoban::movePlayer(Direction dir) {
    sf::Vector2u playerLoc = _playerLoc;
    sf::Vector2u nextLoc = playerLoc;
    switch (dir) {
    case Direction::Up:
      nextLoc.y--;
      playerSprite.setTexture(playerUp);
      break;
    case Direction::Down:
      nextLoc.y++;
      playerSprite.setTexture(playerDown);
      break;
    case Direction::Left:
      nextLoc.x--;
      playerSprite.setTexture(playerLeft);
      break;
    case Direction::Right:
      nextLoc.x++;
      playerSprite.setTexture(playerRight);
      break;
    }

    if (nextLoc.x >= _width || nextLoc.y >= _height) {
      return;
    }

    char &nextCell = _board[nextLoc.y][nextLoc.x];
    if (nextCell == '#') {
      return;
    }

    if (nextCell == 'A' || nextCell == '1') {
      sf::Vector2u boxLoc = nextLoc;
      switch (dir) {
      case Direction::Up:
        boxLoc.y--;
        break;
      case Direction::Down:
        boxLoc.y++;
        break;
      case Direction::Left:
        boxLoc.x--;
        break;
      case Direction::Right:
        boxLoc.x++;
        break;
      }
      if (boxLoc.x >= _width || boxLoc.y >= _height) {
        return;
      }
      char &boxNext = _board[boxLoc.y][boxLoc.x];
      if (boxNext == '#' || boxNext == 'A' || boxNext == '1') {
        return;
      }
      boxNext = (_initialBoard[boxLoc.y][boxLoc.x] == 'a') ? '1' : 'A';
      nextCell = (_initialBoard[nextLoc.y][nextLoc.x] == 'a') ? 'a' : '.';
    }
    char &playerCell = _board[playerLoc.y][playerLoc.x];
    playerCell = (_initialBoard[playerLoc.y][playerLoc.x] == 'a') ? 'a' : '.';
    _playerLoc = nextLoc;
    nextCell = '@';
}

bool Sokoban::isWon() const {
  // Count total storage spots
  int totalSpots = 0;
  for (const auto& row : _initialBoard) {
      totalSpots += std::count(row.begin(), row.end(), 'a');
  }

  // Count total boxes
  int totalBoxes = 0;
  for (const auto& row : _board) {
      totalBoxes += std::count_if(row.begin(), row.end(),
          [](char c) { return c == 'A' || c == '1'; });
  }

  // Count correctly stored boxes
  int boxesStored = 0;
  for (const auto& row : _board) {
      boxesStored += std::count(row.begin(), row.end(), '1');
  }

  // If there are no boxes or no spots, autowin
  if (totalBoxes == 0 || totalSpots == 0) {
      return true;
  }

  // Win condition depends on the relationship between boxes and spots
  if (totalBoxes <= totalSpots) {
      return boxesStored == totalBoxes;
  } else {
      return boxesStored == totalSpots;
  }
}

void Sokoban::reset() {
    _board = _initialBoard;
    _playerLoc = _initialPlayerLoc;
    playerSprite.setTexture(playerDown);
}

std::istream &operator>>(std::istream &in, Sokoban &s) {
    in >> s._height >> s._width;
    s._board.resize(s._height, std::vector<char>(s._width));
    s._initialBoard.resize(s._height, std::vector<char>(s._width));

    for (unsigned int i = 0; i < s._height; i++) {
      for (unsigned int j = 0; j < s._width; j++) {
        in >> s._board[i][j];
        if (s._board[i][j] == '@') {
          s._playerLoc = {j, i};
          s._initialPlayerLoc = {j, i};
        }

        s._initialBoard[i][j] = s._board[i][j];
      }
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const Sokoban &s) {
    out << s._height << " " << s._width << std::endl;
    for (unsigned int i = 0; i < s._height; i++) {
      for (unsigned int j = 0; j < s._width; j++) {
        out << s._board[i][j];
      }
      out << std::endl;
    }
    return out;
}

}  // namespace SB

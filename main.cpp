// Copyright 2025 <Mark Daoud>

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sokoban.hpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./Sokoban <level_file>" << std::endl;
        return 1;
    }

    std::ifstream levelFile(argv[1]);
    if (!levelFile) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    SB::Sokoban game;
    levelFile >> game;

    sf::RenderWindow window(sf::VideoMode(game.width() * game.TILE_SIZE,
                            game.height() * game.TILE_SIZE), "Sokoban");
    sf::Music winSound;

    if (!winSound.openFromFile("Trumpets.wav")) {
          std::cerr << "Failed to load win sound." << std::endl;
          return 1;
      }
    winSound.setLoop(true);

    bool won = false;
    bool soundPlaying = false;

    sf::Font font;
    if (!font.loadFromFile("Roboto.ttf")) {
        std::cerr << "Failed to load font." << std::endl;
        return 1;
    }
    sf::Text text("You won! Press R to restart.", font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width/2.0f,
                   textBounds.top + textBounds.height/2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (!won) {
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                        game.movePlayer(SB::Direction::Up);
                        break;
                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                        game.movePlayer(SB::Direction::Down);
                        break;
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                        game.movePlayer(SB::Direction::Left);
                        break;
                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                        game.movePlayer(SB::Direction::Right);
                        break;
                    case sf::Keyboard::R:
                        game.reset();
                        soundPlaying = false;
                        winSound.stop();
                        break;
                    default:
                        break;
                    }
                }
                if (won && event.key.code == sf::Keyboard::R) {
                    game.reset();
                    won = false;
                    soundPlaying = false;
                    winSound.stop();
                }
            }
        }
        window.clear();
        window.draw(game);

        if (game.isWon()) {
            won = true;
            window.draw(text);

            if (!soundPlaying) {
                winSound.play();
                soundPlaying = true;
            }
        }
        window.display();
    }

    levelFile.close();
    std::cout << game;

    return 0;
}

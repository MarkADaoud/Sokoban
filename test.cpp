// Copyright 2025 <Mark Daoud>
#define BOOST_TEST_MODULE SokobanTests
#include <sstream>
#include <boost/test/included/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

BOOST_AUTO_TEST_CASE(TestMovePlayer) {
  SB::Sokoban game;
  std::istringstream input(
      "5 5\n"
      "#####\n"
      "#.@.#\n"
      "#.A.#\n"
      "#.a.#\n"
      "#####\n");

    input >> game;
    sf::Vector2u initialPlayerLoc = game.playerLoc();
    game.movePlayer(SB::Direction::Right);
    // Check if player moved right
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPlayerLoc.x + 1);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initialPlayerLoc.y);
}

BOOST_AUTO_TEST_CASE(TestMovePlayerIntoWall) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@.#\n"
        "#.A.#\n"
        "#.a.#\n"
        "#####\n");

    input >> game;
    sf::Vector2u initialPlayerLoc = game.playerLoc();
    game.movePlayer(SB::Direction::Up);  // Attempt to move into a wall
    // Check if player location remains unchanged
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPlayerLoc.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initialPlayerLoc.y);
}

BOOST_AUTO_TEST_CASE(TestMoveBox) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@.#\n"
        "#.A.#\n"
        "#.a.#\n"
        "#####\n");

    input >> game;
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK(game.isWon());  // Check if the game is won after moving the box
}

BOOST_AUTO_TEST_CASE(TestBoxWall) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@A#\n"
        "#.#.#\n"
        "#..a#\n"
        "#####\n");

    input >> game;

    sf::Vector2u before = game.playerLoc();

    // Attempt to move the box , which should be blocked by a wall
    game.movePlayer(SB::Direction::Right);

    sf::Vector2u after = game.playerLoc();

    BOOST_CHECK_EQUAL(before.x, after.x);
    BOOST_CHECK_EQUAL(before.y, after.y);
}

BOOST_AUTO_TEST_CASE(TestBoxBox) {
    SB::Sokoban game;
    std::istringstream input(
        "6 5\n"
        "#####\n"
        "#.@.#\n"
        "#.A.#\n"
        "#.Aa#\n"
        "#...#\n"
        "#####\n");

    input >> game;
    sf::Vector2u before = game.playerLoc();
    // Attempt to move the box , which should be blocked by other box
    game.movePlayer(SB::Direction::Down);

    sf::Vector2u after = game.playerLoc();

    BOOST_CHECK_EQUAL(before.x, after.x);
    BOOST_CHECK_EQUAL(before.y, after.y);
}

BOOST_AUTO_TEST_CASE(TestOffScreen) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "##.##\n"
        "#.@.#\n"
        "#.A.#\n"
        "#aA.#\n"
        "#####\n");

    input >> game;

    sf::Vector2u before = game.playerLoc();

    // Attempt to move Right three times which should be blocked by wall
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);
    game.movePlayer(SB::Direction::Right);

    sf::Vector2u after = game.playerLoc();

    BOOST_CHECK_EQUAL(after.x, before.x + 1);
    BOOST_CHECK_EQUAL(before.y, after.y);

    game.reset();

    // Attempt to move off screen upwards
    game.movePlayer(SB::Direction::Up);
    game.movePlayer(SB::Direction::Up);

    BOOST_CHECK_EQUAL(before.x, game.playerLoc().x);
    BOOST_CHECK_EQUAL(before.y - 1, game.playerLoc().y);
}

BOOST_AUTO_TEST_CASE(TestLotsTargets) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@a#\n"
        "#aA.#\n"
        "#.aa#\n"
        "#####\n");

    input >> game;
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(TestLotsBoxes) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@A#\n"
        "#AA.#\n"
        "#.aA#\n"
        "#####\n");

    input >> game;
    game.movePlayer(SB::Direction::Down);
    BOOST_CHECK(game.isWon());
}

BOOST_AUTO_TEST_CASE(TestReset) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@.#\n"
        "#.A.#\n"
        "#.a.#\n"
        "#####\n");

    input >> game;
    sf::Vector2u initialPlayerLoc = game.playerLoc();
    game.movePlayer(SB::Direction::Right);

    game.reset();
    BOOST_CHECK_EQUAL(game.playerLoc().x, initialPlayerLoc.x);
    BOOST_CHECK_EQUAL(game.playerLoc().y, initialPlayerLoc.y);
}

BOOST_AUTO_TEST_CASE(TestMisreadSymbol) {
    SB::Sokoban game;
    std::istringstream input(
        "5 5\n"
        "#####\n"
        "#.@1#\n"
        "#.A.#\n"
        "#.a.#\n"
        "#####\n");

    input >> game;
    sf::Vector2u before = game.playerLoc();

    game.movePlayer(SB::Direction::Right);
    sf::Vector2u after = game.playerLoc();

    // Player should stay in place if '1' is correctly identified as a box in storage
    BOOST_CHECK_EQUAL(before.x, after.x);
    BOOST_CHECK_EQUAL(before.y, after.y);
}

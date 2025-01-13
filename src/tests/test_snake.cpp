#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "../brick_game/snake/controller.h"
#include "../brick_game/snake/model.h"
#include "../brick_game/snake/structure.h"

using namespace s21;

TEST(Snake, Start) {
  Model game{0};
  game.initializeGame();
  EXPECT_TRUE(game.gameInfo->level == 1);
  EXPECT_TRUE(game.gameInfo->score == 0);
  EXPECT_TRUE(game.gameInfo->field != NULL);
  EXPECT_TRUE(game.gameInfo->speed == 1000);
  EXPECT_TRUE(game.gameInfo->pause == 0);
}

TEST(Snake, initSnake) {
  Model game{0};
  game.initializeGame();
  game.initSnake();
  Snake_s *currSnake = game.getSnake();
  EXPECT_TRUE(game.gameInfo->field[8][3] == 1);
  EXPECT_TRUE(currSnake->dir == DOWN);
}

TEST(Snake, changeDir) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  Snake_s *currSnake = game.getSnake();
  game.changeDir(Left, currSnake);
  game.chooseDir(currSnake);
  EXPECT_TRUE(currSnake->dir == LEFT);
  game.putSnake(currSnake);
  EXPECT_TRUE(game.gameInfo->field[8][2] == 1);
}

TEST(Snake, loseGame) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  Snake_s *currSnake = game.getSnake();
  game.changeDir(Left, currSnake);
  game.chooseDir(currSnake);
  EXPECT_TRUE(currSnake->dir == LEFT);
  game.putSnake(currSnake);
  game.changeDir(Left, currSnake);
  game.chooseDir(currSnake);
  game.putSnake(currSnake);
  game.changeDir(Left, currSnake);
  game.chooseDir(currSnake);
  game.putSnake(currSnake);
  EXPECT_TRUE(gs == 1);
}

TEST(Snake, getApple) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  Snake_s *currSnake = game.getSnake();
  game.getApple(currSnake);
  bool isApple = false;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game.gameInfo->field[i][j] == 100) {
        isApple = true;
        break;
      }
    }
  }
  EXPECT_TRUE(isApple == true);
}

TEST(Snake, Snake_clean) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  game.cleanField();
  bool isFull = false;
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (game.gameInfo->field[i][j] == 1) {
        isFull = true;
        break;
      }
    }
  }
  EXPECT_TRUE(isFull == false);
}

TEST(Snake, eatApple) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  Snake_s *currSnake = game.getSnake();
  game.gameInfo->field[9][3] = 100;
  game.changeDir(Down, currSnake);
  game.chooseDir(currSnake);
  game.putSnake(currSnake);
  EXPECT_TRUE(currSnake->v.size() == 5);
}

TEST(Snake, winGame) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  Snake_s *currSnake = game.getSnake();
  game.gameInfo->level = 9;
  game.gameInfo->score = 49;
  game.gameInfo->field[9][3] = 100;
  game.changeDir(Down, currSnake);
  game.chooseDir(currSnake);
  game.putSnake(currSnake);
  EXPECT_TRUE(game.gameInfo->score == 50);
  EXPECT_TRUE(game.gameInfo->level == 10);
  EXPECT_TRUE(gs == 2);
}

TEST(Snake, readMaxscore) {
  GameStatus gs{};
  gs = normal;
  Model game{&gs};
  game.initializeGame();
  game.initSnake();
  int MC = game.readMaxScore();
  int maxScore{};
  std::ifstream in("max_score_snake.txt");
  if (in.is_open()) {
    in >> maxScore;
  }
  in.close();
  EXPECT_TRUE(MC == maxScore);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

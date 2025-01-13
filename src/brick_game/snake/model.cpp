#include "model.h"

#include <sys/time.h>

#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>

#include "../common_structure.h"
#include "structure.h"

using namespace s21;

void Model::initializeGame() {
  gameInfo = new (GameInfo_t);
  gameInfo->field = new int *[FIELD_HEIGHT];

  for (int rowIndex = 0; rowIndex < FIELD_HEIGHT; ++rowIndex) {
    gameInfo->field[rowIndex] = new int[FIELD_WIDTH]();
  }

  max_score = readMaxScore();
  gameInfo->high_score = max_score;
  gameInfo->score = 0;
  gameInfo->level = 1;
  gameInfo->pause = 0;
  gameInfo->speed = 1000;
}

void Model::initSnake() {
  currSnake.y = 3;
  currSnake.v.push_front({currSnake.y, 5});
  currSnake.v.push_front({currSnake.y, 6});
  currSnake.v.push_front({currSnake.y, 7});
  currSnake.v.push_front({currSnake.y, 8});
  Snake_s snake_f = {currSnake.v, 8, currSnake.y, DOWN};
  putFirstSnake(snake_f);
  getApple(&snake_f);
  currSnake = snake_f;
}

void Model::putFirstSnake(Snake_s snake) {
  int fx = snake.y, fy = snake.x;
  if ((fx > 0 && fx < FIELD_WIDTH) && (fy > 0 && fy < FIELD_HEIGHT)) {
    for (unsigned long i = 0; i < snake.v.size(); i++) {
      if (snake.v[i].first && snake.v[i].second) {
        gameInfo->field[snake.v[i].second][snake.v[i].first] = 1;
      }
    }
  }
}

void Model::chooseDir(Snake_s *snake) {
  int fx = snake->y, fy = snake->x;
  if (snake->dir == RIGHT)
    fx = fx + 1;
  else if (snake->dir == LEFT)
    fx = fx - 1;
  else if (snake->dir == UP)
    fy = fy - 1;
  else if (snake->dir == DOWN)
    fy = fy + 1;
  snake->y = fx;
  snake->x = fy;
}

void Model::changeDir(UserAction_t action, Snake_s *snake) {
  if (snake->dir == LEFT || snake->dir == RIGHT) {
    if (action == Up)
      snake->dir = UP;
    else if (action == Down)
      snake->dir = DOWN;
  } else if (snake->dir == DOWN || snake->dir == UP) {
    if (action == Left)
      snake->dir = LEFT;
    else if (action == Right)
      snake->dir = RIGHT;
  }
}

void Model::putSnake(Snake_s *snake) {
  if (*gs != GameStatus::lose) *gs = GameStatus::normal;
  cleanField();
  int fx = snake->y, fy = snake->x;
  if (((fx > 0 && fx < FIELD_WIDTH) && (fy > 0 && fy < FIELD_HEIGHT))) {
    for (unsigned long i = 0; i < snake->v.size(); i++) {
      if (snake->v[i].first == fx && snake->v[i].second == fy) {
        *gs = GameStatus::lose;
        break;
      }
    }
    if (*gs == GameStatus::normal) {
      if (gameInfo->field[fy][fx] == appleField) {
        eatApple(snake);
        if (snake->v.size() == snakeWinSize) *gs = GameStatus::win;
      } else {
        snake->v.pop_back();
        snake->v.push_front({fx, fy});
      }
      for (unsigned long i = 0; i < snake->v.size(); i++) {
        if (snake->v[i].first && snake->v[i].second) {
          gameInfo->field[snake->v[i].second][snake->v[i].first] = 1;
        }
      }
    }
  } else {
    *gs = GameStatus::lose;
  }
}

void Model::eatApple(Snake_s *snake) {
  int fx = snake->y, fy = snake->x;
  gameInfo->field[fy][fx] = 0;
  snake->v.push_front({fx, fy});
  gameInfo->score++;
  if ((gameInfo->score) % 5 == 0) {
    gameInfo->level++;
    gameInfo->speed = gameInfo->speed - 80;
  }
  if (snake->v.size() == 200 || gameInfo->level == 10)
    *gs = GameStatus::win;
  else {
    getApple(snake);
  }
}

void Model::getApple(Snake_s *snake) {
  int appleX{};
  int appleY{};
  bool body_snake = true;
  do {
    appleY = 2 + arc4random() % (FIELD_HEIGHT - 2);
    appleX = 2 + arc4random() % (FIELD_WIDTH - 2);
    for (unsigned long i = 0; i < currSnake.v.size(); i++) {
      if (snake->v[i].first == appleX && snake->v[i].second == appleY) {
        body_snake = true;
        break;
      }
      body_snake = false;
    }
  } while (body_snake == true || gameInfo->field[appleY][appleX]);
  gameInfo->field[appleY][appleX] = 100;
}

int Model::readMaxScore() {
  int maxScore = 0;
  std::ifstream in("max_score_snake.txt");
  if (in.is_open()) {
    in >> maxScore;
  }
  in.close();
  return maxScore;
}

void Model::rewriteHighScore() {
  std::ofstream out;
  out.open("max_score_snake.txt");
  int maxScore = gameInfo->high_score;
  maxScore = gameInfo->score > max_score ? gameInfo->score : max_score;
  if (out.is_open()) {
    out << maxScore << std::endl;
  }
  out.close();
}

void Model::cleanField() {
  if (gameInfo->field != nullptr)
    for (int i = 1; i < FIELD_HEIGHT; i++) {
      for (int j = 1; j < FIELD_WIDTH; j++) {
        if (gameInfo->field[i][j] == 1) {
          gameInfo->field[i][j] = 0;
        }
      }
    }
}

void Model::terminate() {
  if (gameInfo->field != nullptr) {
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
      delete[] (gameInfo->field[i]);
    }
    delete[] (gameInfo->field);
    gameInfo->field = nullptr;
  }
}

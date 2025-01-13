#include "controller.h"

#include <sys/time.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../common_structure.h"
#include "structure.h"

using namespace s21;

Controller::Controller() {
  model = new Model(&gameStatus);
  model->initializeGame();
  model->initSnake();

  hold = false;
  action = Down;

  isDoExit = false;
}

int Controller::getMaxScore() { return model->getMaxScore(); }

int Controller::getSpeed() { return model->getSpeed(); }

bool Controller::holdKey() { return hold; }

bool Controller::getInfoPause() { return model->getGameInfo()->pause; }

UserAction_t Controller::getAction() { return action; }

bool Controller::isExit() { return isDoExit; }

GameInfo_t Controller::updateCurrentState() {
  if (isDoExit == false) {
    if (getAction() == Terminate) {
      isDoExit = true;
    } else if (model->getGameInfo()->pause == 0) {
      model->chooseDir(model->getSnake());
      model->putSnake(model->getSnake());
      if (gameStatus == GameStatus::lose || gameStatus == GameStatus::win ||
          model->getGameInfo()->level == 10) {
        model->rewriteHighScore();
      }
    }
  }
  return *model->getGameInfo();
}

void Controller::userInput(UserAction_t action, bool hold) {
  if (!hold) {
    Snake_s *currSnake = model->getSnake();
    action = this->action;
    switch (action) {
      case Start:
        model->getGameInfo()->pause = 0;
        break;
      case Pause:
        if (model->getGameInfo()->pause == 0) {
          model->getGameInfo()->pause = 1;
        } else if (model->getGameInfo()->pause == 1) {
          model->getGameInfo()->pause = 0;
        }
        break;
      case Terminate:
        model->rewriteHighScore();
        isDoExit = true;
        model->terminate();
        break;
      case Left:
        if (model->getGameInfo()->pause == 1) {
          break;
        }
        model->changeDir(Left, currSnake);
        break;
      case Right:
        if (model->getGameInfo()->pause == 1) {
          break;
        }
        model->changeDir(Right, currSnake);
        break;
      case Down:
        if (model->getGameInfo()->pause == 1) {
          break;
        }
        model->changeDir(Down, currSnake);
        break;
      case Up:
        if (model->getGameInfo()->pause == 1) {
          break;
        }
        model->changeDir(Up, currSnake);
        break;
      case Action:
        break;
      case NoAction:
        break;
    }
    setAction(NoAction);
  }
}

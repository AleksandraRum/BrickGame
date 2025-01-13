#include <thread>

#include "../../brick_game/snake/controller.h"
extern "C" {
#include "frontend.h"
}

using namespace s21;

class ProcessGame {
 public:
  ProcessGame() {
    printBoxes();
    controller = new Controller;
    maxScore = controller->getMaxScore();
    int keyStart{};
    do keyStart = getch();
    while (keyStart != ENTER);
    while (controller->isExit() == false) {
      int speed_timer{};
      if (controller->holdKey() == true) flushinp();
      int key = getch();
      int keyBuf = getch();
      if (key == keyBuf && key != -1 && key != 32)
        controller->setHold(true);
      else if (key == 32)
        controller->setHold(false);
      else if ((key != keyBuf || key == -1) && key != 32)
        controller->setHold(false);
      parsKeys(key);
      if (controller->holdKey() == true) {
        speed_timer = 100;
      } else
        speed_timer = controller->getSpeed();
      updateCurrentState();
      std::chrono::milliseconds timespan(speed_timer);
      std::this_thread::sleep_for(timespan);
    }
  }
  ~ProcessGame() { delete controller; }

  void updateCurrentState() {
    GameInfo_t gInfo = controller->updateCurrentState();
    if (controller->getCurrGameStatus() == GameStatus::normal &&
        controller->isExit() == false) {
      printField(gInfo);
    } else if (controller->getCurrGameStatus() == GameStatus::win) {
      printWinField();
    } else if (controller->getCurrGameStatus() == GameStatus::lose) {
      printLoseField();
    }
    if (gInfo.score > maxScore)
      gInfo.high_score = gInfo.score;
    else
      gInfo.high_score = maxScore;
    printAddField(gInfo);
    if (controller->isExit()) {
      cleanWindows();
    }
  }

  void parsKeys(int key) {
    if ((controller->getAction() == Pause && key != -1) ||
        controller->getAction() != Pause) {
      switch (key) {
        case ESC:
          controller->setAction(Terminate);
          break;
        case KEY_RIGHT:
          controller->setAction(Right);
          break;
        case KEY_LEFT:
          controller->setAction(Left);
          break;
        case KEY_UP:
          controller->setAction(Up);
          break;
        case KEY_DOWN:
          controller->setAction(Down);
          break;
        case ' ':
          controller->setAction(Pause);
          break;
      }
      controller->userInput();
    }
  }

 private:
  Controller *controller{};
  int maxScore{};
};

int main() {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  halfdelay(1);
  curs_set(0);
  srand(time(0));
  ProcessGame pg;
  endwin();
  return 0;
}

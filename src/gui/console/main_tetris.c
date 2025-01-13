#include "../../brick_game/tetris/backend.h"
#include "../../brick_game/tetris/controller.h"
#include "frontend.h"

void whatPrint(GameStatus gs, GameInfo_t *game) {
  if (gs == 0) {
    printField(*game);
  } else if (gs == 1) {
    printLoseField();
  } else if (gs == 2) {
    printWinField();
  }
  printAddField(*game);
  printNext(*game);
}

void parsKey(int key, UserAction_t action, bool hold, GameInfo_t *game,
             Figure_t current_figure) {
  switch (key) {
    case ESC:
      action = Terminate;
      userInput(action, hold, game, current_figure);
      break;
    case ' ':
      action = Pause;
      userInput(action, hold, game, current_figure);
      break;
    case KEY_LEFT:
      action = Left;
      userInput(action, hold, game, current_figure);
      break;
    case KEY_RIGHT:
      action = Right;
      userInput(action, hold, game, current_figure);
      break;
    case KEY_DOWN:
      action = Down;
      userInput(action, hold, game, current_figure);
      break;
    case KEY_UP:
      action = Action;
      userInput(action, hold, game, current_figure);
      break;
  }
}

void winLoseSituation(GameInfo_t *game, GameStatus gs, Figure_t current_figure,
                      Figure_t next_figure) {
  int key = 0;
  rewrite_high_score(game);
  whatPrint(gs, game);
  updateCurrentInfo(game);
  do {
    key = getch();
  } while (key != ESC);
  free_matrix(next_figure.figure, 4);
  free_matrix(current_figure.figure, 4);
  terminate(game);
  cleanWindows();
}

void main_loop(GameInfo_t *game) {
  Figure_t current_figure = create_figure(X_FIGURE, Y_FIGURE);
  Figure_t next_figure = create_figure(X_FIGURE, Y_FIGURE);
  copy_matrix(&next_figure, game);
  drop_new_figure(current_figure, game);
  updateCurrentInfo(game);
  int start = clock();
  bool hold = false;
  int key = 0;
  UserAction_t action = Up;
  GameStatus gs = normal;
  do {
    key = getch();
  } while (key != ENTER);
  while (1) {
    if (game->level >= 10) {
      gs = win;
      winLoseSituation(game, gs, current_figure, next_figure);
      break;
    } else if (losing_position(game)) {
      gs = lose;
      winLoseSituation(game, gs, current_figure, next_figure);
      break;
    }
    if (check_figures_on_field(game)) {
      int current_t = clock();
      if (current_t - start >= game->speed && game->pause != 1 &&
          action != Start) {
        move_down_figure(game);
        current_figure.y++;
        start = current_t;
      } else if (game->pause == 1 || action == Start) {
        start = clock();
      }
      key = getch();
      parsKey(key, action, hold, game, current_figure);
      if (key == ESC) {
        free_matrix(next_figure.figure, 4);
        free_matrix(current_figure.figure, 4);
        cleanWindows();
        break;
      } else {
        whatPrint(gs, game);
        updateCurrentInfo(game);
      }
    } else {
      free_matrix(current_figure.figure, 4);
      current_figure = next_figure;
      next_figure = create_figure(X_FIGURE, Y_FIGURE);
      copy_matrix(&next_figure, game);
      drop_new_figure(current_figure, game);
    }
  }
}

int main(void) {
  initscr();
  keypad(stdscr, TRUE);
  noecho();
  halfdelay(1);
  curs_set(0);
  srand(time(0));
  GameInfo_t *game = initializeGame();
  printBoxes();
  printAddField(*game);
  main_loop(game);
  endwin();
  return 0;
}

#include "frontend.h"

void printField(GameInfo_t gameInfo) {
  for (int i = 1; i < FIELD_HEIGHT; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      if (gameInfo.field[i][j] && gameInfo.field[i][j] != 100) {
        mvwprintw(game_field, i, 2 * j - 1, "[");
        mvwprintw(game_field, i, 2 * j, "]");
      } else if (gameInfo.field[i][j] == 100) {
        mvwprintw(game_field, i, 2 * j - 1, "{");
        mvwprintw(game_field, i, 2 * j, "}");
      } else {
        mvwprintw(game_field, i, 2 * j - 1, " ");
        mvwprintw(game_field, i, 2 * j, " ");
      }
    }
  }
  wrefresh(game_field);
}

void printNext(GameInfo_t gameInfo) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gameInfo.next[i][j]) {
        mvwprintw(next_field, i + 2, 2 * j + 3, "[");
        mvwprintw(next_field, i + 2, 2 * j + 4, "]");
      } else {
        mvwprintw(next_field, i + 2, 2 * j + 3, " ");
        mvwprintw(next_field, i + 2, 2 * j + 4, " ");
      }
    }
  }
  wrefresh(next_field);
}

void printBoxes(void) {
  background = newwin(BACK_HEIGHT, BACK_WIDTH, Y_BACK, X_BACK);
  game_field = subwin(background, FIELD_HEIGHT + 1, FRONT_WIDTH + 1,
                      Y_GAME_FIELD, X_GAME_FIELD);
  score_field = subwin(background, ADD_FIELD_WIDTH, ADD_FIELD_HEIGHT,
                       Y_GAME_FIELD, X_ADD_FIELD);
  level_field = subwin(background, ADD_FIELD_WIDTH, ADD_FIELD_HEIGHT,
                       Y_GAME_FIELD + 5, X_ADD_FIELD);
  speed_field = subwin(background, ADD_FIELD_WIDTH, ADD_FIELD_HEIGHT,
                       Y_GAME_FIELD + 10, X_ADD_FIELD);
  next_field = subwin(background, ADD_FIELD_WIDTH + 2, ADD_FIELD_HEIGHT,
                      Y_GAME_FIELD + 15, X_ADD_FIELD);
  refresh();
  box(background, 0, 0);
  box(game_field, 0, 0);
  box(score_field, 0, 0);
  box(level_field, 0, 0);
  box(speed_field, 0, 0);
  box(next_field, 0, 0);
  mvwprintw(background, 2, X_GAME_FIELD + 8, "SCORE");
  mvwprintw(background, 7, X_GAME_FIELD + 8, "LEVEL");
  mvwprintw(background, 12, X_GAME_FIELD + 6, "HIGH_SCORE");
  mvwprintw(background, 17, X_GAME_FIELD + 9, "NEXT");
  wrefresh(background);
  wrefresh(game_field);
  wrefresh(score_field);
  wrefresh(level_field);
  wrefresh(speed_field);
  wrefresh(next_field);
}

void cleanWindows(void) {
  wclear(game_field);
  delwin(game_field);
  wclear(next_field);
  delwin(next_field);
  wclear(score_field);
  delwin(score_field);
  wclear(speed_field);
  delwin(speed_field);
  wclear(level_field);
  delwin(level_field);
  wclear(background);
  delwin(background);
}

void printAddField(GameInfo_t gameInfo) {
  mvwprintw(score_field, 2, 5, "%3d", gameInfo.score);
  mvwprintw(level_field, 2, 7, "%d", gameInfo.level);
  mvwprintw(speed_field, 2, 5, "%3d", gameInfo.high_score);
  wrefresh(score_field);
  wrefresh(level_field);
  wrefresh(speed_field);
}

void printWinField(void) {
  wclear(game_field);
  delwin(game_field);
  game_field = subwin(background, FIELD_HEIGHT + 1, FRONT_WIDTH + 1,
                      Y_GAME_FIELD, X_GAME_FIELD);
  refresh();
  box(game_field, 0, 0);
  mvwprintw(background, 8, 7, "YOU WON!");
  wrefresh(game_field);
  wrefresh(background);
}

void printLoseField(void) {
  wclear(game_field);
  delwin(game_field);
  game_field = subwin(background, FIELD_HEIGHT + 1, FRONT_WIDTH + 1,
                      Y_GAME_FIELD, X_GAME_FIELD);
  refresh();
  box(game_field, 0, 0);
  mvwprintw(background, 8, 7, "YOU LOST!");
  wrefresh(game_field);
  wrefresh(background);
}

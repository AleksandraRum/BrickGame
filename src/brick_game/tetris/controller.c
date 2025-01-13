#include "controller.h"

GameInfo_t updateCurrentInfo(GameInfo_t *game) {
  game->score += remove_lines(game);
  game->high_score = game->score > max_score ? game->score : max_score;
  game->level = level_counter(game);
  return *game;
}

void userInput(UserAction_t action, bool hold, GameInfo_t *game,
               Figure_t current_figure) {
  if (!hold) {
    switch (action) {
      case Start:
        break;
      case Pause:
        game->pause = 1 - game->pause;
        break;
      case Terminate:
        rewrite_high_score(game);
        terminate(game);
        break;
      case Left:
        if (game->pause == 1) {
          break;
        }
        move_left_figure(game);
        current_figure.x--;
        break;
      case Right:
        if (game->pause == 1) {
          break;
        }
        move_right_figure(game);
        current_figure.x++;
        break;
      case Down:
        if (game->pause == 1) {
          break;
        }
        move_down_figure(game);
        current_figure.y++;
        break;
      case Action:
        if (game->pause == 1) {
          break;
        }
        rotate_figure(&current_figure, game);
        break;
      case Up:
        break;
      case NoAction:
        break;
    }
  }
}

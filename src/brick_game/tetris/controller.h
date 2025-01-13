#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "./backend.h"

GameInfo_t updateCurrentInfo(GameInfo_t *game);
void userInput(UserAction_t action, bool hold, GameInfo_t *game,
               Figure_t current_figure);

#endif  // CONTROLLER_H

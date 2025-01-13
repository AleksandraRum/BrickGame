/**
 * @file frontend.h
 * @brief Заголовочный файл фронтэнда для консоли
 */
#ifndef FRONTEND_H
#define FRONTEND_H

#include <curses.h>

#include "../../brick_game/common_structure.h"

static WINDOW *background, *game_field, *level_field, *speed_field, *next_field,
    *score_field;

/**
 * @brief Отрисовывает ситуацию на поле
 */
void printField(GameInfo_t gameInfo);

/**
 * @brief Отрисовка коробки и написей экране
 */
void printBoxes(void);

/**
 * @brief Полная очистка окон
 */
void cleanWindows(void);
/**
 * @brief Отрисовка поля Next
 */
void printNext(GameInfo_t gameInfo);

/**
 * @brief Отображение дополнительных полей
 * \param gameInfo
 */
void printAddField(GameInfo_t gameInfo);

/**
 * @brief Отображение сообщения о выигрыше
 */
void printWinField(void);
/**
 * @brief Отображение сообщения о прогрыше
 */
void printLoseField(void);

#endif  // FRONTEND_H

/**
 * @file common_structure.h
 * @brief Файл общих структур и дефайнов игры для змейки и тетриса
 */
#ifndef COMMON_STRUCTURE_H
#define COMMON_STRUCTURE_H
/**
 * @brief Основные параметры поля
 */
#define FRONT_WIDTH 21
#define FIELD_WIDTH 11
#define FIELD_HEIGHT 21
#define BACK_HEIGHT FIELD_HEIGHT + 3
#define BACK_WIDTH FRONT_WIDTH + 21
#define Y_BACK (LINES - FIELD_HEIGHT - 2) / 2
#define X_BACK (COLS - FRONT_WIDTH - 22) / 2
#define Y_GAME_FIELD (LINES - FIELD_HEIGHT) / 2
#define X_GAME_FIELD X_BACK + 2
#define ADD_FIELD_WIDTH 5
#define ADD_FIELD_HEIGHT 15
#define X_ADD_FIELD (COLS - FRONT_WIDTH) / 2 + 13
#define Y_FIGURE 1
#define X_FIGURE 4
#define ESC 27
#define ENTER 10
/**
 * @brief Структура для всей игры
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;
/**
 * @brief Структура для действий игрока
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NoAction
} UserAction_t;
/**
 * @brief Структура для фигуры
 */
typedef struct {
  int **figure;
  int x;
  int y;
} Figure_t;
/**
 * @brief Перечисление для статуса игры
 */
typedef enum { normal = 0, lose = 1, win = 2 } GameStatus;

extern int max_score;

#endif  // COMMON_STRUCTURE_H

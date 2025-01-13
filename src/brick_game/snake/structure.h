/**
 * @file structure.h
 * @brief Файл структуры игры для змейки
 */
#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <deque>

/**
 * @brief Перечисление направлений змейки
 */
typedef enum { UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4 } direction_t;
using namespace std;
/**
 * @brief Структура тела змеи
 */
typedef struct {
  deque<pair<int, int> > v;
  int x;
  int y;
  direction_t dir;
} Snake_s;

#endif

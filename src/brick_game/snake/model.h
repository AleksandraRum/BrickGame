/**
 * @file model.h
 * @brief Заголовочный файл для класса Model
 */
#ifndef MODEL_H
#define MODEL_H

#include "../common_structure.h"
#include "structure.h"

namespace s21 {
/**
 * @brief класс Модели
 */
class Model {
 public:
  /**
   * @brief Конструктор
   */
  Model(GameStatus *gs) : gs(gs) {};
  /**
   * @brief Деструктор
   */
  ~Model() = default;

  GameInfo_t *gameInfo{};
  GameStatus *gs{};
  Snake_s currSnake;

  /**
   * @brief initializeGame - инициализация параметров игры
   */
  void initializeGame();
  /**
   * @brief Инициализация Змейки
   */
  void initSnake();
  /**
   * @brief Вывод первой змеи
   */
  void putFirstSnake(Snake_s snake);
  /**
   * @brief Выбор направления змеи
   */
  void chooseDir(Snake_s *snake);
  /**
   * @brief Изменить ход направления змейки
   */
  void changeDir(UserAction_t action, Snake_s *snake);
  /**
   * @brief Вывод змеи
   */
  void putSnake(Snake_s *snake);
  /**
   * @brief Съесть яблоко
   */
  void eatApple(Snake_s *snake);
  /**
   * @brief Добавить новое яблоко
   */
  void getApple(Snake_s *snake);
  /**
   * @brief Считать максимальные очки
   */
  int readMaxScore();
  /**
   * @brief Перезаписать максимальные очки
   */
  void rewriteHighScore();
  /**
   * @brief Очистить поле
   */
  void cleanField();
  /**
   * @brief Выход
   */
  void terminate();
  /**
   * @brief Вернуть текущую структуру змеи
   */
  Snake_s *getSnake() { return &currSnake; }
  /**
   * @brief Вернуть актуальную информацию об игре
   */
  GameInfo_t *getGameInfo() { return gameInfo; }
  /**
   * @brief Вернуть максимальный счет
   */
  int getMaxScore() { return max_score; }
  /**
   * @brief Вернуть текущую скорость
   */
  int getSpeed() { return gameInfo->speed; }

 private:
  int max_score{};
  const short appleField = 100;
  unsigned long snakeWinSize = 200;
};

}  // namespace s21
#endif

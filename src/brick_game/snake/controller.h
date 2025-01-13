/**
 * @file controller.h
 * @brief Заголовочный файл для класса Controller
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {
/**
 * @brief класс Контроллера
 */
class Controller {
 public:
  /**
   * @brief Конструктор
   */
  Controller(/*Model *m*/) /*: model(m)*/;
  /**
   * @brief Деструктор
   */
  ~Controller() = default;
  /**
   * @brief Получение данных о максимальном счете
   */
  int getMaxScore();
  /**
   * @brief Флаг выхода
   */
  bool isExit();
  /**
   * @brief Изменение состояния игры
   */
  GameInfo_t updateCurrentState();
  /**
   * @brief Получение данных о текущей скорости
   */
  int getSpeed();
  /**
   * @brief Флаг зажатой кнопки
   */
  bool holdKey();
  /**
   * @brief Информация о паузе
   */
  bool getInfoPause();
  /**
   * @brief Информация о действии пользователя
   */
  UserAction_t getAction();

  /**
   * @brief Действие пользователя
   */
  void userInput(UserAction_t action = UserAction_t(), bool hold = false);
  /**
   * @brief Текущее состояние игры
   */
  GameStatus getCurrGameStatus() { return gameStatus; }
  /**
   * @brief Текущий статус игры
   */
  void setCurrGameStatus(GameStatus gs) { gameStatus = gs; }
  /**
   * @brief Установить действие пользователя
   */
  void setAction(UserAction_t act) { action = act; }
  /**
   * @brief Изменить состояние кнопки hold
   */
  void setHold(bool h) { hold = h; }

 private:
  Model *model{};
  bool hold{};
  UserAction_t action{};
  GameStatus gameStatus{};
  bool isDoExit{};
};

}  // namespace s21
#endif

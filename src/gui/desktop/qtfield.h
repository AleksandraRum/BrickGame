/**
 * @file qtfield.h
 * @brief Фронтэнд для десктопа
 */
#ifndef QTFIELD_H
#define QTFIELD_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QMainWindow>

#include "../../brick_game/snake/controller.h"

/**
 * @brief Печать коробки
 */
void printBox(QGraphicsScene *scene);
/**
 * @brief Печать полей с доплнительной информацией
 */
void printAddField(GameInfo_t gameInfo, QGraphicsScene *scene);
/**
 * @brief Печать основного поля
 */
void printField(GameInfo_t field, QGraphicsScene *scene);
/**
 * @brief Очистка поля
 */
void cleanField(QGraphicsScene *scene);
/**
 * @brief Печать поля Next
 */
void printNextField(GameInfo_t gameInfo, QGraphicsScene *scene);
/**
 * @brief Тело змеи
 */
static QVector<QGraphicsItem *> snakeVector;
/**
 * @brief избражение яблока
 */
static QGraphicsItem *itemApple{};
/**
 * @brief отображение текстовых полей для доп информации
 */
static QGraphicsItem *itemText1{};
static QGraphicsItem *itemText2{};
static QGraphicsItem *itemText3{};
/**
 * @brief Хранение информации о фигурках и заполненных полях тетриса
 */
static QVector<QGraphicsItem *> tetrVector;
static QVector<QGraphicsItem *> fieldVector;
static QGraphicsItem *itemTetr1{};
static QGraphicsItem *item{};
/**
 * @brief Хранение информации о следующей фигуре
 */
static QGraphicsItem *itemNext{};
static QVector<QGraphicsItem *> nextVector;

#endif  // QTFIELD_H

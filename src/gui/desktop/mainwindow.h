/**
 * @file mainwindow.h
 * @brief Запуск змейки для десктопа
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QMainWindow>

#include "../../brick_game/snake/controller.h"

using namespace s21;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/**
 * @brief класс главного окна
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  /**
   * @brief перегрузка keyPressEvent для вызова при нажатии на клавиатуру
   */
  void keyPressEvent(QKeyEvent *event) override;
  /**
   * @brief перегрузка keyPressEvent для вызова при отпускании клавиши
   */
  void keyReleaseEvent(QKeyEvent *event) override;

 private:
  Ui::MainWindow *ui;
  QGraphicsWidget *widget{};
  QGraphicsScene *scene{};
  Controller *controller{};
  int maxScore{};
  bool isStart = false;
  /**
   * @brief Отображение текущего состояния игры
   */
  void updateCurrentState();
  QTimer *timer{};

 private slots:
  void eventLoop();

 signals:
  void enterPressed();
};
#endif  // MAINWINDOW_H

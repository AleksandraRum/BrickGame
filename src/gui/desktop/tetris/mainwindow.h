#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QMainWindow>

extern "C" {
#include "../../../brick_game/common_structure.h"
#include "../../../brick_game/tetris/controller.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void keyPressEvent(QKeyEvent *event) override;

  void keyReleaseEvent(QKeyEvent *event) override;

 private:
  Ui::MainWindow *ui;
  QGraphicsWidget *widget{};
  QGraphicsScene *scene{};

  GameInfo_t *game{};
  Figure_t current_figure{};
  Figure_t next_figure{};
  QTimer *timer{};
  bool isStart = false;
  GameStatus gs{};

  void printCurrentState();
  GameInfo_t updateCurrentState();

 private slots:
  void eventLoop();

 signals:
  void enterPressed();
};
#endif  // MAINWINDOW_H

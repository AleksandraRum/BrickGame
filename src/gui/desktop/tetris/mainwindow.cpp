#include "mainwindow.h"

#include <QDebug>
#include <QTimer>

#include "../qtfield.h"
#include "../ui_mainwindow.h"

extern "C" {
#include "../../../brick_game/tetris/backend.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFocusPolicy(Qt::StrongFocus);
  ui->graphicsView->setFocusPolicy(Qt::NoFocus);
  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  printBox(scene);
  game = initializeGame();
  UserAction_t action = Up;
  gs = normal;
  timer = new QTimer(this);
  connect(this, &MainWindow::enterPressed, this, &MainWindow::eventLoop);
  connect(timer, &QTimer::timeout, this, &MainWindow::eventLoop);
  timer->start(game->speed / 2);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Return:
      isStart = true;
      break;
    case Qt::Key_Down:
      userInput(Down, true, game, current_figure);
      if (timer->interval() != game->speed / 10) {
        timer->stop();
        timer->start(game->speed / 10);
      }
      break;
    case Qt::Key_Up:
      userInput(Action, false, game, current_figure);
      break;
    case Qt::Key_Left:
      userInput(Left, false, game, current_figure);
      break;
    case Qt::Key_Right:
      userInput(Right, false, game, current_figure);
      break;
    case Qt::Key_Space:
      userInput(Pause, false, game, current_figure);
      break;
    case Qt::Key_Escape:
      userInput(Terminate, false, game, current_figure);
      close();
      break;
    default:
      break;
  }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Return:
      isStart = true;
      break;
    case Qt::Key_Down:
      userInput(NoAction, false, game, current_figure);
      if (timer->interval() != game->speed / 2) {
        timer->stop();
        timer->start(game->speed / 2);
      }
      break;
    case Qt::Key_Up:
      userInput(NoAction, false, game, current_figure);
      break;
    case Qt::Key_Left:
      userInput(NoAction, false, game, current_figure);
      break;
    case Qt::Key_Right:
      userInput(NoAction, false, game, current_figure);
      break;
    case Qt::Key_Space:
      userInput(NoAction, false, game, current_figure);
      break;
    case Qt::Key_Escape:
      userInput(NoAction, false, game, current_figure);
      break;
    default:
      break;
  }
}

GameInfo_t MainWindow::updateCurrentState() {
  if (game->pause == 0) {
    if (check_figures_on_field(game)) {
      move_down_figure(game);
      current_figure.y++;
    } else {
      if (current_figure.figure != NULL) {
        free_matrix(current_figure.figure, 4);
        current_figure = next_figure;
      } else
        current_figure = create_figure(X_FIGURE, Y_FIGURE);
      next_figure = create_figure(X_FIGURE, Y_FIGURE);
      copy_matrix(&next_figure, game);
      drop_new_figure(current_figure, game);
    }
    updateCurrentInfo(game);
    if (losing_position(game))
      gs = lose;
    else if (game->level >= 10)
      gs = win;
  }
  return *game;
}

void MainWindow::printCurrentState() {
  *game = updateCurrentState();
  if (gs == lose || gs == win) {
    rewrite_high_score(game);
  }
  if (gs == normal) {
    printField(*game, scene);
  } else if (gs != normal) {
    cleanField(scene);
    if (gs == lose)
      scene->addText("YOU LOST!")->setPos(180, 200);
    else if (gs == win)
      scene->addText("YOU WON!")->setPos(180, 200);
  }
  printAddField(*game, scene);
  printNextField(*game, scene);
}

void MainWindow::eventLoop() {
  if (isStart) printCurrentState();
}

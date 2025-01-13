#include "mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QTimer>

#include "./ui_mainwindow.h"
#include "qtfield.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFocusPolicy(Qt::StrongFocus);
  ui->graphicsView->setFocusPolicy(Qt::NoFocus);

  scene = new QGraphicsScene(this);
  ui->graphicsView->setScene(scene);
  printBox(scene);
  controller = new s21::Controller;
  maxScore = controller->getMaxScore();
  timer = new QTimer(this);
  connect(this, &MainWindow::enterPressed, this, &MainWindow::eventLoop);
  connect(timer, &QTimer::timeout, this, &MainWindow::eventLoop);
  timer->start(controller->getSpeed());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Return:
      isStart = true;
      break;
    case Qt::Key_Down:
      controller->setAction(Down);
      controller->setHold(true);
      if (timer->interval() != controller->getSpeed() / 5) {
        timer->stop();
        timer->start(controller->getSpeed() / 5);
      }
      break;
    case Qt::Key_Up:
      controller->setAction(Up);
      controller->setHold(true);
      if (timer->interval() != controller->getSpeed() / 5) {
        timer->stop();
        timer->start(controller->getSpeed() / 5);
      }
      break;
    case Qt::Key_Left:
      controller->setAction(Left);
      controller->setHold(true);
      if (timer->interval() != controller->getSpeed() / 5) {
        timer->stop();
        timer->start(controller->getSpeed() / 5);
      }
      break;
    case Qt::Key_Right:
      controller->setAction(Right);
      controller->setHold(true);
      if (timer->interval() != controller->getSpeed() / 5) {
        timer->stop();
        timer->start(controller->getSpeed() / 5);
      }
      break;
    case Qt::Key_Space:
      controller->setAction(Pause);
      break;
    case Qt::Key_Escape:
      controller->setAction(Terminate);
      break;
    default:
      break;
  }
  controller->userInput();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  int key = event->key();
  switch (key) {
    case Qt::Key_Return:
      isStart = true;
      break;
    case Qt::Key_Down:
      controller->setAction(Down);
      controller->setHold(false);
      if (timer->interval() != controller->getSpeed()) {
        timer->stop();
        timer->start(controller->getSpeed());
      }
      break;
    case Qt::Key_Up:
      controller->setAction(Up);
      controller->setHold(false);
      if (timer->interval() != controller->getSpeed()) {
        timer->stop();
        timer->start(controller->getSpeed());
      }
      break;
    case Qt::Key_Left:
      controller->setAction(Left);
      controller->setHold(false);
      if (timer->interval() != controller->getSpeed()) {
        timer->stop();
        timer->start(controller->getSpeed());
      }
      break;
    case Qt::Key_Right:
      controller->setAction(Right);
      controller->setHold(false);
      if (timer->interval() != controller->getSpeed()) {
        timer->stop();
        timer->start(controller->getSpeed());
      }
      break;
    default:
      break;
  }
  controller->userInput();
}

void MainWindow::updateCurrentState() {
  if (controller->isExit()) {
    close();
  }
  GameInfo_t gInfo = controller->updateCurrentState();
  if (controller->getCurrGameStatus() == GameStatus::normal &&
      controller->isExit() == false) {
    printField(gInfo, scene);
  } else if (controller->getCurrGameStatus() != GameStatus::normal) {
    cleanField(scene);
    if (controller->getCurrGameStatus() == GameStatus::lose)

      scene->addText("YOU LOST!")->setPos(180, 200);

    else if (controller->getCurrGameStatus() == GameStatus::win)

      scene->addText("YOU WON!")->setPos(180, 200);
  }
  if (gInfo.score > maxScore)
    gInfo.high_score = gInfo.score;
  else
    gInfo.high_score = maxScore;
  printAddField(gInfo, scene);
}

void MainWindow::eventLoop() {
  if (isStart) updateCurrentState();
}

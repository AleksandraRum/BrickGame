#include "qtfield.h"

void printBox(QGraphicsScene *scene) {
  scene->addRect(120, 120, (FIELD_WIDTH - 1) * 20, (FIELD_HEIGHT - 1) * 20);
  scene->addRect(360, 120, FIELD_WIDTH * 10, 70);
  scene->addText("SCORE")->setPos(390, 130);
  scene->addRect(360, 200, FIELD_WIDTH * 10, 70);
  scene->addText("LEVEL")->setPos(390, 210);
  scene->addRect(360, 280, FIELD_WIDTH * 10, 70);
  scene->addText("HIGH_SCORE")->setPos(370, 290);
  scene->addRect(360, 360, FIELD_WIDTH * 10, 100);
  scene->addText("NEXT")->setPos(390, 370);
}

void printField(GameInfo_t field, QGraphicsScene *scene) {
  cleanField(scene);
  for (int i = 1; i < FIELD_WIDTH; i++) {
    for (int j = 1; j < FIELD_HEIGHT; j++) {
      if (field.field[j][i] == 1) {
        QGraphicsItem *item =
            scene->addRect(100 + 20 * i, 100 + 20 * j, 20, 20);
        snakeVector.push_back(item);
      } else if (field.field[j][i] == 10) {
        itemTetr1 = scene->addRect(100 + 20 * i, 100 + 20 * j, 20, 20);
        tetrVector.push_back(itemTetr1);
      } else if (field.field[j][i] == 2) {
        item = scene->addRect(100 + 20 * i, 100 + 20 * j, 20, 20);
        fieldVector.push_back(item);
      } else if (field.field[j][i] == 100) {
        QPixmap pix("apple.png");
        pix = pix.scaled(QSize(20, 20));
        itemApple = scene->addPixmap(pix);
        itemApple->setPos(100 + 20 * i, 100 + 20 * j);
      }
    }
  }
}

void printAddField(GameInfo_t gameInfo, QGraphicsScene *scene) {
  if (itemText1 != nullptr) {
    scene->removeItem(itemText1);
    delete itemText1;
    scene->removeItem(itemText2);
    delete itemText2;
    scene->removeItem(itemText3);
    delete itemText3;
  }

  itemText1 = scene->addText(QString::number(gameInfo.score));
  itemText1->setPos(410, 150);

  itemText2 = scene->addText(QString::number(gameInfo.level));
  itemText2->setPos(410, 230);

  itemText3 = scene->addText(QString::number(gameInfo.high_score));
  itemText3->setPos(410, 310);
}

void printNextField(GameInfo_t gameInfo, QGraphicsScene *scene) {
  for (auto itemNext : nextVector) {
    scene->removeItem(itemNext);
    delete itemNext;
  }
  nextVector.clear();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (gameInfo.next[j][i]) {
        itemNext = scene->addRect(380 + 20 * i, 400 + 20 * j, 20, 20);
        nextVector.push_back(itemNext);
      }
    }
  }
}

void cleanField(QGraphicsScene *scene) {
  for (auto itemTetr1 : tetrVector) {
    scene->removeItem(itemTetr1);
    delete itemTetr1;
  }
  tetrVector.clear();
  for (auto item : fieldVector) {
    scene->removeItem(item);
    delete item;
  }
  fieldVector.clear();
  for (auto item : snakeVector) {
    scene->removeItem(item);
    delete item;
  }
  snakeVector.clear();
  if (itemApple != nullptr) {
    scene->removeItem(itemApple);
    delete itemApple;
    itemApple = nullptr;
  }
}

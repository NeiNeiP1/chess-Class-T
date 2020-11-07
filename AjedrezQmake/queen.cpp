#include "queen.h"

Queen::Queen(QWidget *parent): Pieza(parent)
{
    PiezaIcon.load("");
    this->setPixmap(PiezaIcon.scaled(QSize(50,50),Qt::KeepAspectRatio));
}

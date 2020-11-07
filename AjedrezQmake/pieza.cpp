#include "pieza.h"

Pieza::Pieza(QWidget *parent) : QLabel(parent)
{
PiezaIcon.load("figur.png");
       this->setPixmap(PiezaIcon.scaled(QSize(50,60), Qt::KeepAspectRatio));
}

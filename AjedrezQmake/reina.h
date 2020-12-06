#ifndef QUEEN_H
#define QUEEN_H

#include "pieza.h"
class Reina:public Pieza
{
public:
    Reina(QString team,QGraphicsItem *parent = 0);
    void setImage();

    void moves();

};

#endif // QUEEN_H

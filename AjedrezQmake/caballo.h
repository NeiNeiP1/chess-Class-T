#ifndef CABALLO_H
#define CABALLO_H

#include "pieza.h"
class Caballo:public Pieza
{
public:
    Caballo(QString team, QGraphicsItem *parent=0);
    void setImage();
    void moves();
};

#endif // CABALLO_H

#ifndef TORRE_H
#define TORRE_H
#include "pieza.h"
class Torre:public Pieza
{
public:
    Torre(QString team, QGraphicsItem *parent = 0);
    void setImage();
    void moves();
};

#endif // TORRE_H

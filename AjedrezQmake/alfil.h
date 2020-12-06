#ifndef ALFIL_H
#define ALFIL_H
#include "pieza.h"
class Alfil:public Pieza
{
public:
    Alfil(QString team,QGraphicsItem *parent=0);
    void setImage();
    void moves();
};

#endif // ALFIL_H

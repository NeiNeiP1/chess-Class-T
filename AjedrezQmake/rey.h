#ifndef REY_H
#define REY_H

#include "pieza.h"
class Rey:public Pieza
{
public:
    Rey(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void lugarSeguro();
    void moves();

};

#endif // KING_H

#ifndef PEON_H
#define PEON_H
#include "pieza.h"
class Peon:public Pieza
{
public:
    Peon(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();

 private:


};
#endif // PEON_H

#ifndef PIEZA_H
#define PIEZA_H

#include <QGraphicsPixmapItem>
#include "casilla.h"
#include <QGraphicsSceneMouseEvent>

class Casilla;
class Pieza:public QGraphicsPixmapItem
{
public:
    Pieza(QString team = "",QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCasilla(Casilla *box);

    Casilla *getCasilla() ;

    QString getEquipo() ;
    void setEquipo( QString value);
    virtual void setImage() = 0;

    bool getLugar() ;
    void setLugar(bool value);

    QList <Casilla *> moveLocation();
    virtual void moves() = 0;
    void decolor();

    bool firstMove;

    bool boxSetting(Casilla *box);
protected:
    Casilla *currentBox;
    QString equipo;
    bool lugar;
    QList <Casilla *> location;

};

#endif

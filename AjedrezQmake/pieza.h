#ifndef PIEZA_H
#define PIEZA_H

#include <QGraphicsPixmapItem>
#include "casilla.h"
#include <QGraphicsSceneMouseEvent>

class Casilla;
class Pieza:public QGraphicsPixmapItem
{
protected:
    Casilla *casilla;
    QString equipo;
    bool lugar;
    QList <Casilla *> location;

public:
    bool firstMove;
    //Constructor
    Pieza(QString team = "",QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //Casilla
    Casilla *getCasilla() ;
    void setCasilla(Casilla *box);
    //Equipo
    QString getEquipo() ;
    void setEquipo( QString value);
    //Lugar
    bool getLugar() ;
    void setLugar(bool value);

    QList <Casilla *> moveLocation();
    virtual void moves() = 0;
    void decolor();
    virtual void setImage() = 0;
    bool boxSetting(Casilla *box);

};

#endif

#ifndef CASILLA_H
#define CASILLA_H
#include <QGraphicsRectItem>
#include <QBrush>
#include "pieza.h"
#include <QGraphicsSceneMouseEvent>

class Pieza;
class Casilla:public QGraphicsRectItem
{
private:
    QBrush brush; //Relleno de las casillas formas dibujadas
    QColor color;
    bool hayPieza; //Valor de si hay Pieza en la casilla
    QString colorP;
public:

    Casilla(QGraphicsItem *parent=0);
    ~Casilla();
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //Evento al seleccionar con Mouse
    void setColor(QColor c); //Cambiar Color
    void setPieza(Pieza *p); //Cambiar Pieza
    void resetColor(); //Recupera el color base
    void setColorOriginal(QColor valor); //Cambiar color original
    bool getHayPieza(); //Método de si hay pieza
    void setHayPieza(bool valor,Pieza *p = 0); //Cambiar método
    void comprobarHaque();
    void peonCambio();
    QString getColorPieza();
    void setColorPieza(QString valor);
    int rowLoc;
    int colLoc;
    Pieza * currentPiece;
};

#endif // CASILLA_H

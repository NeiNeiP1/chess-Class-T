#include "pieza.h"
#include "juego.h"
#include <QDebug>
#include "rey.h"

extern Juego *game;
Pieza::Pieza(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    equipo = team;
    lugar = true;
    firstMove = true;
}

void Pieza::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deseleccionado
    if(this == game->pieza){
        game->pieza->getCasilla()->resetColor(); //Quitar el color
        game->pieza->decolor();
        game->pieza = NULL;
       return;
    }
    //Si no hay Pieza o si la pieza no es del equipo que le toca salta
    if((!getLugar() )|| ( (game->getTurno() != this->getEquipo())&& (!game->pieza)) )
        return;
    //Seleccionar
    if(!game->pieza){

        game->pieza = this;
        game->pieza->getCasilla()->setColor(Qt::yellow); //Color de la ficha seleccionada
        game->pieza->moves();
    }
    //Si se selecciona la pieza enemiga de la pieza elegida a mover. Accion de click de casilla
    else if(this->getEquipo() != game->pieza->getEquipo()){
        this->getCasilla()->mousePressEvent(event);
    }


}

void Pieza::setCasilla(Casilla *box)
{

    currentBox = box;
}

Casilla *Pieza::getCasilla()
{
    return currentBox;
}

QString Pieza::getEquipo()
{
    return equipo;
}

void Pieza::setEquipo( QString value)
{
    equipo = value;
}

bool Pieza::getLugar()
{
    return lugar;
}

void Pieza::setLugar(bool value)
{
    lugar = value;

}
QList<Casilla *> Pieza::moveLocation()
{
    return location;
}
void Pieza::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetColor();
    }
}

bool Pieza::boxSetting(Casilla *box)
{
    if(box->getHayPieza()) {//Si en la casilla hay una pieza
        Rey *q = dynamic_cast<Rey*>(location.last()->currentPiece);
        if(q){//Si es un rey
            box->setColor(Qt::blue); //Que muestre que estará en haque Azul
        }
        else
            box->setColor(Qt::red); //Si no que muestre en rojo la ficha
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed); //Si no hay nada muestra un rojo oscuro
    return false;
}

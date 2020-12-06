#include "peon.h"
#include "juego.h"
#include <QDebug>
#include <typeinfo>
#include "rey.h"
extern Juego * game;
Peon::Peon(QString team,QGraphicsItem *parent):Pieza(team,parent)
{
    setImage();
    firstMove = true; //Tiene efecto de primer movimiento
}

void Peon::setImage()
{ //Según el equipo se le asigna la imagen
    if(equipo == "Blanco")
        setPixmap(QPixmap(":/images/peon1.png"));
    else
        setPixmap(QPixmap(":/images/peon.png"));
}



void Peon::moves()
{ //Limpiando sus casillas anteriores
    location.clear();
    int row = this->getCasilla()->rowLoc; //Fila
    int col = this->getCasilla()->colLoc; //Columna de donde está
    //Si la pieza es blanca
    if(this->getEquipo() == "Blanco"){
        //Y si aun no llegó al final de arriba
        //Si no está al extremo de la izquierda y hay una ficha al frente izquierda Negro
        if(col > 0 && row > 0 && game->caja[row-1][col-1]->getColorPieza() == "Negro") {
            //Guarda que puede ir a esta casilla de la izquierda
            location.append(game->caja[row-1][col-1]);
            //Actualiza color
            boxSetting(location.last());
        }
        //Si no está al extremo de la derecha y hay una ficha al frente derecha Negro
        if(col < 7 && row > 0 && game->caja[row-1][col+1]->getColorPieza() == "Negro") {
            //Guarda que puede ir a esta casilla de la derecha
            location.append(game->caja[row-1][col+1]);
            //Actualiza color
            boxSetting(location.last());
        }
        //Si al frente suyo no hay ficha
        if(row>0 && (!game->caja[row-1][col]->getHayPieza())) {
            //Guarda que puede ir a esta casilla
            location.append(game->caja[row-1][col]);
            //Actualiza color
            boxSetting(location.last());
            //Si aun no hizo su primer movimiento y si está libre las seg casilla de frente
            if(firstMove && !game->caja[row-2][col]->getHayPieza()){
                //Guarda que puede ir a esta casilla
                location.append(game->caja[row-2][col]);
                //Actualiza color
                boxSetting(location.last());
            }

        }

    }
    //Si la pieza es negra
    else{
        //Si aún no llega al final de abajo
        //Si no está al extremo de la izquierda y hay una ficha al frente izquierda Blanca
        if(col > 0 && row < 7 && game->caja[row+1][col-1]->getColorPieza() == "Blanco") {
            //Guarda que puede ir a esta casilla de la izquierda
            location.append(game->caja[row+1][col-1]);
            //Actualiza color
            boxSetting(location.last());
        }
        //Si no está al extremo de la derecha  y hay una ficha al frente derecha Blanca
        if(col < 7 && row <  7 && game->caja[row+1][col+1]->getColorPieza() == "Blanco") {
            //Guarda que puede ir a esta casilla de la derecha
            location.append(game->caja[row+1][col+1]);
            //Actualiza color
            boxSetting(location.last());
        }
         //Si al frente suyo no hay ficha
        if(row<7 && (!game->caja[row+1][col]->getHayPieza())) {
            //Guarda que puede ir a esta casilla
            location.append(game->caja[row+1][col]);
            //Actualiza color
            boxSetting(location.last());
            //Si aun no hizo su primer movimiento y si está libre las seg casilla de frente
            if(firstMove && !game->caja[row+2][col]->getHayPieza()){
                //Guarda que puede ir a esta casilla
                location.append(game->caja[row+2][col]);
                //Actualiza color
                boxSetting(location.last());
            }

        }

    }

}



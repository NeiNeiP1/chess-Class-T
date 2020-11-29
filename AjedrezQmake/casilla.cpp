#include "casilla.h"
#include "juego.h"
#include <QDebug>
#include "rey.h"

extern Juego *game;
Casilla::Casilla(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //Casilla del Tablero
    setRect(0,0,100,100); //Medida
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHayPieza(false); //Defecto no Hay Pieza
    setColorPieza("NONE"); //Color para Pieza
    currentPiece = NULL;
}

Casilla::~Casilla()
{
    delete this;
}

void Casilla::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

        //Deseleccionar contraparte de la Pieza
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //Si es seleccionada
        if(game->pieceToMove){
            //Si es del mismo equipo
            if(this->getColorPieza() == game->pieceToMove->getSide())
                return;
            //Quitar la Pieza Comida
            QList <Casilla *> movLoc = game->pieceToMove->moveLocation();

            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) { //Comprueba si la casilla elegida está en la zona para moverse
                    check++;

                }
            }
            //Si no hay opción de movida sale
            if(check == 0)
                return;
            //Cambia el color al normal
             game->pieceToMove->decolor();
             //Solo para el Peón el movimiento puede ser falso
             game->pieceToMove->firstMove = false;
            if(this->getHayPieza()){ //Si hay una pieza del enemigo
                this->currentPiece->setIsPlaced(false); //Se reemplaza
                this->currentPiece->setCurrentBox(NULL);
                game->fichaComida(this->currentPiece); //Se consume la ficha

            }
            //Cambia el estado y reestablece la región izquierda anterior
            game->pieceToMove->getCurrentBox()->setHayPieza(false);
            game->pieceToMove->getCurrentBox()->currentPiece = NULL;
            game->pieceToMove->getCurrentBox()->resetColor();
            setPieza(game->pieceToMove);

            game->pieceToMove = NULL;
            //Cambia Turno
            game->changeTurn();
            comprobarHaque();
        }
       // Selección de la contraparte de la pieza de ajedrez
        else if(this->getHayPieza())
        {
            this->currentPiece->mousePressEvent(event);
        }
}
//SetColor
void Casilla::setColor(QColor c)
{
    brush.setColor(c);
    setBrush(c);
}
//SetPieza
void Casilla::setPieza(Pieza *p)
{

    p->setPos(x()+50- p->pixmap().width()/2  ,y()+50-p->pixmap().width()/2);
    p->setCurrentBox(this);
    setHayPieza(true,p);
    currentPiece = p;


}
//Resetear Color
void Casilla::resetColor()
{
    setColor(color);
}


//Set Color Original
void Casilla::setColorOriginal(QColor valor)
{
    color = valor;
    setColor(color);
}
//Get Hay Pieza
bool Casilla::getHayPieza()
{
    return hayPieza;
}
//Set Hay Pieza
void Casilla::setHayPieza(bool valor, Pieza *p)
{
    hayPieza = valor;
    if(valor)
        setColorPieza(p->getSide());
    else
        setColorPieza("NONE");
}

void Casilla::comprobarHaque()
{
    bool cam = false;
    QList <Pieza *> piezas = game->alivePiece; //Piezas del Juego
    for(size_t i = 0,n=piezas.size(); i < n; i++ ) {

        Rey * p = dynamic_cast<Rey *> (piezas[i]); //Comprueba si la clase de la Lista es Rey
        if(p){
            continue; //Si lo es salta
        }
        piezas[i]->moves();  //Mover
        piezas[i]->decolor();
        QList <Casilla *> casi = piezas[i]->moveLocation(); //Ver el MoveLocation de la pieza
        for(size_t j = 0,n = casi.size(); j < n; j ++) {
            Rey * p = dynamic_cast<Rey *> (casi[j]->currentPiece); //Si en la casillas hay un rey
            if(p) {
                if(p->getSide() == piezas[i]->getSide())//Y si es el mismo get side
                    continue; //Salta
                casi[j]->setColor(Qt::blue); //De lo contrario se cambia el color de la casilla a azul
                piezas[i]->getCurrentBox()->setColor(Qt::darkRed); //El color de la ficha que dejó en haque en rojo oscuro
                if(!game->haque->isVisible())//Si aun no hubo un haque antes
                    game->haque->setVisible(true); //se actualiza a que hay un haque
                else{
                    casi[j]->resetColor();  //De lo contrario reiniciar el color base
                    piezas[i]->getCurrentBox()->resetColor();
                    game->gameOver(); //Se acaba el juego
                }
                cam=true;

            }
        }


    }
    if(!cam){
        game->haque->setVisible(false); //Se quita el haque
        for(size_t i = 0,n=piezas.size(); i < n; i++ )
           piezas[i]->getCurrentBox()->resetColor(); //Se actualiza el color de las casillas
    }
}
//Get del Color de la Pieza
QString Casilla::getColorPieza()
{
    return colorP;
}
//Set del Color de la Pieza
void Casilla::setColorPieza(QString valor)
{
    colorP = valor;
}

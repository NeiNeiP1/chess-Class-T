#include "casilla.h"
#include "juego.h"
#include <QDebug>
#include "rey.h"

extern Juego *game;
Casilla::Casilla(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //making the Square CHess Box
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHayPieza(false);
    setColorPieza("NONE");
    currentPiece = NULL;
}

Casilla::~Casilla()
{
    delete this;
}

void Casilla::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      //  qDebug() << getChessPieceColor();
        //Deselecting counter part of ChessPiece
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(game->pieceToMove){
            //if same team
            if(this->getColorPieza() == game->pieceToMove->getSide())
                return;
            //removing the eaten piece
            QList <Casilla *> movLoc = game->pieceToMove->moveLocation();
            //TO make sure the selected box is in move zone
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;

                }
            }
            // if not prsent return
            if(check == 0)
                return;
            //change the color back to normal
             game->pieceToMove->decolor();
             //make the first move false applicable for pawn only
             game->pieceToMove->firstMove = false;
             //this is to eat or consume the enemy present inn the movable region
            if(this->getHayPieza()){
                this->currentPiece->setIsPlaced(false);
                this->currentPiece->setCurrentBox(NULL);
                game->fichaComida(this->currentPiece);

            }
            //changing the new stat and resetting the previous left region
            game->pieceToMove->getCurrentBox()->setHayPieza(false);
            game->pieceToMove->getCurrentBox()->currentPiece = NULL;
            game->pieceToMove->getCurrentBox()->resetColor();
            setPieza(game->pieceToMove);

            game->pieceToMove = NULL;
            //changing turn
            game->changeTurn();
            comprobarHaque();
        }
        //Selecting couterpart of the chessPiece
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

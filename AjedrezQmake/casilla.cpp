#include "casilla.h"
#include "juego.h"
#include <QDebug>
#include "rey.h"
#include "peon.h"
#include "reina.h"
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

        //Deseleccionar la Pieza
        if(currentPiece == game->pieza && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //Si ya hay pieza elegida a mover
        if(game->pieza){
            //Si la pieza de la casilla el color es la misma que la elegida Salta
            if(this->getColorPieza() == game->pieza->getEquipo())
                return;
            //Guardar la posible posicion de la pieza
            QList <Casilla *> movLoc = game->pieza->moveLocation();

            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) { //Comprueba si la casilla elegida está en la zona para moverse
                    check++;

                }
            }
            //Si no hay opción de movida sale
            if(check == 0)
                return;
            //Resetea el color
             game->pieza->decolor();
             //Cambia el que ya hizo su primer movimiento
             enroque();
             game->pieza->firstMove = false;
            if(this->getHayPieza()){ //Si hay una pieza del enemigo
                this->currentPiece->setLugar(false); //Se reemplaza
                this->currentPiece->setCasilla(NULL);
                game->fichaComida(this->currentPiece); //Se consume la ficha

            }
            //Cambia el estado de la pieza en donde estaba antes.
            game->pieza->getCasilla()->setHayPieza(false);
            game->pieza->getCasilla()->currentPiece = NULL;
            game->pieza->getCasilla()->resetColor();
            game->registrar(this->getLetra(),game->pieza->getEquipo());
            peonCambio();


            //Cambia Turno
            game->changeTurn();
            comprobarHaque();
        }
       //Si no habia pieza seleccionada hará accion de seleccionar pieza
        else if(this->getHayPieza())
        {
            this->currentPiece->mousePressEvent(event);
        }
}
void Casilla::enroque(){
    Rey *p=dynamic_cast<Rey *>(game->pieza);
    if(p){
        int fil=game->pieza->getCasilla()->rowLoc;
        int colu=game->pieza->getCasilla()->colLoc;
        if(game->pieza->firstMove&&(this->colLoc-2==game->pieza->getCasilla()->colLoc)){

            Pieza *tor=game->caja[fil][colu+3]->currentPiece;
            game->caja[fil][colu+3]->setHayPieza(false);
            game->caja[fil][colu+3]->currentPiece = NULL;
            game->caja[fil][colu+1]->setPieza(tor);
            tor->setCasilla(game->caja[fil][colu+1]);
        }
        if(game->pieza->firstMove&&(this->colLoc+2==game->pieza->getCasilla()->colLoc)){
            Pieza *tor=game->caja[fil][colu-4]->currentPiece;
            game->caja[fil][colu-4]->setHayPieza(false);
            game->caja[fil][colu-4]->currentPiece = NULL;
            game->caja[fil][colu-1]->setPieza(tor);
            tor->setCasilla(game->caja[fil][colu-1]);
        }
    }
}
//El cambio que tiene el peon al llegar al otro extremo del tablero
void Casilla::peonCambio(){
    Peon * p = dynamic_cast<Peon *> (game->pieza);
    if(p){
        if(game->pieza->getEquipo()=="Blanco"){
            if(game->pieza->getCasilla()->rowLoc==1){
                Reina *r=new Reina("Blanco");
                game->pVivas.removeAll(game->pieza);
                game->pVivas.append(r);
                game->tabla->blancas.append(r);
                game->addToScene(r);
                game->removeFromScene(game->pieza);
                setPieza(r);

            }
            else
                setPieza(game->pieza);
        }
        else {
            if(game->pieza->getCasilla()->rowLoc==6){
                Reina *r=new Reina("Negro");
                game->pVivas.removeAll(game->pieza);
                game->pVivas.append(r);
                game->tabla->negras.append(r);
                game->addToScene(r);
                game->removeFromScene(game->pieza);
                setPieza(r);

            }
            else
                setPieza(game->pieza);

        }
    }
    else
        setPieza(game->pieza);
    game->pieza = NULL;
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
    p->setCasilla(this);
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
        setColorPieza(p->getEquipo());
    else
        setColorPieza("NONE");
}

void Casilla::comprobarHaque(){
    bool cam = false;
    QList <Pieza *> piezas = game->pVivas; //Piezas del Juego
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
                if(p->getEquipo() == piezas[i]->getEquipo())//Y si es el mismo get Equipo
                    continue; //Salta
                casi[j]->setColor(Qt::blue); //De lo contrario se cambia el color de la casilla a azul
                piezas[i]->getCasilla()->setColor(Qt::darkRed); //El color de la ficha que dejó en haque en rojo oscuro
                if(!game->haque->isVisible())//Si aun no hubo un haque antes
                    game->haque->setVisible(true); //se actualiza a que hay un haque
                else{
                    casi[j]->resetColor();  //De lo contrario reiniciar el color base
                    piezas[i]->getCasilla()->resetColor();
                    if(casi[j]->currentPiece->getEquipo()=="Blanco")
                        game->gameOver(0); //Se acaba el juego
                    else
                        game->gameOver(1); //Se acaba el juego
                }
                cam=true;

            }
        }


    }
    if(!cam){
        game->haque->setVisible(false); //Se quita el haque
        for(size_t i = 0,n=piezas.size(); i < n; i++ )
           piezas[i]->getCasilla()->resetColor(); //Se actualiza el color de las casillas
    }
}
QString Casilla::getLetra(){
    return letra;
}
void Casilla::setLetra(QString v){
    letra=v;
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

#include "rey.h"
#include "juego.h"
#include "peon.h"
extern Juego *game;
Rey::Rey(QString team,QGraphicsItem *parent):Pieza(team,parent)
{
    setImage();
    firstMove=true;
}

void Rey::setImage()
{
    if(equipo == "Blanco")
        setPixmap(QPixmap(":/images/rey1.png"));
    else
        setPixmap(QPixmap(":/images/rey.png"));
}


void Rey::moves()
{//Actualizar Casillas a donde puede ir
    location.clear();
    int row = this->getCasilla()->rowLoc; //Fila
    int col = this->getCasilla()->colLoc; //Columna en Donde está
    QString team = this->getEquipo(); //El Equipo en donde está
    // Si no está a extremo izquierda y si no hay una pieza aliada a la izquierda
    if(col>0 && !(game->caja[row][col-1]->getColorPieza() == team)){
        //Guarda que la casilla es disponible
        location.append(game->caja[row][col-1]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row][col-1]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    // Si no está a extremo derecha y si no hay una pieza aliada a la derecha
    if(col<7 && !(game->caja[row][col+1]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row][col+1]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row][col+1]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    // Si no está a extremo arriba y si no hay una pieza aliada arriba
    if(row>0 && !(game->caja[row-1][col]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row-1][col]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row-1][col]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }

    if(row<7 && !(game->caja[row+1][col]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row+1][col]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row+1][col]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    // Si no está a extremo arriba izquierda y si no hay una pieza aliada arriba izquierda
    if(col > 0 && row > 0 && !(game->caja[row-1][col-1]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row-1][col-1]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row-1][col-1]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    // Si no está a extremo arriba derecha y si no hay una pieza aliada arriba derecha
    if(col < 7 && row > 0 && !(game->caja[row-1][col+1]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row-1][col+1]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row-1][col+1]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    // Si no está a extremo abajo izquierda y si no hay una pieza aliada abajo izquierda
    if(col > 0 && row < 7  && !(game->caja[row+1][col-1]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row+1][col-1]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row+1][col-1]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    // Si no está a extremo abajo derecha y si no hay una pieza aliada abajo derecha
    if(col < 7 && row < 7 && !(game->caja[row+1][col+1]->getColorPieza() == team)) {
        //Guarda que la casilla es disponible
        location.append(game->caja[row+1][col+1]);
        //Se guarda la casilla a rojo oscuro estando vacia
        game->caja[row+1][col+1]->setColor(Qt::darkRed);
        //Si hay una pieza Actualiza y pasa a rojo
        if(location.last()->getHayPieza()){
            location.last()->setColor(Qt::red);
        }
    }
    //Movimiento Enroque derecha
    if(firstMove&&!(game->caja[row][col+1]->getHayPieza())&&!(game->caja[row][col+2]->getHayPieza())&&(game->caja[row][col+3]->currentPiece->firstMove)){
        location.append(game->caja[row][col+2]);
        game->caja[row][col+2]->setColor(Qt::green);
    }
    //Movimiento Enroque Izquierda
    if(firstMove&&!(game->caja[row][col-1]->getHayPieza())&&!(game->caja[row][col-2]->getHayPieza())&&!(game->caja[row][col-3]->getHayPieza())&&(game->caja[row][col-4]->currentPiece->firstMove)){
        location.append(game->caja[row][col-2]);
        game->caja[row][col-2]->setColor(Qt::green);
    }
    lugarSeguro();


}

void Rey::lugarSeguro() {
    QList <Pieza *> pList = game->pVivas;
    for(size_t i = 0,n = pList.size(); i < n; i++) {
        if(pList[i]->getEquipo() != this->getEquipo()){//Las piezas enemigas
            QList <Casilla *> bList = pList[i]->moveLocation(); //Que indique sus posibles lugares a moverse
            for(size_t j = 0, n = bList.size(); j < n; j++){
                //Conserva si la pieza es un peón
                Peon *c = dynamic_cast<Peon *> (pList[i]) ;
                for(size_t k = 0, n = location.size(); k < n; k++) {
                if(c){
                    int fil=pList[i]->getCasilla()->rowLoc; //Fila
                    int colu=pList[i]->getCasilla()->colLoc; //Columna del Peon
                        if(pList[i]->getEquipo()=="Blanco"){
                            if((fil>0)||((fil-1)==this->getCasilla()->rowLoc)){
                                if(colu>0){
                                    Casilla *cas=game->caja[fil-1][colu+1]; //El lado Noreste que si cae el rey muere
                                    if(cas==location[k]){
                                        location[k]->setColor(Qt::blue); //Peligro
                                    }
                                }
                                if(colu< 7){
                                     Casilla *cas=game->caja[fil-1][colu-1]; //El lado Noroeste que si cae el rey muere
                                     if(cas==location[k]){
                                         location[k]->setColor(Qt::blue); //Peligro
                                     }
                                }
                            }
                        }
                        else{
                            if((fil<7)||((fil+1)==this->getCasilla()->rowLoc)){
                                if(colu>0){
                                    Casilla *cas=game->caja[fil+1][colu+1]; //El lado Sureste que si cae el rey muere
                                    if(cas==location[k]){
                                        location[k]->setColor(Qt::blue);
                                    }
                                }
                                if(colu<7){
                                     Casilla *cas=game->caja[fil+1][colu-1]; //El lado Suroeste que si cae el rey muere
                                     if(cas==location[k]){
                                         location[k]->setColor(Qt::blue);
                                     }
                                }
                            }
                        }

                }
                else{
                    if(bList[j] == location [k]) { //Las casillas por defecto
                        location[k]->setColor(Qt::blue);
                    }
                }
             }
        }
        }
    }
}

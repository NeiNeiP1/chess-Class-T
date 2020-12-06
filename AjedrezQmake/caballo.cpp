#include "caballo.h"
#include "juego.h"
extern Juego *game;
Caballo::Caballo(QString team,QGraphicsItem *parent):Pieza(team,parent)
{
    setImage();
}
void Caballo::setImage(){
    if(equipo=="Blanco")
        setPixmap(QPixmap(":/images/caballo1.png"));
    else
        setPixmap(QPixmap(":/images/caballo.png"));
}
void Caballo::moves(){
    int row=this->getCasilla()->rowLoc;
    int col=this->getCasilla()->colLoc;
    QString team= this->getEquipo();
    //Posiciones de Arriba
    int i=row-2;
    int j=col-1;
    if(i>=0 &&j>=0 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    j=col+1;
    if(i>=0 &&j<=7 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    //Posiciones Abajo
    i=row+2;
    if(i<=7 &&j<=7 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    j=col-1;
    if(i<=7 &&j>=0 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    //Posiciones del lado izquierdo
    i=row+1;
    j=col-2;
    if(i<=7 &&j>=0 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    i=row-1;
    if(i>=0 &&j>=0 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    //Posiciones del lado derecho
    j=col+2;
    if(i>=0 &&j<=7 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
    i=row+1;
    if(i<=7 &&j<=7 && (game->caja[i][j]->getColorPieza()!=team)){
        location.append(game->caja[i][j]);
        if(location.last()->getHayPieza())
            location.last()->setColor(Qt::red);
        else
            location.last()->setColor(Qt::darkRed);
    }
}

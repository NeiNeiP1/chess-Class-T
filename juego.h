#ifndef JUEGO_H
#define JUEGO_H


#include <QGraphicsView>
#include <QGraphicsScene>
#include <board.h>
#include "pieza.h"
class Juego:public QGraphicsView
{
    Q_OBJECT
private:
    QGraphicsScene *escena;
    QList <Pieza *> comidasB;
    QList <Pieza *> comidasN;
    QGraphicsRectItem * deadHolder;
    QString turn;
    Board *tablero;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turno;


public:
    Juego(QWidget *parent = 0);
    void tablaComida(int x, int y, QColor color);
    void drawChessBoard();
    void blancaComida();
    void negraComida();
    void fichaComida(Pieza *piece);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    //getters/setters
    Pieza *pieceToMove;

    QString getTurno() ;
    void setTurno( QString value);
    void changeTurn();



    Casilla *collection[8][8];
    QGraphicsTextItem *haque;
    QList <Pieza *> alivePiece;

    void gameOver();
    void removeAll();
    void menu();
public slots:
    void start();

};


#endif // JUEGO_H

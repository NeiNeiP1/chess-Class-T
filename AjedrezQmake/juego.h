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
    QList <Pieza *> comidasB; //Lista Fichas Comidas Blancas
    QList <Pieza *> comidasN; //Lista Fichas Comidas Negras
    QGraphicsRectItem * deadHolder;
    QString turn; //Cambio de Turno
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turno;


public:
    Juego(QWidget *parent = 0);
    void tablaComida(int x, int y, QColor color); //Actualiza la tabla donde se muestran las fichas comidas
    void dibujarTablero();
    void blancaComida();
    void negraComida();
    void fichaComida(Pieza *piece);

    //Añadir o quitar item grafico en la escena
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    Board *tabla; //Tablero
    Pieza *pieza;
    //Turnos
    QString getTurno() ;
    void setTurno( QString value);
    void changeTurn();

    Casilla *caja[8][8];
    QGraphicsTextItem *haque; //Muestra de Haque
    QList <Pieza *> pVivas;

    void gameOver();
    void removeAll();
    void menu();
public slots:
    void start();

};


#endif // JUEGO_H

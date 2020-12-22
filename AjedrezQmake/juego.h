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
    QGraphicsRectItem * muerto;
    QString turn; //Cambio de Turno
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turno;
    QGraphicsPixmapItem *star;
    QGraphicsTextItem* cron1=new QGraphicsTextItem();
    QGraphicsTextItem* cron2=new QGraphicsTextItem();
    int seg1=0;
    int seg2=0;
    int min1=0;
    int min2=0;
    QTimer *cronometro;
    QTimer *cronometro2;
    int contador=0;
public:
    Juego(QWidget *parent = 0);
    void tablaComida(int x, int y, QColor color); //Actualiza la tabla donde se muestran las fichas comidas
    void dibujarTablero();
    void blancaComida();
    void negraComida();
    void fichaComida(Pieza *piece);
    //Variables para cronometros

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
    //Registro de Casillas
    QList <QString> registroB;
    QList <QString> registroN;
    void registrar(QString letra,QString team);
    void registrarB(QString letra);
    void registrarN(QString letra);
    void removeAll();
    void gameOver(int i);
    void menu();
public slots:
    void start();
    void renunciaB();
    void renunciaN();
    void activarTiempo();
    void activarTiempo2();
};


#endif // JUEGO_H

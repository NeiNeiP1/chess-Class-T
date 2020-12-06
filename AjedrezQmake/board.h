#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsRectItem>
#include "pieza.h"
class Board
{
private:

public:
    QList <Pieza *> blancas; //Lista de Piezas Blancas
    QList <Pieza *> negras; //Lista de Piezas Negras
    Board();
    void tablero(int x, int y); //Hacer el tablero según las medidas
    void ponerFB(); //Método para colocar las Fichas Blancas
    void ponerFN(); //Método para colocar las Fichas Negras
    void agregarPieza(); //Método de agregar las piezas
    void reset(); //Resetear el juego
};

#endif // BOARD_H

#include "board.h"
#include "casilla.h"
#include "juego.h"
#include "peon.h"
#include "rey.h"
extern Juego *game;
Board::Board()
{
    ponerFN();
    ponerFB();
}
void Board::tablero(int x,int y)
{
    int pos = 100; //Valor para el tamaño y posición de las casillas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            Casilla *casilla = new Casilla();
            game->collection[i][j] = casilla ; //Se guarda un array
            casilla ->rowLoc = i; //Se guarda posición i
            casilla ->colLoc = j; //Se guarda posición j
            casilla ->setPos(x+pos*j,y+pos*i); //Se coloca la posición con shift
            if((i+j)%2==0)//Si la casilla es par
                casilla ->setColorOriginal(Qt::gray); //Será de color gris
            else //Si no
                casilla ->setColorOriginal(Qt::white); //Será de color blanca
            game->addToScene(casilla); //Se añade a la vista



        }
    }

}

//Método para agregar pieza
void Board::agregarPieza() {
    int n=0; //Variable para agregar piezas negras
    int b=0; //Variable para agregar piezas blancas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            Casilla *casilla =game->collection[i][j];
            if(i < 2) { //En la primera y segunda fila se añadirán las piezas negras

                casilla->setPieza(negras[n]); //Se guarda la posición de la pieza "n" y sus datos en la casilla
                game->alivePiece.append(negras[n]); //Se inserta la pieza "n" en la QList
                game->addToScene(negras[n++]); //Se agrega la siguiente pieza a la escena
            }
            if(i > 5) { //En la penultima y ultima fila se añadiran las piezas blancas

                casilla->setPieza(blancas[b]); //Se guarda la posición de la pieza "b" y sus datos en la casilla
                game->alivePiece.append(blancas[b]); //Se inserta la pieza "b" en la QList
                game->addToScene(blancas[b++]); //Se agrega la siguiente pieza a la escena
            }

        }
    }
}
//Al crear una clase Pieza, esta recibe el tipo que será, se coloca en un
//orden específico.
void Board::ponerFB()
{
    Pieza *piece;
    for(int i = 0; i < 16; i++) {
        if(i!=12){
        piece = new Peon("Blanco");
        }else{
            piece = new Rey("Blanco");
        }

        blancas.append(piece);
    }


}
//Al crear una clase Pieza, esta recibe el tipo que será, se coloca en un
//orden específico.
void Board::ponerFN()
{
    Pieza *piece;
    for(int i = 0; i < 16; i++) {
        if(i!=4){
        piece = new Peon("Negro");
        }else{
            piece = new Rey("Negro");
            blancas.append(piece);
        }
        blancas.append(piece);
    }
}


void Board::reset() {
    int n=0; //Variable para agregar piezas negras
    int b=0; //Variable para agregar piezas blancas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            Casilla *casilla =game->collection[i][j];
            casilla->setHayPieza(false); //Se borra la prueba de que habia una ficha en la casilla.
            casilla->setColorPieza("NONE"); //Se quita el color de ficha que estaba
            casilla->currentPiece = NULL; //Se quita la pieza
            if(i < 2) { //En la primera y segunda fila se añadirán las piezas negras

                casilla->setPieza(negras[n]); //Se guarda la posición de la pieza "n" y sus datos en la casilla
                negras[n]->setIsPlaced(true); //Se actualizan los datos
                negras[n]->firstMove = true;
                game->alivePiece.append(negras[n++]); //Se inserta la pieza "n" en la QList

            }
            if(i > 5) {

                casilla->setPieza(blancas[b]); //Se guarda la posición de la pieza "b" y sus datos en la casilla
                blancas[b]->setIsPlaced(true); //Se actualizan los datos
                blancas[b]->firstMove = true;
                game->alivePiece.append(blancas[b++]); //Se inserta la pieza "b" en la QList


            }

        }
    }
}

#include "board.h"
#include "casilla.h"
#include "juego.h"
#include "reina.h"
#include "torre.h"
#include "peon.h"
#include "rey.h"
#include "caballo.h"
#include "alfil.h"
extern Juego *game;
Board::Board()
{
    ponerFN();
    ponerFB();
}
void Board::tablero(int x,int y){
    int pos = 100; //Valor para el tamaño y posición de las casillas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            Casilla *casilla = new Casilla();
            game->caja[i][j] = casilla ; //Se guarda un array
            casilla ->rowLoc = i; //Se guarda posición i
            casilla ->colLoc = j; //Se guarda posición j
            casilla ->setPos(x+pos*j,y+pos*i); //Se coloca la posición con shift
            if((i+j)%2==0)//Si la casilla es par
                casilla ->setColorOriginal(Qt::gray); //Será de color gris
            else //Si no
                casilla ->setColorOriginal(Qt::white); //Será de color blanca

            QGraphicsTextItem* num= new QGraphicsTextItem();
            QGraphicsTextItem* num2= new QGraphicsTextItem();
            switch (i){
                case 0:
                    num->setPlainText("8");
                    num->setPos(game->width()/2-430,80); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("8");
                    num2->setPos(1120,80); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 1:
                    num->setPlainText("7");
                    num->setPos(game->width()/2-430,180); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("7");
                    num2->setPos(1120,180); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 2:
                    num->setPlainText("6");
                    num->setPos(game->width()/2-430,280); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("6");
                    num2->setPos(1120,280); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 3:
                    num->setPlainText("5");
                    num->setPos(game->width()/2-430,380); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("5");
                    num2->setPos(1120,380); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 4:
                    num->setPlainText("4");
                    num->setPos(game->width()/2-430,480); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("4");
                    num2->setPos(1120,480); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 5:
                    num->setPlainText("3");
                    num->setPos(game->width()/2-430,580); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("3");
                    num2->setPos(1120,580); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 6:
                    num->setPlainText("2");
                    num->setPos(game->width()/2-430,680); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("2");
                    num2->setPos(1120,680); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
                case 7:
                    num->setPlainText("1");
                    num->setPos(game->width()/2-430,780); //Se coloca la posición con shift
                    num->setFont(QFont("Arial",20));
                    game->addToScene(num);
                    num2->setPlainText("1");
                    num2->setPos(1120,780); //Se coloca la posición con shift
                    num2->setFont(QFont("Arial",20));
                    game->addToScene(num2);
                    break;
            }
            switch (j) {
                case 0:
                    casilla->setLetra("A");
                    break;
                case 1:
                    casilla->setLetra("B");
                    break;
                case 2:
                    casilla->setLetra("C");
                    break;
                case 3:
                    casilla->setLetra("D");
                    break;
                case 4:
                    casilla->setLetra("E");
                    break;
                case 5:
                    casilla->setLetra("F");
                    break;
                case 6:
                    casilla->setLetra("G");
                    break;
                case 7:
                    casilla->setLetra("H");
                    break;

            }
            casilla->setLetra(casilla->getLetra()+QString::number(8-i));
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
            Casilla *casilla =game->caja[i][j];
            if(i < 2) { //En la primera y segunda fila se añadirán las piezas negras

                casilla->setPieza(negras[n]); //Se guarda la posición de la pieza "n" y sus datos en la casilla
                game->pVivas.append(negras[n]); //Se inserta la pieza "n" en la QList
                game->addToScene(negras[n++]); //Se agrega la siguiente pieza a la escena
            }
            if(i > 5) { //En la penultima y ultima fila se añadiran las piezas blancas

                casilla->setPieza(blancas[b]); //Se guarda la posición de la pieza "b" y sus datos en la casilla
                game->pVivas.append(blancas[b]); //Se inserta la pieza "b" en la QList
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
    for(int i = 0; i < 8; i++) {
        piece = new Peon("Blanco");
        blancas.append(piece);
    }
    piece=new Torre("Blanco");
    blancas.append(piece);
    piece=new Caballo("Blanco");
    blancas.append(piece);
    piece=new Alfil("Blanco");
    blancas.append(piece);
    piece=new Reina("Blanco");
    blancas.append(piece);
    piece=new Rey("Blanco");
    blancas.append(piece);
    piece=new Alfil("Blanco");
    blancas.append(piece);
    piece=new Caballo("Blanco");
    blancas.append(piece);
    piece=new Torre("Blanco");
    blancas.append(piece);
}
//Al crear una clase Pieza, esta recibe el tipo que será, se coloca en un
//orden específico.
void Board::ponerFN()
{
    Pieza *piece;
    piece=new Torre("Negro");
    negras.append(piece);
    piece=new Caballo("Negro");
    negras.append(piece);
    piece=new Alfil("Negro");
    negras.append(piece);
    piece=new Reina("Negro");
    negras.append(piece);
    piece=new Rey("Negro");
    negras.append(piece);
    piece=new Alfil("Negro");
    negras.append(piece);
    piece=new Caballo("Negro");
    negras.append(piece);
    piece=new Torre("Negro");
    negras.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Peon("Negro");
        negras.append(piece);
    }

}


void Board::reset() {
    int n=0; //Variable para agregar piezas negras
    int b=0; //Variable para agregar piezas blancas
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            Casilla *casilla =game->caja[i][j];
            casilla->setHayPieza(false); //Se borra la prueba de que habia una ficha en la casilla.
            casilla->setColorPieza("NONE"); //Se quita el color de ficha que estaba
            casilla->currentPiece = NULL; //Se quita la pieza
            if(i < 2) { //En la primera y segunda fila se añadirán las piezas negras

                casilla->setPieza(negras[n]); //Se guarda la posición de la pieza "n" y sus datos en la casilla
                negras[n]->setLugar(true); //Se actualizan los datos
                negras[n]->firstMove = true;
                game->pVivas.append(negras[n++]); //Se inserta la pieza "n" en la QList

            }
            if(i > 5) {

                casilla->setPieza(blancas[b]); //Se guarda la posición de la pieza "b" y sus datos en la casilla
                blancas[b]->setLugar(true); //Se actualizan los datos
                blancas[b]->firstMove = true;
                game->pVivas.append(blancas[b++]); //Se inserta la pieza "b" en la QList


            }

        }
    }
}

#include "juego.h"
#include "button.h"
#include <QPixmap>
#include "rey.h"
#include <QDebug>
Juego::Juego(QWidget *parent ):QGraphicsView(parent)
{

    //Escena
    escena = new QGraphicsScene();
    escena->setSceneRect(0,0,1400,900); //Posición de Escena, Derecha, Abajo, Izquierda y Arriba

    //Vista
    setFixedSize(1400,900); //Tamaño
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Barra de desplazamiento Horizontal Apagada
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Barra de desplazamiento Vertical Apagada
    setScene(escena);//Colocar la Escena
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray); //Color en espacio vacio
    setBackgroundBrush(brush);
    pieceToMove = NULL; //Ninguna pieza a mover

    //Texto Turno
    turno = new QGraphicsTextItem();
    turno->setPos(width()/2-220,5); //Posición X Y
    turno->setDefaultTextColor(Qt::magenta); //Color
    turno->setFont(QFont("Impact",25)); //Fuente y Tamaño
    turno->setPlainText("Turno del BLANCO"); //Contexto

    //Texto Haque
    haque = new QGraphicsTextItem();
    haque->setPos(width()/2+100,3);  //Posición X Y
    haque->setDefaultTextColor(Qt::yellow); //Color Texto
    haque->setFont(QFont("Impact",30)); //Fuente y Tamaño
    haque->setPlainText("HAQUE MATE"); //Contexto
    haque->setVisible(false); //Oculto
    setTurno("Blanco"); //Colocar turno de Blancos

}

void Juego::drawChessBoard()
{
    tablero = new Board();
    tablaComida(0,0,Qt::gray); //Posición y Color de Caja Fichas comidas del lado de los Blancos
    tablaComida(1100,0,Qt::gray); //Posición y Color de Caja Fichas comidas del lado de los Negras
    tablero->tablero(width()/2-400,50); //Posición del Tablero
}
//Metodo actualizar Fichas Blancas Comidas
void Juego::blancaComida()
{
    int pos = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = comidasB.size(); i<n; i++) {
            if(j == 4){ //A cada cuarta ficha en una fila
                k++; //Baja una fila
                j = 0;
            }
            comidasB[i]->setPos(40+pos*j++,100+pos*2*k); //Posición en la que se verá la ficha
    }
}
//Metodo actualizar Fichas Negras Comidas
void Juego::negraComida()
{
    int pos = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = comidasN.size(); i<n; i++) {
        if(j == 4){ //A cada cuarta ficha en una fila
            k++;  //Baja una fila
            j = 0;
        }
        comidasN[i]->setPos(1140+pos*j++,100+pos*2*k); //Posición en la que se verá la ficha
    }
}
//Método de Comer Pieza
void Juego::fichaComida(Pieza *piece)
{
    if(piece->getSide() == "WHITE") { //Si la pieza es blanca
        comidasB.append(piece); //En la Lista de Fichas Blancas Comidas se guarda
        Rey *g = dynamic_cast <Rey *>(piece); //Si la ficha era el rey
        if(g){

            haque->setPlainText("Equipo Negro Gana"); //Las fichas Negras ganan
            gameOver(); //Fin del Juego
        }
        blancaComida(); //Método para actualizar las fichas comidas en la vista
    }
    else{  //Si la pieza era negra
        comidasN.append(piece); //En la Lista de Fichas Negras Comidas se guarda
        Rey *g = dynamic_cast <Rey *>(piece);  //Si la ficha era el rey
        if(g){

            haque->setPlainText("Equipo Blanco Gana"); //Las fichas Blancas ganan
            gameOver(); //Fin del juego
        }
        negraComida(); //Método para actualizar las fichas comidas en la vista
    }
    alivePiece.removeAll(piece); //Remover de las fichas vivas la comida
}

void Juego::addToScene(QGraphicsItem *item)
{
    escena->addItem(item); //Añadir item a la Escena
}

void Juego::removeFromScene(QGraphicsItem *item)
{
    escena->removeItem(item); //Remover item de la Escena

}

QString Juego::getTurno() //Mostrar Turno
{
    return turn;
}

void Juego::setTurno(QString value) //Cambiar Turno
{
    turn = value;
}

void Juego::changeTurn() //Cambio de Turno
{
    if(getTurno() == "Blanco") //Del turno blanco al del negro
        setTurno("Negro");
    else
        setTurno("Blanco"); //Sino del negro al blanco
    turno->setPlainText("Turno del " + getTurno()); //Actualiza el texto a segun el turno

}
//Método de Inicio
void Juego::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++) //Remover de la escena los items
        removeFromScene(listG[i]);

    addToScene(turno); //Añadir Texto turno
    addToScene(haque); //Añadir Texto Haque
    QGraphicsTextItem* reyBlanco = new QGraphicsTextItem(); //Rey Blanco Item Vista
    reyBlanco->setPos(70,10); //Posición
    reyBlanco->setDefaultTextColor(Qt::white); //Color Texto
    reyBlanco->setFont(QFont("Impact",50)); //Estilo Tamaño
    reyBlanco->setPlainText("L"); //Contexto
    addToScene(reyBlanco);  //Añadir a Escena
    QGraphicsTextItem* reyNegro = new QGraphicsTextItem(); //Rey Negro Item Vista
    reyNegro->setPos(1170,10); //Posición
    reyNegro->setDefaultTextColor(Qt::black); //Color Texto
    reyNegro->setFont(QFont("Impact",50)); //Estilo Tamaño
    reyNegro->setPlainText("Kira"); //Contexto
    addToScene(reyNegro); //Añadir a Escena
    tablero->agregarPieza(); //Agregar las Piezas al Tablero
}
//Menú de Inicio
void Juego::menu()
{
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem();
    p->setPixmap(QPixmap(":/images/rey1.png")); //Muestra al Rey Blanco
    p->setPos(420,170); //Posición
    addToScene(p);//Añadir
    listG.append(p);//Añadir lista de item

    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/images/rey.png")); //Muestra al Rey Negro
    p1->setPos(920,170); //Posición
    addToScene(p1);//Añadir
    listG.append(p1);//Añadir lista de item

    //Titulo
    QGraphicsTextItem *titleText = new QGraphicsTextItem("--Ajedrez--");
    QFont titleFont("Impact" , 50); //Fuente y Tamaño
    titleText->setFont( titleFont); //Actualizar
    int xPos = width()/2 - titleText->boundingRect().width()/2; //Posición X
    int yPos = 150;//Posición Y
    titleText->setPos(xPos,yPos);
    addToScene(titleText);//Añadir
    listG.append(titleText);//Añadir lista de item

    //Botón De Inicio
    Button * playButton = new Button("Jugar");
    int pxPos = width()/2 - playButton->boundingRect().width()/2; //Posición X
    int pyPos = 400; //Posición Y
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start())); //Señal al dar click de iniciar
    addToScene(playButton); //Añadir a la escena
    listG.append(playButton); //Añadir lista de item

    //Botón Salida
    Button * quitButton = new Button("Salir");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2; //Posición X
    int qyPos = 550; //Posición Y
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close())); //Señal al dar click de cerrar
    addToScene(quitButton); //Añadir a la escena
    drawChessBoard(); //Dibujar el tablero de fondo sin piezas
    listG.append(quitButton); //Añadir lista de item
}
//Método Fichas Comida
void Juego::tablaComida(int x, int y,QColor color)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900); //Medidas del Grafico Posicion
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color); //Color
    deadHolder->setBrush(brush);
    addToScene(deadHolder); //Añadir a la Escena
}



//Método del Fin del Juego
void Juego::gameOver()
{
    removeAll();
    setTurno("Blanco");
    alivePiece.clear();
    tablero->reset();
    //Titulo
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Fin del Juego");
    QFont titleFont("Impact" , 50); //Fuente y Tamaño
    titleText->setFont( titleFont); //Actualizar
    int xPos = width()/2 - titleText->boundingRect().width()/2; //Posición X
    int yPos = 200;//Posición Y
    titleText->setPos(xPos,yPos);
    addToScene(titleText);//Añadir
    listG.append(titleText);//Añadir lista de item


    //Botón De Inicio
    Button * playButton = new Button("Reiniciar");
    int pxPos = width()/2 - playButton->boundingRect().width()/2; //Posición X
    int pyPos = 350; //Posición Y
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start())); //Señal al dar click de iniciar
    addToScene(playButton); //Añadir a la escena
    listG.append(playButton); //Añadir lista de item

    //Botón Salida
    Button * quitButton = new Button("Salir");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2; //Posición X
    int qyPos = 450; //Posición Y
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close())); //Señal al dar click de cerrar
    addToScene(quitButton); //Añadir a la escena
    drawChessBoard(); //Dibujar el tablero de fondo sin piezas
    listG.append(quitButton); //Añadir lista de item




}
//Método para remover todos los items graficos
void Juego::removeAll(){
    QList<QGraphicsItem*> itemsList = escena->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=haque)
          removeFromScene(itemsList[i]);
    }
}

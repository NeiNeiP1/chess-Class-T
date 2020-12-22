#include "juego.h"
#include "button.h"
#include <QPixmap>
#include "rey.h"
#include <QDebug>
#include<QTimer>
#include<unistd.h>
#include<QTimeLine>
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
    pieza = NULL; //Ninguna pieza a mover

    //Texto Turno
    turno = new QGraphicsTextItem();
    turno->setPos(width()/2-220,5); //Posición X Y
    turno->setDefaultTextColor(Qt::magenta); //Color
    turno->setFont(QFont("Impact",25)); //Fuente y Tamaño
    turno->setPlainText("Turno del BLANCO"); //Contexto


    setTurno("Blanco"); //Colocar turno de Blancos

}

void Juego::dibujarTablero()
{
    tabla = new Board();
    tablaComida(0,0,Qt::gray); //Posición y Color de Caja Fichas comidas del lado de los Blancos
    tablaComida(1100,0,Qt::gray); //Posición y Color de Caja Fichas comidas del lado de los Negras
    tabla->tablero(width()/2-400,50); //Posición del Tablero
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
void Juego::registrarB(QString letra){
    registroB.append(letra);
    int y=480;
    int x=0;
    for(size_t i=0,n=registroB.size();i<n;i++){
        QGraphicsTextItem* r=new QGraphicsTextItem();
        r->setPlainText(registroB[i]);
        QString asc=registroB[i];
        if(i%4==0){
            y=y+20;
            x=0;
        }
        r->setPos(width()/2+500+(x*50),y);
        r->setFont(QFont("Impact",15));
        addToScene(r);
        x++;
    }

}
void Juego::registrarN(QString letra){
    registroN.append(letra);
    int y=480;
    int x=0;
    for(size_t i=0,n=registroN.size();i<n;i++){
        QGraphicsTextItem* r=new QGraphicsTextItem();
        r->setPlainText(registroN[i]);
        if(i%4==0){
            y=y+20;
            x=0;
        }
        r->setPos(width()/2-650+(x*50),y);
        r->setFont(QFont("Impact",15));
        addToScene(r);
        x++;
    }
}
void Juego::registrar(QString letra, QString team){
    if(team=="Blanco"){
        registrarB(letra);
    }
    else{
        registrarN(letra);
    }
}
//Método de Comer Pieza
void Juego::fichaComida(Pieza *piece)
{
    if(piece->getEquipo() == "Blanco") { //Si la pieza es blanca
        comidasB.append(piece); //En la Lista de Fichas Blancas Comidas se guarda
        Rey *g = dynamic_cast <Rey *>(piece); //Si la ficha era el rey
        if(g){

            haque->setPlainText("Equipo Negro Gana"); //Las fichas Negras ganan
            gameOver(0); //Fin del Juego
        }
        blancaComida(); //Método para actualizar las fichas comidas en la vista
    }
    else{  //Si la pieza era negra
        comidasN.append(piece); //En la Lista de Fichas Negras Comidas se guarda
        Rey *g = dynamic_cast <Rey *>(piece);  //Si la ficha era el rey
        if(g){

            haque->setPlainText("Equipo Blanco Gana"); //Las fichas Blancas ganan
            gameOver(1); //Fin del juego
        }
        negraComida(); //Método para actualizar las fichas comidas en la vista
    }
    pVivas.removeAll(piece); //Remover de las fichas vivas la comida
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
    if(getTurno() == "Blanco"){ //Del turno blanco al del negro
        setTurno("Negro");
        star->setPos(230,10); //Posición
        cronometro2->start(1000);
        cronometro->stop();
    }
    else{
        setTurno("Blanco"); //Sino del negro al blanco
        star->setPos(1300,10); //Posición
        cronometro2->stop();
        cronometro->start(1000);

    }
    turno->setPlainText("Turno del " + getTurno()); //Actualiza el texto a segun el turno

}
//Método de Inicio
void Juego::start()
{

    for(size_t i =0, n = listG.size(); i < n; i++) //Remover de la escena los items
        removeFromScene(listG[i]);
    //Texto Haque
    haque = new QGraphicsTextItem();
    haque->setPos(width()/2+100,3);  //Posición X Y
    haque->setDefaultTextColor(Qt::yellow); //Color Texto
    haque->setFont(QFont("Impact",30)); //Fuente y Tamaño
    haque->setPlainText("HAQUE MATE"); //Contexto
    haque->setVisible(false); //Oculto
    addToScene(haque); //Añadir Texto Haque
    QGraphicsTextItem* reyBlanco = new QGraphicsTextItem(); //Rey Blanco Item Vista
    reyBlanco->setPos(70,10); //Posición
    reyBlanco->setDefaultTextColor(Qt::black); //Color Texto
    reyBlanco->setFont(QFont("Impact",30)); //Estilo Tamaño
    reyBlanco->setPlainText("NEGROS"); //Contexto
    addToScene(reyBlanco);  //Añadir a Escena
    QGraphicsTextItem* reyNegro = new QGraphicsTextItem(); //Rey Negro Item Vista
    reyNegro->setPos(1170,10); //Posición
    reyNegro->setDefaultTextColor(Qt::white); //Color Texto
    reyNegro->setFont(QFont("Impact",30)); //Estilo Tamaño
    reyNegro->setPlainText("BLANCOS"); //Contexto
    addToScene(reyNegro); //Añadir a Escena
    tabla->agregarPieza(); //Agregar las Piezas al Tablero
    star= new QGraphicsPixmapItem();
    star->setPixmap(QPixmap(":/images/star.png")); //Muestra al Rey Blanco
    star->setPos(1300,10); //Posición
    addToScene(star);//Añadir
    //Botón De Renuncia Blanco
    Button * playButton = new Button("Rendirse");
    int pxPos = width()/2 - playButton->boundingRect().width()/2-550; //Posición X
    int pyPos = 850; //Posición Y
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(renunciaB())); //Señal al dar click de iniciar
    addToScene(playButton); //Añadir a la escena
    listG.append(playButton); //Añadir lista de item
    //Botón De Renuncia Blanco
    Button * playButton2 = new Button("Rendirse");
    pxPos = width()/2 - playButton->boundingRect().width()/2+550; //Posición X
    pyPos = 850; //Posición Y
    playButton2->setPos(pxPos,pyPos);
    connect(playButton2,SIGNAL(clicked()) , this , SLOT(renunciaN())); //Señal al dar click de iniciar
    addToScene(playButton2); //Añadir a la escena
    listG.append(playButton2); //Añadir lista de item
    cron1->setPlainText("00:00");
    cron2->setPlainText("00:00");
    addToScene(cron1);
    cron1->setPos(width()/2+500,790);
    cron1->setFont(QFont("Impact",20));
    addToScene(cron2);
    cron2->setPos(width()/2-600,790);
    cron2->setFont(QFont("Impact",20));
    cronometro=new QTimer(this);
    cronometro2=new QTimer(this);
    connect(cronometro, SIGNAL(timeout()), this, SLOT(activarTiempo()));
    connect(cronometro2, SIGNAL(timeout()), this, SLOT(activarTiempo2()));
    cronometro->start(1000);

}
void Juego::activarTiempo(){
    QString s;
    QString m;
    if(comidasB.size()>14&&comidasN.size()>14){
        contador++;
    }
    if(seg1==59){
        if(min1+1==3){
            min1=3;
            seg1=0;
            renunciaB();
        }
        else
            min1++;
        seg1=0;
    }
    else
        seg1++;
    s.setNum(seg1);
    m.setNum(min1);
    if(seg1<10){
        s.prepend("0");
    }
    if(min1<10){
        m.prepend("0");
    }
    cron1->setPlainText(m+":"+s);
    cron1->setPos(width()/2+500,790);
    cron1->setFont(QFont("Impact",20));
    addToScene(cron1);
}
void Juego::activarTiempo2(){
    QString s;
    QString m;
    if(comidasB.size()>14&&comidasN.size()>14){
        contador++;
        if(contador==30){
            gameOver(2);
        }
    }
    if(seg2==59){
        if(min2+1==3){

            min2=3;
            seg2=0;
            renunciaN();
        }
        else
            min2++;
        seg2=0;
    }
    else
        seg2++;
    s.setNum(seg2);
    m.setNum(min2);
    if(seg2<10){
        s.prepend("0");
    }
    if(min2<10){
        m.prepend("0");
    }
    cron2->setPlainText(m+":"+s);
    cron2->setPos(width()/2-600,790);
    cron2->setFont(QFont("Impact",20));
    addToScene(cron2);
}
void Juego::renunciaB(){
    haque->setPlainText("Equipo Negro Gana"); //Las fichas Negras ganan
    gameOver(1);
}
void Juego::renunciaN(){
    haque->setPlainText("Equipo Blanco Gana"); //Las fichas Negras ganan
    gameOver(0);
}

//Menú de Inicio
void Juego::menu()
{

    QGraphicsPixmapItem *star2 = new QGraphicsPixmapItem();
    star2->setPixmap(QPixmap(":/images/star.png")); //Muestra al Rey Blanco
    star2->setPos(670,100); //Posición
    addToScene(star2);//Añadir
    listG.append(star2);//Añadir lista de item

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
    dibujarTablero(); //Dibujar el tablero de fondo sin piezas
    listG.append(quitButton); //Añadir lista de item
    QGraphicsTextItem* letra= new QGraphicsTextItem();
    letra->setPlainText(" A           B          C          D          E          F          G          H");
    letra->setPos(width()/2-370,5); //Se coloca la posición con shift
    letra->setFont(QFont("Arial",20));
    addToScene(letra); //Se añade a la vista
    QGraphicsTextItem* letra2= new QGraphicsTextItem();
    letra2->setPlainText(" A           B          C          D          E          F          G          H");
    letra2->setPos(width()/2-370,850); //Se coloca la posición con shift
    letra2->setFont(QFont("Arial",20));
    addToScene(letra2); //Se añade a la vista
}
//Método Fichas Comida
void Juego::tablaComida(int x, int y,QColor color)
{
    muerto = new QGraphicsRectItem(x,y,300,900); //Medidas del Grafico Posicion
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color); //Color
    muerto->setBrush(brush);
    addToScene(muerto); //Añadir a la Escena
}



//Método del Fin del Juego
void Juego::gameOver(int i)
{
    cronometro->stop();
    cronometro2->stop();
    seg1=0;
    seg2=0;
    min1=0;
    min2=0;
    QGraphicsTextItem *text=haque;
    removeAll();
    setTurno("Blanco");
    pVivas.clear();
    registroB.clear();
    registroN.clear();
    tabla->reset();

    addToScene(text);
    //Titulo
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Fin del Juego");
    if(i==1){
        titleText->setPlainText("Blancos Ganan");
    }
    else if(i==0){
        titleText->setPlainText("Negros Ganan");
    }
    else{
        titleText->setPlainText("Empate");
    }
    QFont titleFont("Impact" , 50); //Fuente y Tamaño
    titleText->setFont( titleFont); //Actualizar
    int xPos = width()/2 - titleText->boundingRect().width()/2; //Posición X
    int yPos = 200;//Posición Y
    titleText->setPos(xPos,yPos);
    addToScene(titleText);//Añadir
    listG.append(titleText);//Añadir lista de item
    haque=text;
    addToScene(haque);
    listG.append(haque);
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
    dibujarTablero(); //Dibujar el tablero de fondo sin piezas
    listG.append(quitButton); //Añadir lista de item
    QGraphicsTextItem* letra= new QGraphicsTextItem();
    letra->setPlainText(" A           B          C          D          E          F          G          H");
    letra->setPos(width()/2-370,5); //Se coloca la posición con shift
    letra->setFont(QFont("Arial",20));
    addToScene(letra); //Se añade a la vista
    QGraphicsTextItem* letra2= new QGraphicsTextItem();
    letra2->setPlainText(" A           B          C          D          E          F          G          H");
    letra2->setPos(width()/2-370,850); //Se coloca la posición con shift
    letra2->setFont(QFont("Arial",20));
    addToScene(letra2); //Se añade a la vista



}

//Método para remover todos los items graficos
void Juego::removeAll(){
    QList<QGraphicsItem*> itemsList = escena->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=haque)
          removeFromScene(itemsList[i]);
    }
}

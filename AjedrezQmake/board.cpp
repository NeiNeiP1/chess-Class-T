#include "board.h"
#include "ui_board.h"
#include "QMimeData"

Board::Board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    BoardIcon.load(""); //Enlace de imagen
    fichas = std::make_unique<Pieza>(this);

    fichas->move(50,50);
    fichas->show();
}

Board::~Board()
{
    delete ui;
}
void Board::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,width(),height(),BoardIcon);
}
void Board::mousePressEvent(QMouseEvent *event){
    auto child = childAt(event->pos());
    if(child==nullptr){
        std::cout<<"null\n";
        return;
    }
    std::cout<<"child\n";
    QByteArray data;
    QDataStream dataStream (&data,QIODevice::WriteOnly);
    dataStream <<QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData();
    mimeData->setData("application/x-dnditemdata",data);

    QDrag * drag= new QDrag(this);
    drag->setMimeData(mimeData);
    drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);

}

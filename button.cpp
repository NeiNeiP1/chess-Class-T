#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>
Button::Button(QString name, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    setRect(0,0,200,50); //Medidas del Botón
    QBrush brush; //Contenido del Botón
    brush.setStyle(Qt::SolidPattern); //Estilo
    brush.setColor(Qt::blue); //Color
    setBrush(brush);
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2-4; //Posición X
    int yPos = rect().height()/2 - text->boundingRect().height()/2-4; //Posición Y
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white); //Texto del Botón
    text->setFont(QFont("Impact",15));
    setAcceptHoverEvents(true); //Cambia a permitir eventos de desplazamiento
}
//Reacción al ser Presionado por Mouse
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    emit clicked();

}
//Reacción al ser apuntado por Mouse
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkBlue); //Cambia el color mientras es apuntado
    setBrush(brush);
    }
}
//Reacción al dejar de ser apuntado por Mouse
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {

    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue); //Cambia el color al ya no ser apuntado
    setBrush(brush);
    }
}

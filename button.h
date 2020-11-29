#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>


class Button:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
private:
    QGraphicsTextItem *text; //Texto del Botón
public:
//Métodos Publicos
    Button(QString name, QGraphicsItem * parent = NULL);
    //Evento
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked(); //Señal

};
#endif // BUTTON_H

#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <memory>
#include <pieza.h>
#include <iostream>
#include <QtWidgets>
namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

    void paintEvent(QPaintEvent *event) override;

private:
    Ui::Board *ui;
    QPixmap BoardIcon;
    std:: unique_ptr<Pieza> fichas;

    void mousePressEvent(QMouseEvent *event) override;

};

#endif // BOARD_H

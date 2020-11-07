#ifndef QUEEN_H
#define QUEEN_H

#include <QLabel>
#include <QPixmap>
#include "pieza.h"
class Queen : public Pieza
{
public:
    explicit Queen(QWidget *parent= nullptr);
};

#endif // QUEEN_H

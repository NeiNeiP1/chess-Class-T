#ifndef PIEZA_H
#define PIEZA_H
#include <QLabel>
#include <QPixmap>
namespace ui{
class Pieza;
}
class Pieza : public QLabel
{
    Q_OBJECT
public:
    explicit Pieza(QWidget *parent =nullptr);
    virtual ~Pieza(){};

protected:
    ui::Pieza *ui;
    QPixmap PiezaIcon;
};

#endif // PIEZA_H

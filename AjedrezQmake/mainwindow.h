#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QHash>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void definirResultadoFinal();
    QMessageBox msgBox;
    void Iniciar();
    QVector<QString> casillas{"1A","1B","1C","1D","1E","1F","1G","1H",
                             "2A","2B","2C","2D","2E","2F","2G","2H",
                              "3A","3B","3C","3D","3E","3F","3G","3H",
                              "4A","4B","4C","4D","4E","4F","4G","4H",
                              "5A","5B","5C","5D","5E","5F","5G","5H",
                              "6A","6B","6C","6D","6E","6F","6G","6H",
                              "7A","7B","7C","7D","7E","7F","7G","7H",
                              "8A","8B","8C","8D","8E","8F","8G","8H",
                             };
    QPushButton* botones;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

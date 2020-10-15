#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Iniciar();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::definirResultadoFinal(){
    msgBox.setWindowTitle("Juego Terminado");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);
    msgBox.setText("Partida Inconclusa");
    if(QMessageBox::Yes==msgBox.exec()){
        Iniciar();
    }
    else{
        QCoreApplication::quit();
    }
}
void MainWindow::Iniciar(){

}

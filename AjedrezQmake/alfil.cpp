#include "alfil.h"
#include <QDebug>
#include "juego.h"
extern Juego *game;
Alfil::Alfil(QString team, QGraphicsItem *parent):Pieza(team,parent)
{
    setImage();
}
void Alfil::setImage(){
    if(equipo=="Blanco")
        setPixmap(QPixmap(":/images/alfil1.png"));
    else
        setPixmap(QPixmap(":/images/alfil.png"));
}
void Alfil::moves(){
    location.clear();
    int row =this->getCasilla()->rowLoc;
    int col=this->getCasilla()->colLoc;
    QString team=this->getEquipo();
    for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--){ //Para Diagonal Noroeste
        if(game->caja[i][j]->getColorPieza() == team ){
            //Si hay una pieza aliada se detiene y no registra
            break;
        }
        else{
            //Guarda que la casilla es disponible
            location.append(game->caja[i][j]);
            //Si en la ultima posición habia una ficha se detiene
            if(boxSetting(location.last())){
                break;
            }
        }
   }
     for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {//Para Diagonal Noreste
         if(game->caja[i][j]->getColorPieza() == team ){
             //Si hay una pieza aliada se detiene y no registra
             break;
         }
         else{
             //Guarda que la casilla es disponible
             location.append(game->caja[i][j]);
             //Si en la ultima posición habia una ficha se detiene
             if(boxSetting(location.last())){
                 break;
             }
         }
    }
      for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) { //Para Diagonal Sureste
          if(game->caja[i][j]->getColorPieza() == team ){
              //Si hay una pieza aliada se detiene y no registra
              break;
          }
          else{
              //Guarda que la casilla es disponible
              location.append(game->caja[i][j]);
              //Si en la ultima posición habia una ficha se detiene
              if(boxSetting(location.last())){
                  break;
              }
          }
     }
       for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--){ //Para Diagonal Suroeste
           if(game->caja[i][j]->getColorPieza() == team ){
               //Si hay una pieza aliada se detiene y no registra
               break;
           }
           else{
               //Guarda que la casilla es disponible
               location.append(game->caja[i][j]);
               //Si en la ultima posición habia una ficha se detiene
               if(boxSetting(location.last())){
                   break;
               }
           }
      }
}

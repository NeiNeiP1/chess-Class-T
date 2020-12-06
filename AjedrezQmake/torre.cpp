#include "torre.h"
#include "juego.h"
extern Juego *game;
Torre::Torre(QString team, QGraphicsItem *parent):Pieza(team,parent)
{
    setImage();
}
void Torre::setImage(){
    if(equipo=="Blanco")
        setPixmap(QPixmap(":/images/torre1.png"));
    else
        setPixmap(QPixmap(":/images/torre.png"));
}
void Torre::moves(){
    location.clear();
    int row = this->getCasilla()->rowLoc;
    int col = this->getCasilla()->colLoc;
    QString team = this->getEquipo();
    for(int i = row,j = col-1; j >= 0 ; j--){ //Para la Izquierda
        if(game->caja[i][j]->getColorPieza() == team ) {
            //Si hay una pieza aliada se detiene y no registra
            break;
        }
        else{
            //Guarda que la casilla es disponible
            location.append(game->caja[i][j]);
             //Si en la ultima posición habia una ficha se detiene
            if(boxSetting(location.last()))
                break;
         }
     }
     for(int i = row,j = col+1; j <= 7 ; j++){ //Para la Derecha
         if(game->caja[i][j]->getColorPieza() == team ) {
             //Si hay una pieza aliada se detiene y no registra
             break;
         }
         else{
             //Guarda que la casilla es disponible
             location.append(game->caja[i][j]);
              //Si en la ultima posición habia una ficha se detiene
             if(boxSetting(location.last()))
                 break;
          }

     }
      for(int i = row-1,j = col; i >= 0 ; i--) { //Para arriba
        if(game->caja[i][j]->getColorPieza() == team ) {
            //Si hay una pieza aliada se detiene y no registra
            break;
        }
        else{
            //Guarda que la casilla es disponible
            location.append(game->caja[i][j]);
             //Si en la ultima posición habia una ficha se detiene
            if(boxSetting(location.last()))
                break;
         }
     }
       for(int i = row+1,j = col; i <= 7 ; i++) { //Para abajo
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


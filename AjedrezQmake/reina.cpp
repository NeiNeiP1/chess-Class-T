#include "reina.h"
#include "juego.h"
extern Juego *game;
Reina::Reina(QString team,QGraphicsItem *parent):Pieza(team,parent)
{
    setImage();
}

void Reina::setImage()
{
    if(equipo == "Blanco")
        setPixmap(QPixmap(":/images/reina1.png"));
    else
        setPixmap(QPixmap(":/images/reina.png"));
}
void Reina::moves()
{ //Actualizar Casillas a donde puede ir
    location.clear();
    int row = this->getCasilla()->filaLoc; //Fila
    int col = this->getCasilla()->colLoc; //Columna de Donde está
    QString team = this->getEquipo();//El equipo en donde está
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

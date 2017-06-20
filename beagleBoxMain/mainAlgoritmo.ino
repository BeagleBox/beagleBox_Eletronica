
//===========================================================================
//Constantes
//===========================================================================

#define linhas 8
#define colunas 8
//===========================================================================
//Variaveis 
//===========================================================================
int numeroDaRota;
int roboI;
int roboJ;

int mapa[linhas][colunas] = {{0,0,0,0,0,0,0},
                             {0,5,4,3,2,1,0},
                             {0,6,5,4,3,2,0},
                             {0,7,6,5,4,3,0},
                             {0,8,7,0,0,0,0},
                             {0,9,8,0,0,0,0},
                             {0,255,9,0,0,0,0},
                             {0,0,0,0,0,0,0}};

//===========================================================================
//Funções
//===========================================================================                 
void rosaDosVentos(){
  if(bussola > -1 && bussola < 1){orientacao = 'N';}
  else if(bussola > 89 && bussola < 91){orientacao = 'L';}
  else if((bussola > 179 && bussola < 180) || (bussola < -179 && bussola > -180)){orientacao = 'S';}
  else if(bussola < -89 && bussola > -91){orientacao = 'O';}  
}

void calculoNumeroDaRota () {
  for(int i=0; i<linhas;i++){
    for(int j=0; j<colunas; j++){
      if(mapa[i][j] > numeroDaRota && mapa[i][j] > 255) numeroDaRota = mapa[i][j];
    }
  }
}

void posicaoRobo(){
  for(int i=0; i<linhas;i++){
    for(int j=0; j<colunas; j++){
      if(mapa[i][j] == 255) {
        roboI = i; 
        roboJ = j;
        break;
      }
    }
  }
}

void wavefront(){
  switch (orientacao) {
    case 'N':
      if(mapa[roboI-1][roboJ] == numeroDaRota ){
        moverParaFrente();
        roboI = roboI-1;
      }
      else if(mapa[roboI][roboJ+1] == numeroDaRota){
        girar('D','L');
        moverParaFrente();
        roboJ = roboJ+1;
      }
      else if(mapa[roboI][roboJ-1] == numeroDaRota){
        girar('E','O');
        moverParaFrente();
        roboJ = roboJ-1;
      }
      else if(mapa[roboI+1][roboJ] == numeroDaRota){
        girar('T','S');
        moverParaFrente();
        roboI = roboI+1;
      }

    break;
    case 'S':
      if(mapa[roboI+1][roboJ] == numeroDaRota ){
        moverParaFrente();
        roboI = roboI+1;
      }
      else if(mapa[roboI][roboJ-1] == numeroDaRota){
        girar('D','O');
        moverParaFrente();
        roboJ = roboJ-1;
      }
      else if(mapa[roboI][roboJ+1] == numeroDaRota){
        girar('E','L');
        moverParaFrente();
        roboJ = roboJ+1;
      }
      else if(mapa[roboI+1][roboJ] == numeroDaRota){
        girar('T','N');
        moverParaFrente();
        roboI = roboI+1;
      }

    break;
    case 'L':
      if(mapa[roboI][roboJ+1] == numeroDaRota ){
        moverParaFrente();
        roboJ = roboJ+1;
      }
      else if(mapa[roboI+1][roboJ] == numeroDaRota){
        girar('D','S');
        moverParaFrente();
        roboI = roboI+1;
      }
      else if(mapa[roboI-1][roboJ] == numeroDaRota){
        girar('E','N');
        moverParaFrente();
        roboI = roboI-1;
      }
      else if(mapa[roboI][roboJ-1] == numeroDaRota){
        girar('T','S');
        moverParaFrente();
        roboJ = roboJ-1;
      }

    break;
    case 'O':
      if(mapa[roboI][roboJ-1] == numeroDaRota ){
        moverParaFrente();
        roboJ = roboJ-1;
      }
      else if(mapa[roboI-1][roboJ] == numeroDaRota){
        girar('D','N');
        moverParaFrente();
        roboI = roboI-1;
      }
      else if(mapa[roboI+1][roboJ] == numeroDaRota){
        girar('E','S');
        moverParaFrente();
        roboI = roboI+1;
      }
      else if(mapa[roboI][roboJ+1] == numeroDaRota){
        girar('T','L');
        moverParaFrente();
        roboJ = roboJ+1;
      }

    break;

  }
  
  numeroDaRota--; 
}


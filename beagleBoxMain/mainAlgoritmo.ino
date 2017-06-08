
//===========================================================================
//Definições
//===========================================================================

//===========================================================================
//Variaveis 
//===========================================================================

int mapa[8][8] = {{0,0,0,0,0,0,0},
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
/*
void Wavefront(){
  switch (orientacao) {
    case 'N':
      if(mapa[i-1][j] == numeroDaRota ){
        moverParaFrente();
      }
      else if(mapa[i][j+1] == numeroDaRota){
        girar(D);
        orientacao = 'L';
        moverParaFrente();
      }
      else if(mapa[i][j-1] == numeroDaRota){
        girar(E);
        orientacao = 'O';
        moverParaFrente();
      }
      else if(mapa[i+1][j] == numeroDaRota){
        girar(T);
        orientacao = 'S';
        moverParaFrente();
      }

    break;
    case 'S':
      if(mapa[i+1][j] == numeroDaRota ){
        moverParaFrente();
      }
      else if(mapa[i][j-1] == numeroDaRota){
        girar(D);
        orientacao = 'O';
        moverParaFrente();
      }
      else if(mapa[i][j+1] == numeroDaRota){
        girar(E);
        orientacao = 'L';
        moverParaFrente();
      }
      else if(mapa[i+1][j] == numeroDaRota){
        girar(T);
        orientacao = 'N';
        moverParaFrente();
      }

    break;
    case 'L':
      if(mapa[i][j+1] == numeroDaRota ){
        moverParaFrente();
      }
      else if(mapa[i+1][j] == numeroDaRota){
        girar(D);
        orientacao = 'S';
        moverParaFrente();
      }
      else if(mapa[i-1][j] == numeroDaRota){
        girar(E);
        orientacao = 'N';
        moverParaFrente();
      }
      else if(mapa[i][j-1] == numeroDaRota){
        girar(T);
        orientacao = 'S';
        moverParaFrente();
      }

    break;
    case 'O':
      if(mapa[i][j-1] == numeroDaRota ){
        moverParaFrente();
      }
      else if(mapa[i-1][j] == numeroDaRota){
        girar(D);
        orientacao = 'N';
        moverParaFrente();
      }
      else if(mapa[i+1][j] == numeroDaRota){
        girar(E);
        orientacao = 'S';
        moverParaFrente();
      }
      else if(mapa[i][j+1] == numeroDaRota){
        girar(T);
        orientacao = 'L';
        moverParaFrente();
      }

    break;

  }
  
  numeroDaRota--; 
}
*/

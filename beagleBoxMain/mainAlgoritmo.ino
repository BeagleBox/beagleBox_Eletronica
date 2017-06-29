
//===========================================================================
//Constantes
//===========================================================================

#define linhas 8
#define colunas 8
#define distanciaMinimaUltrassom 3
#define distanciaMaximaUltrassom 50
#define tempoDeEspera 3000
#define comprimentoQuadrado 20

//===========================================================================
//Variaveis
//===========================================================================
int numeroDaRota;
float distancia = 0;
bool flag = true;
bool flagObstaculo = false;
unsigned long esperaTimer = 0;
// int posi = 6;
// int posj = 1;

int mapa[linhas][colunas] = {
  {0, 0, 0, 0, 0, 0, 0},
  {0, 5, 4, 3, 2, 1, 0},
  {0, 6, 5, 4, 3, 2, 0},
  {0, 0, 6, 5, 4, 3, 0},
  {0, 8, 7, 0, 0, 0, 0},
  {0, 9, 8, 0, 0, 0, 0},
  {0, 10, 9, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0}
};

//===========================================================================
//Funções
//===========================================================================

//Converte os valores da bussola para direções conhecidas
void rosaDosVentos() {
  if (bussola > -1 && bussola < 1) {
    orientacao = 'N';
  }
  else if (bussola > 89 && bussola < 91) {
    orientacao = 'L';
  }
  else if ((bussola > 179 && bussola < 180) || (bussola < -179 && bussola > -180)) {
    orientacao = 'S';
  }
  else if (bussola < -89 && bussola > -91) {
    orientacao = 'O';
  }
  /*
    IDEIA PARA AJUSTAR AS EVENTUAIS MUNDANÇAS DE DIREÇÃO E CORRIGI-LAS

    else{
    orientacao = 'IDLE';
    }*/
}

//Calcula o menor numero da redondeza do robo para que ele siga o caminho
void calculoNumeroDaRota () {
  
  numeroDaRota = 30000;
  
  if(mapa[roboI+1][roboJ] < numeroDaRota && mapa[roboI+1][roboJ] != 0){numeroDaRota = mapa[roboI+1][roboJ];}
  if(mapa[roboI-1][roboJ] < numeroDaRota && mapa[roboI-1][roboJ] != 0){numeroDaRota = mapa[roboI-1][roboJ];}
  if(mapa[roboI][roboJ+1] < numeroDaRota && mapa[roboI][roboJ+1] != 0){numeroDaRota = mapa[roboI][roboJ+1];}
  if(mapa[roboI][roboJ-1] < numeroDaRota && mapa[roboI][roboJ-1] != 0){numeroDaRota = mapa[roboI][roboJ-1];}
      
  
}

//Encontra a posição do Robo no mapa
// void posicaoRobo( posi, posj) {

//         roboI = posi;
//         roboJ = posj;
//   // for (int i = 0; i < linhas; i++) {
//   //   for (int j = 0; j < colunas; j++) {
//   //     if (mapa[i][j] == 255) {
//   //       roboI = posi;
//   //       roboJ = posj;
//   //       break;
//   //     }
//   //     if (posi == i && posj == j) {
//   //       mapa[posi][posj] == 255
//   //       mapa[roboI][roboJ]
//   //     }

//   //   }
//   // }
// }



//Faz com que o robo avance uma casa na martiz
void moverParaFrente() {
  if (flag) {
    controle('w');
    distancia = encoder;
    flag = false;
  }
  Serial.print("In: moverParaFrente. \t");
  if (encoder - distancia >= comprimentoQuadrado) {
    controle('s');
    flag = true;
    Serial.print("In: Condição de pausa moverParaFrente  \t");
    switch (orientacao) {
      case 'N':
        roboI = roboI - 1;
        break;
      case 'S':
        roboI = roboI + 1;
        break;
      case 'L':
        roboJ = roboJ + 1;
        break;
      case 'O':
        roboJ = roboJ - 1;
        break;
    calculoNumeroDaRota();
    }
  }
}

//===========================================================================
//Girar o robo
//===========================================================================

void girar(char direcao, char rumo) {
  Serial.print("In: girar \t");
  switch (direcao) {
    case 'DIREITA':
      do {
        controle('d');
        leituraOrientacao();
        rosaDosVentos();
        Serial.println(orientacao);
      } while (orientacao != rumo);
      break;

    case 'ESQUERDA':
      do {
        controle('a');
        leituraOrientacao();
        rosaDosVentos();        
         Serial.println(orientacao);
      } while (orientacao != rumo);
      break;

    case 'MEIAVOLTA':
      do {
        controle('d');
        leituraOrientacao();
        rosaDosVentos();
         Serial.println(orientacao);
      } while (orientacao != rumo);
      break;

  }
}

//===========================================================================
//Algoritmo
//===========================================================================

void rodarWavefront() {
  Serial.print("In: rodarWavefront \t");

  // Checa se o robo chegou ao destino e ordena parada
  if (numeroDaRota < 1) {
    controle('s');
    Serial.print("Cheguei ao destino.");
    while (1);
  }
  // Checa se existe um obstáculo detectado pelos ultrassons.
  else if (ultrassomEsquerda > distanciaMinimaUltrassom &&  ultrassomEsquerda < distanciaMaximaUltrassom  || ultrassomDireita > distanciaMinimaUltrassom && ultrassomDireita < distanciaMaximaUltrassom || ultrassomCentro > distanciaMinimaUltrassom && ultrassomCentro < distanciaMaximaUltrassom) {
    
      Serial.print("In: ultrassom check \t");

    if (flagObstaculo){
      if(millis() - esperaTimer > tempoDeEspera){
          Serial.print("In: esperei 3s \t");

        switch (orientacao) {
          case 'N':
            mapa[roboI-1][roboJ] = 0;
            flagObstaculo = false;
            break;
          case 'S':
            mapa[roboI+1][roboJ] = 0;
            flagObstaculo = false;
            break;
          case 'L':
            mapa[roboI][roboJ+1] = 0;
            flagObstaculo = false;
            break;
          case 'O':
            mapa[roboI][roboJ-1] = 0;
            flagObstaculo = false;
            break;
        }
      //posicaoRobo(roboI,roboJ);
      }
    }
    else{ 
      controle('s');
      flagObstaculo = true;
      esperaTimer = millis(); 
        Serial.print("In: ultrassomCheck primeira passagem\t");

    }
  }
  // Caso não exista obstáculo e o destino não tenha sido alcançado, realiza os movimentos
  if (!flagObstaculo){
      Serial.print("In: wavefront sem obstaculo \t");
    flagObstaculo = false;
    switch (orientacao) {
      case 'N':
        if (mapa[roboI - 1][roboJ] == numeroDaRota ) {
          Serial.print("In: wavefront N frente  \t");
          moverParaFrente();
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          Serial.print("In: wavefront N girar D  \t");
          girar('DIREITA','L');
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('ESQUERDA','O');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('MEIAVOLTA','S');
        }
        break;
      case 'S':
        if (mapa[roboI + 1][roboJ] == numeroDaRota ) {
          moverParaFrente();
          Serial.print("In: wavefront S frente \t");
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('DIREITA','O');
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          girar('ESQUERDA','L');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('MEIAVOLTA','N');
        }
        break;

      case 'L':
        if (mapa[roboI][roboJ + 1] == numeroDaRota ) {
          Serial.print("In: wavefront L frente  \t");
          moverParaFrente();
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('DIREITA','S');
        }
        else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
          girar('ESQUERDA','N');
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('MEIAVOLTA','O');
        }
        break;

      case 'O':
        if (mapa[roboI][roboJ - 1] == numeroDaRota ) {
          Serial.print("In: wavefront O frente \t");
          moverParaFrente();
        }
        else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
          girar('DIREITA','N');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('ESQUERDA','S');
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          girar('MEIAVOLTA','L');
        }
        break;

      default: rosaDosVentos();
    }
  }
}

//===========================================================================
//Setup
//===========================================================================

void setupAlgoritmo() {
  rosaDosVentos();
  calculoNumeroDaRota(); 
  Serial.println(numeroDaRota); 
}



//===========================================================================
//Constantes
//===========================================================================

#define linhas 8
#define colunas 8
#define distanciaMinima 3
#define distanciaMaxima 50
#define tempoDeEspera 1000
#define comprimentoQuadrado 20

//===========================================================================
//Variaveis
//===========================================================================
int numeroDaRota;
float distancia = 0;
bool flag = true;

int mapa[linhas][colunas] = {
  {0, 0, 0, 0, 0, 0, 0},
  {0, 5, 4, 3, 2, 1, 0},
  {0, 6, 5, 4, 3, 2, 0},
  {0, 0, 6, 5, 4, 3, 0},
  {0, 8, 7, 0, 0, 0, 0},
  {0, 9, 8, 0, 0, 0, 0},
  {0, 255, 9, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0}
};

//===========================================================================
//Funções
//===========================================================================

//===========================================================================
//Converte os valores da bussola para direções conhecidas
//===========================================================================
void rosaDosVentos() {
  if (bussola > -1 && bussola < 1) {
    orientacao = 'NORTE';
  }
  else if (bussola > 89 && bussola < 91) {
    orientacao = 'LESTE';
  }
  else if ((bussola > 179 && bussola < 180) || (bussola < -179 && bussola > -180)) {
    orientacao = 'SUL';
  }
  else if (bussola < -89 && bussola > -91) {
    orientacao = 'OESTE';
  }
  /*
    IDEIA PARA AJUSTAR AS EVENTUAIS MUNDANÇAS DE DIREÇÃO E CORRIGI-LAS
  
    else{
    orientacao = 'IDLE';
  }*/
}

//===========================================================================
//Calcula o menor numero da redondeza do robo para que ele siga o caminho
//===========================================================================

void calculoNumeroDaRota () {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (mapa[i][j] > numeroDaRota && mapa[i][j] != 255) numeroDaRota = mapa[i][j];
    }
  }
}

//===========================================================================
//Funções
//===========================================================================

void posicaoRobo() {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (mapa[i][j] == 255) {
        roboI = i;
        roboJ = j;
        break;
      }
    }
  }
}

//===========================================================================
//Mover o robo pra frente
//===========================================================================

void moverParaFrente() {
  if (flag) {
    controle('w');
    distancia = encoderEsquerda;
    flag = false;
  }
  Serial.print("In: moverParaFrente. \t");
  if (encoderEsquerda - distancia >= comprimentoQuadrado){
    controle('s');
    numeroDaRota--;
    flag = true;
    Serial.print("In: Condição de pausa moverParaFrente  \t");
    switch (orientacao) {
      case 'NORTE':
      roboI = roboI - 1;
      break;
      case 'SUL':
      roboI = roboI + 1;
      break;
      case 'LESTE':
      roboJ = roboJ + 1;
      break;
      case 'OESTE':
      roboJ = roboJ - 1;
      break;
    }
  }
}

//===========================================================================
//Girar o robo
//===========================================================================

void girar(char direcao) {
  switch (direcao) {
    case 'DIREITA':
      controle('d');
      Serial.print("In: girar D. \t");
    break;
    case 'ESQUERDA':
      controle('a');
      Serial.print("In: girar E. \t");
    break;
    case 'MEIAVOLTA':
      controle('d');
      Serial.print("In: girar T. \t");
    break;
    default: controle('s');
  }
}

//===========================================================================
//Algoritmo
//===========================================================================

void rodarWavefront() {
  if (numeroDaRota < 1){ 
    controle('s');
    Serial.print("Cheguei ao destino.");
    while(1);
  }
  else if (ultrassomEsquerda > distanciaMinima &&  ultrassomEsquerda < distanciaMaxima  || ultrassomDireita > distanciaMinima && ultrassomDireita < distanciaMaxima || ultrassomCentro > distanciaMinima && ultrassomCentro < distanciaMaxima) {
    controle('s');
    delay(tempoDeEspera);
    if(flag) {
      if(ultrassomDireita <= ultrassomEsquerda) gira('DIREITA');
      else gira('ESQUERDA');
    }
  }
  else {
    rosaDosVentos();
    switch (orientacao) {
      case 'NORTE':
        if (mapa[roboI - 1][roboJ] == numeroDaRota ) {
          Serial.print("In: wavefront N frente  \t");
          moverParaFrente();
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          Serial.print("In: wavefront N girar D  \t");
          girar('DIREITA');
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('ESQUERDA');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('MEIAVOLTA');
        }
        break;
      case 'SUL':
        if (mapa[roboI + 1][roboJ] == numeroDaRota ) {
          moverParaFrente();
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('DIREITA');
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          girar('ESQUERDA');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('MEIAVOLTA');
        }
        break;

      case 'LESTE':
        if (mapa[roboI][roboJ + 1] == numeroDaRota ) {
          Serial.print("In: wavefront L frente  \t");
          moverParaFrente();
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('DIREITA');
        }
        else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
          girar('ESQUERDA');
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('MEIAVOLTA');
        }
        break;

      case 'OESTE':
        if (mapa[roboI][roboJ - 1] == numeroDaRota ) {
          moverParaFrente();
        }
        else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
          girar('DIREITA');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('ESQUERDA');
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          girar('MEIAVOLTA');
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
  posicaoRobo();
}


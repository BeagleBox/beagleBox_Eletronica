
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

//Converte os valores da bussola para direções conhecidas
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

//Calcula o menor numero da redondeza do robo para que ele siga o caminho
void calculoNumeroDaRota () {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      if (mapa[i][j] > numeroDaRota && mapa[i][j] != 255) numeroDaRota = mapa[i][j];
    }
  }
}

//Encontra a posição do Robo no mapa
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

//Faz com que o robo avance uma casa na martiz
void moverParaFrente() {
  if (flag) {
    controle('w');
    distancia = encoderEsquerda;
    flag = false;
  }
  Serial.print("In: moverParaFrente. \t");
  if (encoderEsquerda - distancia >= comprimentoQuadrado) {
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

void girar(char direcao, char rumo) {
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
  // Checa se o robo chegou ao destino e ordena parada
  if (numeroDaRota < 1) {
    controle('s');
    Serial.print("Cheguei ao destino.");
    while (1);
  }
  // Checa se existe um obstáculo detectado pelos ultrassons.
  else if (ultrassomEsquerda > distanciaMinimaUltrassom &&  ultrassomEsquerda < distanciaMaximaUltrassom  || ultrassomDireita > distanciaMinimaUltrassom && ultrassomDireita < distanciaMaximaUltrassom || ultrassomCentro > distanciaMinimaUltrassom && ultrassomCentro < distanciaMaximaUltrassom) {
    
    if (flagObstaculo){
      if(millis() - esperaTimer > tempoDeEspera){
        switch (orientacao) {
          case 'NORTE':
            mapa[roboI-1][roboJ] = 0;
            flagObstaculo = false;
            break;
          case 'SUL':
            mapa[roboI+1][roboJ] = 0;
            flagObstaculo = false;
            break;
          case 'LESTE':
            mapa[roboI][roboJ+1] = 0;
            flagObstaculo = false;
            break;
          case 'OESTE':
            mapa[roboI][roboJ-1] = 0;
            flagObstaculo = false;
            break;
        }
      }
    }
    else{ 
      controle('s');
      flagObstaculo = true;
      esperaTimer = millis(); 
    }
  }
  // Caso não exista obstáculo e o destino não tenha sido alcançado, realiza os movimentos
  if (!flagObstaculo){
    rosaDosVentos();
    switch (orientacao) {
      case 'NORTE':
        if (mapa[roboI - 1][roboJ] == numeroDaRota ) {
          Serial.print("In: wavefront N frente  \t");
          moverParaFrente();
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          Serial.print("In: wavefront N girar D  \t");
          girar('DIREITA','LESTE');
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('ESQUERDA','OESTE');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('MEIAVOLTA','SUL');
        }
        break;
      case 'SUL':
        if (mapa[roboI + 1][roboJ] == numeroDaRota ) {
          moverParaFrente();
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('DIREITA','OESTE');
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          girar('ESQUERDA','LESTE');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('MEIAVOLTA','NORTE');
        }
        break;

      case 'LESTE':
        if (mapa[roboI][roboJ + 1] == numeroDaRota ) {
          Serial.print("In: wavefront L frente  \t");
          moverParaFrente();
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('DIREITA','SUL');
        }
        else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
          girar('ESQUERDA','NORTE');
        }
        else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
          girar('MEIAVOLTA','OESTE');
        }
        break;

      case 'OESTE':
        if (mapa[roboI][roboJ - 1] == numeroDaRota ) {
          moverParaFrente();
        }
        else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
          girar('DIREITA','NORTE');
        }
        else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
          girar('ESQUERDA','SUL');
        }
        else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
          girar('MEIAVOLTA','LESTE');
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


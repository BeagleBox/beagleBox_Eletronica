
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
bool flagMoverParaFrente = true;
bool flagObstaculo = false;
unsigned long esperaTimer = 0;
int aPercorrer = 0;

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

//===========================================================================
//Direcoes NORTE SUL LESTE E OESTE
//===========================================================================

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

//===========================================================================
//Menor Vizinho
//===========================================================================

void calculoNumeroDaRota () {
  
  numeroDaRota = 30000;
  
  if(mapa[roboI+1][roboJ] < numeroDaRota && mapa[roboI+1][roboJ] != 0){numeroDaRota = mapa[roboI+1][roboJ];}
  if(mapa[roboI-1][roboJ] < numeroDaRota && mapa[roboI-1][roboJ] != 0){numeroDaRota = mapa[roboI-1][roboJ];}
  if(mapa[roboI][roboJ+1] < numeroDaRota && mapa[roboI][roboJ+1] != 0){numeroDaRota = mapa[roboI][roboJ+1];}
  if(mapa[roboI][roboJ-1] < numeroDaRota && mapa[roboI][roboJ-1] != 0){numeroDaRota = mapa[roboI][roboJ-1];}
}

//===========================================================================
//Avança uma casa
//===========================================================================

int moverParaFrente() {
  if (flagMoverParaFrente) {
    controle('w');
    distancia = encoder;
    flagMoverParaFrente = false;

    switch (orientacao) {
      case 'N':
        aPercorrer = comprimentoQuadrado - quantoRodeiN;
        quantoRodeiN = 0;
        break;
      case 'S':
        aPercorrer = comprimentoQuadrado - quantoRodeiS;
        quantoRodeiS = 0;
        break;
      case 'L':
        aPercorrer = comprimentoQuadrado - quantoRodeiL;
        quantoRodeiL = 0;
        break;
      case 'O':
        aPercorrer = comprimentoQuadrado - quantoRodeiO;
        quantoRodeiO = 0;
        break;
    }

  }

  Serial.print("In: moverParaFrente. \t");
  if (encoder - distancia >= aPercorrer) {
    Serial.print("In: Condição de pausa moverParaFrente  \t");
    
    controle('s');
    flagMoverParaFrente = true;

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
    }
  }
  return encoder - distancia;
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
//Encontrou o destino
//===========================================================================

void fim(){
  controle('s');
  Serial.print("Cheguei ao destino.");
  while (1);
}

//===========================================================================
//Checa os obstaculos
//===========================================================================

void obstaculo() {

  if (flagObstaculo){
      if(millis() - esperaTimer > tempoDeEspera){
          Serial.print("In: esperei 3s \t");

        switch (orientacao) {
          case 'N':
            quantoRodeiN = encoder - distancia;
            mapa[roboI-1][roboJ] = 0;
            flagObstaculo = false;
            break;
          case 'S':
            quantoRodeiS = encoder - distancia;
            mapa[roboI+1][roboJ] = 0;
            flagObstaculo = false;
            break;
          case 'L':
            quantoRodeiL = encoder - distancia;
            mapa[roboI][roboJ+1] = 0;
            flagObstaculo = false;
            break;
          case 'O':x
            quantoRodeiO = encoder - distancia;
            mapa[roboI][roboJ-1] = 0;
            flagObstaculo = false;
            break;
        }
      //posicaoRobo(roboI,roboJ);
      }
    }
    else{ 
      Serial.print("In: ultrassomCheck primeira passagem\t");
      controle('s');
      esperaTimer = millis(); 
      


      flagObstaculo = true;
    }
}

//===========================================================================
//Controle dos movimentos
//===========================================================================

void movimento(){
  
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

//===========================================================================
//Setup
//===========================================================================

void setupAlgoritmo() {
  rosaDosVentos();
  calculoNumeroDaRota(); 
  Serial.println(numeroDaRota); 
}

//===========================================================================
//Algoritmo
//===========================================================================

void rodarWavefront() {
  Serial.print("In: rodarWavefront \t");

  calculoNumeroDaRota();

  // Checa se o robo chegou ao destino e ordena parada
  if (numeroDaRota < 1) {
    fim();
  }
  // Checa se existe um obstáculo detectado pelos ultrassons.
  else if (ultrassomEsquerda > distanciaMinimaUltrassom &&  ultrassomEsquerda < distanciaMaximaUltrassom  || ultrassomDireita > distanciaMinimaUltrassom && ultrassomDireita < distanciaMaximaUltrassom || ultrassomCentro > distanciaMinimaUltrassom && ultrassomCentro < distanciaMaximaUltrassom) {
    Serial.print("In: ultrassom check \t");
    obstaculo();  
  }
  // Caso não exista obstáculo e o destino não tenha sido alcançado, realiza os movimentos
  if (!flagObstaculo){
    Serial.print("In: wavefront sem obstaculo \t");
    movimento();
  }
}




//===========================================================================
//Constantes
//===========================================================================

#define passoDeVelocidade 10
#define comprimentoQuadrado 50

//===========================================================================
//Variaveis
//===========================================================================

int motorDianteiroEsquerda = 5;
int motorTraseiroEsquerda = 6;
int motorDianteiroDireita = 9;
int motorTraseiroDireita = 10;
// Velocidade dos motores, pusol PWM: (0-255)
int velocidadeMotor = 180;
float distancia = 0;
bool flag = true;

//===========================================================================
//Funções
//===========================================================================

void movimento(int a, int b, int c, int d) {
  /*analogWrite(motorDianteiroDireita, a);
  analogWrite(motorDianteiroEsquerda, b);
  analogWrite(motorTraseiroDireita, c);
  analogWrite(motorTraseiroEsquerda, d);
*/}

void velocidade(signed int a) {
  velocidadeMotor = constrain(velocidadeMotor + a, 0, 255);
}

void controle(char estado) {
  if (estado == 'i') {} // OFF
  if (estado == 'w') { // Frente
    movimento(velocidadeMotor, velocidadeMotor, 0, 0);
    //Serial.println ("FRENTE");
  }
  if (estado == 'd') { // Direita
    movimento(velocidadeMotor, 0, 0, velocidadeMotor);
    //Serial.println ("Direita");
  }
  if (estado == 'a') { // Esquerda
    movimento(0, velocidadeMotor, velocidadeMotor, 0 );
  }
  if (estado == 'x') { // Ré
    movimento(0, 0, velocidadeMotor, velocidadeMotor);
  }
  if (estado == 's') { // Parado
    movimento(0, 0, 0, 0);
  }
  //Velocidade
  if (estado == 'q') { // Aumenta a velocidade dos motores
    velocidade(passoDeVelocidade);
  }
  if (estado == 'e') { // Diminui a velocidade dos motores
    velocidade(-passoDeVelocidade);
  }
}

void moverParaFrente() {
  if (flag) {
    controle('w');
    distancia = encoderEsquerda;
    flag = false;
  }
  // Serial.print("In: moverParaFrente. \t");
  
  if (encoderEsquerda - distancia >= comprimentoQuadrado){
    controle('s');
    numeroDaRota--;
    flag = true;
    rosaDosVentos();
    // Serial.print("In: Condição de pausa moverParaFrente  \t");
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
}

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

void setupPWMControl() {

  pinMode(motorDianteiroDireita, OUTPUT);
  pinMode(motorTraseiroDireita, OUTPUT);
  pinMode(motorDianteiroEsquerda, OUTPUT);
  pinMode(motorTraseiroEsquerda, OUTPUT);

}
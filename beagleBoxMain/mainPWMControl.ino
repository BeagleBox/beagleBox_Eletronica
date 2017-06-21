
//===========================================================================
//Constantes
//===========================================================================

#define passoDeVelocidade 10
#define comprimentoQuadrado 20

//===========================================================================
//Variaveis
//===========================================================================

int motorDianteiroEsquerda = 5;
int motorTraseiroEsquerda = 6;
int motorDianteiroDireita = 9;
int motorTraseiroDireita = 10;
// Velocidade dos motores, pusol PWM: (0-255)
int velocidadeMotor = 100;
float distancia = 0;

//===========================================================================
//Funções
//===========================================================================

void movimento(int a, int b, int c, int d) {
  analogWrite(motorDianteiroDireita, a);
  analogWrite(motorDianteiroEsquerda, b);
  analogWrite(motorTraseiroDireita, c);
  analogWrite(motorTraseiroEsquerda, d);
}

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
    movimento(0, velocidadeMotor, 0, velocidadeMotor);
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
  distancia = encoderEsquerda;
  while (encoderEsquerda - distancia < comprimentoQuadrado) {
    movimento(velocidadeMotor, velocidadeMotor, 0, 0);
    leituraEncoder();
    Serial.println (encoderEsquerda);
  }
}

void girar(char direcao, char rumo) {
  switch (direcao) {
    case 'D':
      do {
        rosaDosVentos();
        movimento(velocidadeMotor, 0, 0, velocidadeMotor);
        leituraOrientacao();
        Serial.println(orientacao);
      } while (orientacao != rumo);
      break;

    case 'E':
      do {
        rosaDosVentos();
        movimento(0, velocidadeMotor, 0, velocidadeMotor);
        leituraOrientacao();
         Serial.println(orientacao);
      } while (orientacao != rumo);
      break;

    case 'T':
      do {
        rosaDosVentos();
        movimento(velocidadeMotor, 0, 0, velocidadeMotor);
        leituraOrientacao();
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

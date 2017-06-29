
//===========================================================================
//Constantes
//===========================================================================

#define passoDeVelocidade 10

//===========================================================================
//Variaveis
//===========================================================================

int motorDianteiroEsquerda = 5;
int motorTraseiroEsquerda = 6;
int motorDianteiroDireita = 9;
int motorTraseiroDireita = 10;
// Velocidade dos motores, pusol PWM: (0-255)
int velocidadeMotor = 100;

//===========================================================================
//Funções
//===========================================================================

void comando(int a, int b, int c, int d) {
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
    comando(velocidadeMotor, velocidadeMotor, 0, 0);
    //Serial.println ("FRENTE");
  }
  if (estado == 'd') { // Direita
    comando(velocidadeMotor, 0, 0, velocidadeMotor);
    //Serial.println ("Direita");
  }
  if (estado == 'a') { // Esquerda
    comando(0, velocidadeMotor, 0, velocidadeMotor);
  }
  if (estado == 'x') { // Ré
    comando(0, 0, velocidadeMotor, velocidadeMotor);
  }
  if (estado == 's') { // Parado
    comando(0, 0, 0, 0);
  }
  //Velocidade
  if (estado == 'q') { // Aumenta a velocidade dos motores
    velocidade(passoDeVelocidade);
  }
  if (estado == 'e') { // Diminui a velocidade dos motores
    velocidade(-passoDeVelocidade);
  }
}

void setupPWMControl() {

  pinMode(motorDianteiroDireita, OUTPUT);
  pinMode(motorTraseiroDireita, OUTPUT);
  pinMode(motorDianteiroEsquerda, OUTPUT);
  pinMode(motorTraseiroEsquerda, OUTPUT);

}

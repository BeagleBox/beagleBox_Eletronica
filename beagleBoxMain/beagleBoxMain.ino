
/*
Codigo controle BeagleBox 

Funcionalidades:
  #Ultrassom
  #Encoder
  #PWM
  #Acelerometro/Giroscopio


*/
//===========================================================================
//Bibliotecas
//===========================================================================

//===========================================================================
//Definições
//===========================================================================

#define passoDeVelocidade 10

//===========================================================================
//Variaveis 
//===========================================================================

//MOTOR
int motorDianteiroEsquerda = 5; 
int motorTraseiroEsquerda = 6; 
int motorDianteiroDireita = 9; 
int motorTraseiroDireita = 10; 
// Velocidade dos motores, pusol PWM: (0-255)
int velocidadeMotor = 0; 

//ENCODER
//Contador do numero de voltas que o encoder realizou
unsigned int encoderCounter=0;
//Variaveis para contagem de giros do encoder
boolean encoderOldValue = true;
boolean encoderNewValue = true;

//ULTRASSOM

//ACELERÔMETRO E GIROSCÓPIO

//FLAGS E VARIÁVEIS DE CONTROLE
int flag = 0;
int b = 255;

//===========================================================================
//Funções
//===========================================================================

//DISTANCIA PERCORRIDA
void distanciaPercorrida()
{
  Serial.print("Numero de rotacoes: ");  
  Serial.println(encoderCounter,DEC);  
  encoderCounter=0;  //  reset counter to zero
  Encoder1Timer = millis();
}

//CONTROLE DE ACIONAMENTO DOS MOTORES
void movimento(int a,int b,int c,int d) {
  analogWrite(motorDianteiroDireita, a); 
  analogWrite(motorDianteiroEsquerda, b);
  analogWrite(motorTraseiroDireita, c); 
  analogWrite(motorTraseiroEsquerda, d);
  //ultimoEstado = estado;
}

//CONTROLE DE VELOCIDADE
void velocidade(signed int a){
  velocidadeMotor = constrain(velocidadeMotor + a,0,255);
  Serial.print("Velocidade: ");
  Serial.println(velocidadeMotor);
  //estado = ultimoEstado; //Variavel pra continuar o mesmo comando de movimento
}

//AÇÃO DO ROBO
void controle(char estado){
  if(estado=='i'){} // OFF
  if(estado=='w'){ // Frente
    movimento(velocidadeMotor,velocidadeMotor,0,0);
    //Serial.println ("FRENTE");
  }
  if(estado=='d'){ // Direita
    movimento(velocidadeMotor,0,0,velocidadeMotor);
    //Serial.println ("Direita");
  }
  if(estado=='a'){ // Esquerda
    movimento(0,velocidadeMotor,0,velocidadeMotor);
  } 
  if(estado=='x'){ // Ré
    movimento(0,0,velocidadeMotor,velocidadeMotor);
  }
  if(estado=='s'){ // Parado
    movimento(0,0,0,0);
  }
  //Velocidade 
  if(estado=='q'){ // Aumenta a velocidade dos motores
    velocidade(passoDeVelocidade);
  }
  if(estado=='e'){ // Diminui a velocidade dos motores
    velocidade(-passoDeVelocidade);
  }
}

//===========================================================================
//Algoritmo
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

//===========================================================================
//Setup
//===========================================================================

void setup() { 
  
  Serial.begin(38400); // Comunicação com a Rasp
  
  pinMode(motorDianteiroDireita, OUTPUT);
  pinMode(motorTraseiroDireita, OUTPUT);
  pinMode(motorDianteiroEsquerda, OUTPUT);
  pinMode(motorTraseiroEsquerda, OUTPUT);
  pinMode(2,INPUT);

  int mapa[8][8] = {{0,0,0,0,0,0,0},
                    {0,5,4,3,2,G,0}
                    {0,6,5,4,3,2,0}
                    {0,7,6,5,4,3,0}
                    {0,8,7,W,W,W,0}
                    {0,9,8,W,0,0,0}
                    {0,R,9,W,0,0,0}
                    {0,0,0,0,0,0,0}};

  setupBussola();
  
  //if (digitalRead(2) == LOW){encoderOldValue = false;}
  
  //velocidade(100);
  //controle('w');
} 

//===========================================================================
//Loop
//===========================================================================

void loop() { 

  
}


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
//Tempo que leva para chamar a função
const unsigned long Encoder1Interval = 1000;
//Timer
unsigned long Encoder1Timer;
int flagEncoder=0;

//ULTRASSOM

//ACELERÔMETRO E GIROSCÓPIO

//FLAGS E VARIÁVEIS DE CONTROLE
int i=0; //TESTE APAGAR
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
  Serial.print("Numero de acoes: ");  
  Serial.println(i); //TESTE APAGAR   
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
//Setup
//===========================================================================

void setup() { 
  Encoder1Timer = millis();
  Serial.begin(38400); // Comunicação com a Rasp
  pinMode(motorDianteiroDireita, OUTPUT);
  pinMode(motorTraseiroDireita, OUTPUT);
  pinMode(motorDianteiroEsquerda, OUTPUT);
  pinMode(motorTraseiroEsquerda, OUTPUT);

  pinMode(12,INPUT);

  if (digitalRead(12) == LOW){encoderOldValue = false;}
  
  velocidade(255);
  controle('w');
} 

//===========================================================================
//Loop
//===========================================================================
void loop() { 

  /*
  encoderNewValue = digitalRead(2);
  //if (flagEncoder== 0){ 
  if(digitalRead(2) != encoderOldValue ){
    encoderCounter++;
    encoderOldValue = encoderNewValue;
    
    Serial.print("Digital :");
    Serial.println(encoderCounter);
  }
  //}
  if (flag ==0){
  Serial.print("Analogico: " );
  Serial.println(analogRead(0));
  }

  //Andar 1 girocompletofrente
  if (encoderCounter == 100){velocidade(b);controle('x');flag = 1; b = b-20;}
  if (encoderCounter == 101){b=255;velocidade(100);controle('d'); delay(500); controle('w');}
  if(encoderCounter == 220){velocidade(b);controle('x');flag = 1; b = b-20;}
  if (encoderCounter == 221){b=255;velocidade(100);controle('d'); delay(500); controle('w');}
  if (encoderCounter == 300){velocidade(b);controle('x');flag = 1; b = b-20;}
  if (encoderCounter > 301){controle('s');}
  */
  
  if ((millis() - Encoder1Timer) >= Encoder1Interval) {
    distanciaPercorrida();
  }//fim da leitura

  encoderNewValue = digitalRead(12);
  //if (flagEncoder== 0){ 
  if(digitalRead(12) != encoderOldValue ){
    encoderCounter++;
    encoderOldValue = encoderNewValue;
    
  }
  
  //}

  //Girar 45 graus
  i++; // TESTE APAGAR
  
}


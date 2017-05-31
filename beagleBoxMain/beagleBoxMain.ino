


//===========================================================================
//Variaveis 

#define passoDeVelocidade 10

//Pinos de controle do motor
int esqA = 5; 
int esqB = 6; 
int dirA = 9; 
int dirB = 10; 

//Largura do pulso PWM nos motores
int vel = 0; // Velocidade dos motores, Range:(0-255)

//Estado de atuação dos motores
//int estado = 'i'; // inicia sem atuação nos motores
int ultimoEstado;

//Contador do numero de voltas que o encoder realizou
unsigned int encoderCounter=0;

//Variaveis para contagem de giros do encoder
boolean encoderOldValue = true;
boolean encoderNewValue = true;

//Tempo que leva para chamar a função
const unsigned long Encoder1Interval = 1000;
//Timer
unsigned long Encoder1Timer;


int flag = 0;
//===========================================================================
//DISTANCIA PERCORRIDA

void distanciaPercorrida()
{
  Serial.print("Numero de rotacoes: ");  
  Serial.println(encoderCounter,DEC);  
  encoderCounter=0;  //  reset counter to zero
  Encoder1Timer = millis();
}


//===========================================================================
//CONTROLE DE MOVIMENTAÇÃO INDEPENDENTE

//Funçao para controle dos movimentos Frente, Ré, Direita, Esquerda e Parado
void movimento(int a,int b,int c,int d) {
  analogWrite(dirA, a); 
  analogWrite(esqA, b);
  analogWrite(dirB, c); 
  analogWrite(esqB, d);
  //ultimoEstado = estado;
}

void velocidade(signed int a){
  vel = constrain(vel + a,0,255);
  Serial.print("Velocidade: ");
  Serial.println(vel);
  //estado = ultimoEstado; //Variavel pra continuar o mesmo comando de movimento
}
//===========================================================================
// PEGAR DADO NA SERIAL UM SÓ VEZ

/*void serialEvent() {
  while (Serial.available()) {
    estado = Serial.read(); // recebe novo dado até receber \n
  }
}*/

//===========================================================================
//Controle

void controle(char estado){
  if(estado=='i'){} // OFF
  if(estado=='w'){ // Frente
    movimento(vel,vel,0,0);
    //Serial.println ("FRENTE");
  }
  if(estado=='d'){ // Direita
    movimento(vel,0,0,vel);
    //Serial.println ("Direita");
  }
  if(estado=='a'){ // Esquerda
    movimento(0,vel,0,vel);
  } 
  if(estado=='x'){ // Ré
    movimento(0,0,vel,vel);
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
//SETUP E LOOP

void setup() { 
  Encoder1Timer = millis();
  Serial.begin(38400); // Comunicação com a Rasp
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(esqA, OUTPUT);
  pinMode(esqB, OUTPUT);

  pinMode(2,INPUT);

  if (digitalRead(2) == LOW){encoderOldValue = false;}
  
  velocidade(60);
  controle('w');
} 

void loop() { 

  encoderNewValue = digitalRead(2);
  
  if(digitalRead(2) != encoderOldValue ){
    encoderCounter++;
    encoderOldValue = encoderNewValue;
    
    Serial.print("Digital :");
    Serial.println(encoderCounter);
  }
  
  if (flag ==0){
  Serial.print("Analogico: " );
  Serial.println(analogRead(0));
  }
  /*if ((millis() - Encoder1Timer) >= Encoder1Interval) {
    distanciaPercorrida();
  }*/
  
  //Controle 
  
  
  //Andar 1 girocompletofrente
  if (encoderCounter == 32){velocidade(200);controle('x');flag = 1;}
  if (encoderCounter == 33){controle('s');}
  if (encoderCounter == 34){controle('s');}
  if (encoderCounter == 35){controle('s'); }


}


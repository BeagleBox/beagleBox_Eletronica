#define passoDeVelocidade 10

int esqA = 5; 
int esqB = 6; 
int dirA = 9; 
int dirB = 10; 
int vel = 0; // Velocidade dos motores, Range:(0-255)
int estado = 'i'; // inicia sem atuação nos motores
int ultimoEstado;
boolean flagSerial = false;
unsigned int encoderCounter=0;

boolean encoderOldValue = true;
boolean encoderNewValue = true;

//INTERVALO
const unsigned long Encoder1Interval = 1000;
//TIMER
unsigned long Encoder1Timer;

//===========================================================================

void distanciaPercorrida()
{
  Serial.print("Numero de rotacoes: ");  
  Serial.println(encoderCounter,DEC);  
  encoderCounter=0;  //  reset counter to zero
  Encoder1Timer = millis();
}

//===========================================================================

void setup() { 
  Encoder1Timer = millis();
  Serial.begin(38400); // Comunicação com a Rasp
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(esqA, OUTPUT);
  pinMode(esqB, OUTPUT);

  pinMode(2,INPUT);

  if (digitalRead(2) == LOW){encoderOldValue = false;}
} 
//===========================================================================

void loop() { 

  encoderNewValue = digitalRead(2);
  
  if(digitalRead(2) != encoderOldValue ){
    encoderCounter++;
    encoderOldValue = encoderNewValue;
  }
  
  if ((millis() - Encoder1Timer) >= Encoder1Interval) {
    distanciaPercorrida();
  }//fim Encoder1
  
  //Controle 
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

//Funçao para controle dos movimentos Frente, Ré, Direita, Esquerda e Parado
void movimento(int a,int b,int c,int d) {
  analogWrite(dirA, a); 
  analogWrite(esqA, b);
  analogWrite(dirB, c); 
  analogWrite(esqB, d);
  ultimoEstado = estado;
}

void velocidade(signed int a){
  vel = constrain(vel + a,0,255);
  Serial.print("Velocidade: ");
  Serial.println(vel);
  estado = ultimoEstado; //Variavel pra continuar o mesmo comando de movimento
}
//===========================================================================

void serialEvent() {
  while (Serial.available()) {
    estado = Serial.read(); // recebe novo dado até receber \n
  }
}


//===========================================================================

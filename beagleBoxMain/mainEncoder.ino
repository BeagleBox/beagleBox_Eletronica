
//===========================================================================
//Definições
//===========================================================================

# define encoderEsquerda 12
# define encoderDireita 11

//===========================================================================
//Variaveis 
//===========================================================================

//Contador do numero de voltas que o encoder realizou
unsigned int encoderCounter=0;
//Variaveis para contagem de giros do encoder
boolean encoderOldValue = true;
boolean encoderNewValue = true;

//===========================================================================
//Funções
//===========================================================================

void distanciaPercorrida(){}

void setupEncoder(){
  pinMode(encoderEsquerda,INPUT);  
  pinMode(encoderDireita,INPUT);  
}

void leituraEncoder(){
  
  encoderNewValue = digitalRead(encoderEsquerda);

  if(digitalRead(2) != encoderOldValue ){
  encoderCounter++;
  encoderOldValue = encoderNewValue;
  }

  //Adicionando por causa do Timer
  encoderTimer = millis();
}

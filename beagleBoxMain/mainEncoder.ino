
//===========================================================================
//Constantes
//===========================================================================

# define pinoEncoder 3

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

void setupEncoder(){
  pinMode(pinoEncoder,INPUT);  
  digitalwrite(3,HIGH);
  attachInterrupt(1, leituraEncoder, RISING); 
  //if (digitalRead(pinoEncoder) == LOW){encoderOldValue = false;} 
}

void leituraEncoder(){
  
  encoder++; // * 0.508938 para cm
  //Adicionando por causa do Timer
  encoderTimer = millis();
}

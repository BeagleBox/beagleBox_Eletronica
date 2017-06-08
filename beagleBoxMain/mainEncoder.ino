
//===========================================================================
//Definições
//===========================================================================

# define encoderEsquerda 2
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

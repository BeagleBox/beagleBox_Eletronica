
//===========================================================================
//Definições
//===========================================================================

#define SONAR_NUM 3
#define SONAR_DIREITA 0      // Numero do sensor no array
#define SONAR_CENTRO 1      // Numero do sensor no array
#define SONAR_ESQUERDA 2      // Numero do sensor no array
#define NUMERO_MEDICOES 10
#define MAX_DISTANCE 400 // Maxima distancia (em cm).
#define uS1 7 // pino que recebe o ping(trig/echo)
#define uS2 3
#define uS3 4

//===========================================================================
//Variaveis 
//===========================================================================

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(uS1, uS1, MAX_DISTANCE), // trig/echo/maxDist 
  NewPing(uS2, uS2, MAX_DISTANCE), 
  NewPing(uS3, uS3, MAX_DISTANCE)
};

//===========================================================================
//Funções
//===========================================================================
void setupUltrassom(){}

void leituraUltrassomDireita() {  
  ultrassomDireita = sonar[SONAR_DIREITA].convert_cm(sonar[SONAR_DIREITA].ping_median(NUMERO_MEDICOES)); // Calcula a media entre 10 pulsos e converte o resultado para cm  
  ultrassomTimer= millis();
}

void leituraUltrassomCentro() {    
  ultrassomCentro = sonar[SONAR_CENTRO].convert_cm(sonar[SONAR_CENTRO].ping_median(NUMERO_MEDICOES)); // Calcula a media entre 10 pulsos e converte o resultado para cm
  //ultrassomTimer= millis();
}
    
void leituraUltrassomEsquerda() { 
  ultrassomEsquerda = sonar[SONAR_ESQUERDA].convert_cm(sonar[SONAR_ESQUERDA].ping_median(NUMERO_MEDICOES)); // Calcula a media entre 10 pulsos e converte o resultado para cm
  //ultrassomTimer= millis();
}

 

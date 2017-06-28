
//===========================================================================
//Constantes
//===========================================================================

#define SONAR_NUM 3          // 
#define SONAR_DIREITA 0      // Numero do sensor no array
#define SONAR_CENTRO 1       // Numero do sensor no array
#define SONAR_ESQUERDA 2     // Numero do sensor no array
#define NUMERO_MEDICOES 1    
#define MAX_DISTANCE 300 // Maxima distancia (em cm).
#define uS1 7 // pino que recebe o ping(trig/echo) ultrassom direita
#define uS2 12 // pino que recebe o ping(trig/echo) ultrassom centro
#define uS3 4 // pino que recebe o ping(trig/echo) ultrassom esquerda

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
  // Calcula a media entre 10 pulsos e converte o resultado para cm  
  ultrassomDireita = sonar[SONAR_DIREITA].convert_cm(sonar[SONAR_DIREITA].ping_median(NUMERO_MEDICOES)); 
  // Atualiza o timer da leitura do ultrassom
  ultrassomTimer= millis();
}

void leituraUltrassomCentro() {    
  // Calcula a media entre 10 pulsos e converte o resultado para cm
  ultrassomCentro = sonar[SONAR_CENTRO].convert_cm(sonar[SONAR_CENTRO].ping_median(NUMERO_MEDICOES)); 
}
    
void leituraUltrassomEsquerda() { 
  // Calcula a media entre 10 pulsos e converte o resultado para cm
  ultrassomEsquerda = sonar[SONAR_ESQUERDA].convert_cm(sonar[SONAR_ESQUERDA].ping_median(NUMERO_MEDICOES)); 
}


 

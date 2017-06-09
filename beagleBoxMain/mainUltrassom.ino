
//===========================================================================
//Definições
//===========================================================================

#define SONAR_NUM 3      // Numero de sensores.
#define MAX_DISTANCE 400 // Maxima distancia (em cm).
#define uS1 7 // pino que recebe o ping(trig/echo)
#define uS2 3
#define uS3 4

//===========================================================================
//Variaveis 
//===========================================================================
int flagUltrassom = 0;
//float ultrassom1 = 0;

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(uS1, uS1, MAX_DISTANCE), // trig/echo/maxDist 
  NewPing(uS2, uS2, MAX_DISTANCE), 
  NewPing(uS3, uS3, MAX_DISTANCE)
};

//===========================================================================
//Funções
//===========================================================================
void setupUltrassom(){
  while(flagUltrassom < 4){
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop
    delay(50); // Espera 50ms entre os pings, não pode diminuir mais do que para 30ms
    //ultrassom[i] = sonar[i].convert_cm(sonar[i].ping_median(5)); // Calcula a media entre 10 pulsos e converte o resultado para cm
  } 
  flagUltrassom++;
  }
}

void leituraUltrassom() { 
  for (uint8_t i = 0; i< SONAR_NUM; i++){
    // Espera 50ms entre os pings, não pode diminuir mais do que para 30ms
    if (i==1){
    ultrassomDireita = sonar[i].convert_cm(sonar[i].ping_median(10)); // Calcula a media entre 10 pulsos e converte o resultado para cm
    delay(50);
    }
    if (i==1){
    ultrassomCentro = sonar[i].convert_cm(sonar[i].ping_median(10)); // Calcula a media entre 10 pulsos e converte o resultado para cm
    delay(50);
    }
    if (i==1){
    ultrassomEsquerda = sonar[i].convert_cm(sonar[i].ping_median(10)); // Calcula a media entre 10 pulsos e converte o resultado para cm
    delay(50);
    }
  }
}

/*
  Controle BeagleBox

  Funcionalidades:
  #Ultrassom
  #Encoder
  #PWM
  #Acelerometro/Giroscopio (Bussola)

  Pinagem Arduino:
  A0 ----> 
  A1 ----> 
  A2 ---->
  A3 ---->
  A4 ----> SCA MPU6050
  A5 ----> SCL MPU6050
  A6 ---->
  A7 ---->

  D00 ---> TX
  D01 ---> RX
  D02 ---> Interrupção do MPU6050
  D03 ---> Interrupção do Encoder
  D04 ---> Ultrassom Esquerda
  D05 ---> Motor Dianteiro Esquerda
  D06 ---> Motor Traseiro Esquerda
  D07 ---> Ultrassom Direita
  D08 --->
  D09 ---> Motor Dianteiro Direita
  D10 ---> Motor Traseiro Direita
  D11 ---> 
  D12 ---> Ultrassom Centro
  D13 --->

*/
//===========================================================================
//Bibliotecas
//===========================================================================

//BUSSOLA
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

//ULTRASSOM
#include <NewPing.h>

//===========================================================================
//Constantes
//===========================================================================

#define LED_PIN 13
#define intervaloCalibracao 16000
#define intervaloEntreUltrassons 50

//===========================================================================
//Variaveis
//===========================================================================

//Posicionamento do robo na matriz
int roboI = 6;
int roboJ = 1;
int velocidadeMotor = 150;

//inidicação de atividade
bool blinkState = false;

float bussola = 0;
float ultrassomDireita = 0;
float ultrassomCentro = 0;
float ultrassomEsquerda = 0;
unsigned int encoder = 0;
float teste = 0;
char orientacao = 'I';

//INTERVALOS DE LEITURA DOS SINAIS
const unsigned long orientacaoIntervalo = 10;
const unsigned long ultrassomIntervalo = 150;

//TIMERS PARA REPETIR A LEITURA DO SINAL
unsigned long orientacaoTimer;
unsigned long ultrassomTimer;

//===========================================================================
//Funções
//===========================================================================

/*Algoritmo
  wavefront                 ALGORITMO DE RESOLUÇÃO DO MAPA
  rosaDosVentos             TRASFORMA O DADO DA BUSSOLA PARA DIRECOES N,S,L,O
  calculoNumeroDaRota       CALCULA O
  posicaoRobo
*/
/*Bussola
  orientacao                LOOP DA BUSSOLA QUE INFORMA A ORIENTACAO DO ROBO
*/
/*Encoder
  distanciaPercorrida       DISTANCIA QUE O ROBO ANDOU EM (cm)
*/
/*PWM
  movimento                 CONTROLE DE ACIONAMENTO DOS MOTORES
  velocidade                CONTROLE DE VELOCIDADE
  controle                  AÇÃO DO ROBO
*/
/*Ultrassom
  leituraUltrassom
*/

//===========================================================================
//LED mosta que o loop está acontecendo
//===========================================================================

void atividade() {
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

//===========================================================================
//Rotina de Leitura dos Sensores
//===========================================================================

void lerSensores() {
  Serial.println("In: lerSensores");

  if ((millis() - orientacaoTimer) >= orientacaoIntervalo) {
    leituraOrientacao();
    rosaDosVentos();
  }//fim da leitura
  if ((millis() - ultrassomTimer) >= ultrassomIntervalo) {
    leituraUltrassomDireita();
  }//fim da leitura
  if ((millis() - (ultrassomTimer + intervaloEntreUltrassons)) >= ultrassomIntervalo) {
    leituraUltrassomCentro();
  }//fim da leitura
  if ((millis() - (ultrassomTimer + 2 * intervaloEntreUltrassons)) >= ultrassomIntervalo) {
    leituraUltrassomEsquerda();
  }//fim da leitura
}

//===========================================================================
//Serial Debug
//===========================================================================

void serialDebug() {
  
  Serial.print("In: serialDebug");
  
  Serial.print(bussola);
  Serial.print("<-bussola\t");
  Serial.print(ultrassomDireita);
  Serial.print("<-ud\t");
  Serial.print(ultrassomCentro);
  Serial.print("<-uc\t");
  Serial.print(ultrassomEsquerda);
  Serial.print("<-ue\t");
  Serial.print(encoder);
  Serial.print("<-encoder\t");
  Serial.print(orientacao);
  Serial.print("<-orientacao\t");
  Serial.print(roboI);
  Serial.print("<-roboI\t");
  Serial.print(roboJ);
  Serial.println("<-roboJ");


}

//===========================================================================
//Setup
//===========================================================================

void setup() {

  //SERIAL
  Serial.begin(115200); // Comunicação com a Rasp
  //INICIALIZAÇÃO DOS SENSORES
  Serial.println("  ");
  Serial.println("Inicializando Sensores...");
  setupAlgoritmo();
  Serial.println("\tAlgoritmo Inicializado.");
  setupBussola();
  Serial.println("\tBussola Inicializado.");
  setupEncoder();
  Serial.println("\tEncoder Inicializado.");
  setupPWMControl();
  Serial.println("\tPWMControl Inicializado.");
  setupUltrassom();
  Serial.println("\tUltrassom Inicializado.");

  //LED de indicação de atividade
  pinMode(LED_PIN, OUTPUT);

  //intervalo de calibração dos sensores
  Serial.println("Calibrando Sensores...");
  while (millis() < intervaloCalibracao) {};

  Serial.println("\tPRONTO!");
  delay(500);

  //tempo que foi chamado
  orientacaoTimer = millis();
  ultrassomTimer = millis();

}

//===========================================================================
//Loop
//===========================================================================

void loop() {

  //atualiza o valor dos sensores.
  lerSensores();

  //Algoritmo que realiza os movimentos do robo
  rodarWavefront();

  //Rotina para acompanhar os valores dos sensores e posição da execução
  serialDebug();

  //LED para indicar atividade
  atividade();
}

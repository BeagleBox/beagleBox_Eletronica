/*
  Controle BeagleBox
  Funcionalidades:
  #Ultrassom
  #Encoder
  #PWM
  #Acelerometro/Giroscopio (Bussola)
  Pinagem Arduino:
  A0 ----> Analogico Encoder Esquerda
  A1 ----> Analogico Encoder Direita
  A2 ---->
  A3 ---->
  A4 ----> SCA MPU6050
  A5 ----> SCL MPU6050
  A6 ---->
  A7 ---->
  D00 ---> TX
  D01 ---> RX
  D02 ---> Interrupção do MPU6050
  D03 ---> Interrupção do EncoderEsquerda
  D04 ---> Ultrassom Esquerda
  D05 ---> Motor Dianteiro Esquerda
  D06 ---> Motor Traseiro Esquerda
  D07 ---> Ultrassom Direita
  D08 --->
  D09 ---> Motor Dianteiro Direita
  D10 ---> Motor Traseiro Direita
  D11 ---> Encoder Direita
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
int roboI;
int roboJ;

//inidicação de atividade
bool blinkState = false;

float bussola = 0;
float ultrassomDireita = 0;
float ultrassomCentro = 0;
float ultrassomEsquerda = 0;
float encoderEsquerda = 0;
float encoderDireita = 0;
float teste = 0;
char orientacao = 'I';

//INTERVALOS DE LEITURA DOS SINAIS
const unsigned long orientacaoIntervalo = 10;
const unsigned long ultrassomIntervalo = 150;
const unsigned long encoderIntervalo = 1;

//TIMERS PARA REPETIR A LEITURA DO SINAL
unsigned long orientacaoTimer;
unsigned long ultrassomTimer;
unsigned long encoderTimer;

//===========================================================================
//Funções
//===========================================================================

/*Algoritmo
  wavefront                 ALGORITMO DE RESOLUÇÃO DO MAPA
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
//Rotina de Leitura dos Sensores
//===========================================================================

void leituraSensores(){  
  if ((millis() - orientacaoTimer) >= orientacaoIntervalo) {
    leituraOrientacao();
  }//fim da leitura
  if ((millis() - ultrassomTimer) >= ultrassomIntervalo) {
    leituraUltrassomDireita();
  }//fim da leitura
  if ((millis() - (ultrassomTimer + intervaloEntreUltrassons)) >= ultrassomIntervalo) {
    leituraUltrassomCentro();
  }//fim da leitura
  if ((millis() - (ultrassomTimer + 2*intervaloEntreUltrassons)) >= ultrassomIntervalo) {
    leituraUltrassomEsquerda();
  }//fim da leitura
  if ((millis() - encoderTimer) >= encoderIntervalo) {
    leituraEncoder();
  }//fim da leitura
}

//===========================================================================
//Serial Debug
//===========================================================================

void serialDebug() {  
  Serial.print(bussola);
  Serial.print("\t");
  Serial.print(ultrassomDireita);
  Serial.print("\t");
  Serial.print(ultrassomCentro);
  Serial.print("\t");
  Serial.print(ultrassomEsquerda);
  Serial.print("\t");
  Serial.print(encoderEsquerda);
  Serial.print("\t");
  Serial.println(orientacao);
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
  leituraOrientacao();
  delay(500);
  leituraOrientacao();

  //tempo que foi chamado
  orientacaoTimer = millis();
  ultrassomTimer = millis();
  encoderTimer = millis();

}

//===========================================================================
//Loop
//===========================================================================

void loop() {

  leituraSensores();

  wavefront();

  serialDebug();

  //LED para indicar atividade
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}
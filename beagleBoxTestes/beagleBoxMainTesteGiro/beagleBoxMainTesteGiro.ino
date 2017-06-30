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

//===========================================================================
//Constantes
//===========================================================================

#define LED_PIN 13
#define intervaloCalibracao 16000

//===========================================================================
//Variaveis
//===========================================================================

int dadoSerial = 'i';
//inidicação de atividade
bool blinkState = false;

float bussola = 0;

char orientacao = 'I';

//INTERVALOS DE LEITURA DOS SINAIS
const unsigned long orientacaoIntervalo = 10;
const unsigned long serialIntervalo = 200;

//TIMERS PARA REPETIR A LEITURA DO SINAL
unsigned long orientacaoTimer;
unsigned long serialTimer;


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
    rosaDosVentos();
  }//fim da leitura

}

//===========================================================================
//Serial Debug
//===========================================================================

void serialDebug() {  
  Serial.print(bussola);
  Serial.print("\t");
  Serial.println(orientacao);

  serialTimer = millis();
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
  setupBussola();
  Serial.println("\tBussola Inicializado.");
  setupPWMControl();
  Serial.println("\tPWMControl Inicializado.");


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
  serialTimer = millis();

}

//===========================================================================
//Loop
//===========================================================================

void loop() {

  leituraSensores();
 
  if(dadoSerial == 'w'){
    Serial.print("w ");
    girar('ESQUERDA','L');}
  else if(dadoSerial == 'a'){
    Serial.print("a ");
    girar('ESQUERDA','S');}
  else if(dadoSerial == 'x'){
    Serial.print("x ");
    girar('ESQUERDA','O');}
  else if(dadoSerial == 'd'){
    Serial.print("d ");
    girar('ESQUERDA','N');}
  else if(dadoSerial == 't'){
    Serial.print("t ");
    girar('DIREITA','O');}
  else if(dadoSerial == 'f'){
    Serial.print("f ");
    girar('DIREITA','S');}
  else if(dadoSerial == 'b'){
    Serial.print("b ");
    girar('DIREITA','L');}
  else if(dadoSerial == 'h'){
    Serial.print("h ");
    girar('DIREITA','N');}
  else if(dadoSerial == 'o'){
    Serial.print("o ");
    girar('MEIAVOLTA','O');}
  else if(dadoSerial == 'p'){
    Serial.print("p ");
    girar('MEIAVOLTA','L');}  

  controle('s');

  // if ((millis() - serialTimer) >= serialIntervalo) {
   serialDebug();
  // }//fim da leitura


  //LED para indicar atividade
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

void serialEvent() {
  while (Serial.available()) {
    dadoSerial = Serial.read();
  }
}
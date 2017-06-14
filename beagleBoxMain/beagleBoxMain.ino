/*
Codigo controle BeagleBox 

Funcionalidades:
  #Ultrassom
  #Encoder
  #PWM
  #Acelerometro/Giroscopio


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
//Definições
//===========================================================================

#define LED_PIN 13 
#define intervaloCalibracao 20000

//===========================================================================
//Variaveis 
//===========================================================================

//inidicação de atividade
bool blinkState = false;

int bussola = 0;
float ultrassomDireita = 0;
float ultrassomCentro = 0;
float ultrassomEsquerda = 0;

//INTERVALOS DE LEITURA DOS SINAIS
const unsigned long orientacaoIntervalo = 1;
const unsigned long ultrassomIntervalo = 250;
const unsigned long encoderIntervalo = 1000;

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
//Setup
//===========================================================================

void setup() { 

  //SERIAL
  Serial.begin(38400); // Comunicação com a Rasp
  //INICIALIZAÇÃO DOS SENSORES
  Serial.println("Inicializando Sensores...");
  setupBussola();
  Serial.println("Bussola Inicializado.");
  setupEncoder();
  Serial.println("Encoder Inicializado.");
  setupPWMControl();
  Serial.println("PWMControl Inicializado.");
  setupUltrassom();
  Serial.println("Ultrassom Inicializado.");

  //tempo que foi chamado
  orientacaoTimer = millis();
  ultrassomTimer = millis();
  encoderTimer = millis();

  //LED de indicação de atividade
  pinMode(LED_PIN, OUTPUT);
  
} 

//===========================================================================
//Loop
//===========================================================================

void loop() { 
  
  if ((millis() - orientacaoTimer) >= orientacaoIntervalo) {
    leituraOrientacao();
  }//fim da leitura

  if ((millis() - ultrassomTimer) >= ultrassomIntervalo) {
    leituraUltrassom();
  }//fim da leitura

  if ((millis() - encoderTimer) >= encoderTimer) {
    leituraEncoder();
  }//fim da leitura
  

  if(millis() > intervaloCalibracao){
    //leituraUltrassom();
    Serial.print("Bussola: ");
    Serial.println(bussola);
    Serial.print("Ultrassom Direita: ");
    Serial.println(ultrassomDireita);
    Serial.print("Ultrassom Centro: ");
    Serial.println(ultrassomCentro);
    Serial.print("Ultrassom Esquerda: ");
    Serial.println(ultrassomEsquerda);
    
  }
  else{}

  //LED para indicar atividade
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}


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

//===========================================================================
//Definições
//===========================================================================

#define LED_PIN 13 

//===========================================================================
//Variaveis 
//===========================================================================

bool blinkState = false;

//===========================================================================
//Funções
//===========================================================================

/*Algoritmo
wavefront                 ALGORITMO DE RESOLUÇÃO DO MAPA
*/
/*Bussola
orientação                LOOP DA BUSSOLA QUE INFORMA A ORIENTAÇÃO DO ROBO
*/
/*Encoder
distanciaPercorrida       DISTANCIA QUE O ROBO ANDOU EM (cm)
*/
/*PWM
movimento                 CONTROLE DE ACIONAMENTO DOS MOTORES
velocidade                CONTROLE DE VELOCIDADE
controle                  AÇÃO DO ROBO
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

  //LED de indicação de atividade
  pinMode(LED_PIN, OUTPUT);
  
} 

//===========================================================================
//Loop
//===========================================================================

void loop() { 


  
  //LED para indicar atividade
  blinkState = !blinkState;
  digitalWrite(LED_PIN, blinkState);
}

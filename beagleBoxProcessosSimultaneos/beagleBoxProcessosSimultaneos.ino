//================================
//===== LEDS =====================
const byte LEDverde = 12;
const byte LEDvermelho = 13;

//================================
//===== Intervalos================
const unsigned long LEDverdeInterval = 500;
const unsigned long LEDvermelhoInterval = 250;

//================================
//===== Timers ===================
unsigned long LEDverdeTimer;
unsigned long LEDvermelhoTimer;

//================================
//===== Outras variáveis =========
int Rnd = 0;

//================================
//===== Setup ====================
void setup() {
  pinMode(LEDverde, OUTPUT);
  pinMode(LEDvermelho, OUTPUT);
  
  LEDverdeTimer = millis();
  LEDvermelhoTimer = millis();

}

//================================
//===== LEDverdePisca ============
void LEDverdePisca() {
  if (digitalRead(LEDverde) == LOW) {
    digitalWrite(LEDverde, HIGH);
  } else {
    digitalWrite(LEDverde, LOW);    
  }
  
  //tempo que foi chamado
  LEDverdeTimer = millis();
}//LEDverdePisca

//================================
//===== LEDvermelhoPisca =========
void LEDvermelhoPisca() {
  if (digitalRead(LEDvermelho) == LOW) {
    digitalWrite(LEDvermelho, HIGH);
  } else {
    digitalWrite(LEDvermelho, LOW);    
  }
  
  //tempo que foi chamado
  LEDvermelhoTimer = millis();
}//LEDvermelhoPisca


//================================
//===== Loop =====================
void loop() {
  // LEDverdePisca
  if ((millis() - LEDverdeTimer) >= LEDverdeInterval) {
    LEDverdePisca();
  }//fim LEDverdePisca
  
  // LEDvermelhoPisca
  if ((millis() - LEDvermelhoTimer) >= LEDvermelhoInterval) {
    LEDvermelhoPisca();
  }//fim LEDvermelhoPisca
  
}

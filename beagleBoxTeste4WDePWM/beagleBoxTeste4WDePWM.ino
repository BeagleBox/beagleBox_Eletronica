
int esqA = 5; 
int esqB = 6; 
int dirA = 9; 
int dirB = 10; 
int vel = 0; // Velocidade dos motores, Range:(0-255)
int estado = 'i'; // inicia sem atuação nos motores
int ultimoEstado;
bool flagSerial = false;

void setup() { 
  Serial.begin(38400); // Comunicação com a Rasp
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
  pinMode(esqA, OUTPUT);
  pinMode(esqB, OUTPUT);
} 

void loop() { 

  //Controle 
  if(estado=='i'){} // OFF
  if(estado=='w'){ // Frente
    movimento(vel,vel,0,0);
    //Serial.println ("FRENTE");
  }
  if(estado=='d'){ // Direita
    movimento(vel,0,0,vel);
    //Serial.println ("Direita");
  }
  if(estado=='a'){ // Esquerda
    movimento(0,vel,vel,0);
  } 
  if(estado=='x'){ // Ré
    movimento(0,0,vel,vel);
  }
  if(estado=='s'){ // Parado
    movimento(0,0,0,0);
  }
  //Velocidade 
  if(estado=='q'){ // Aumenta a velocidade dos motores
    velocidade(+64);
  }
  if(estado=='e'){ // Diminui a velocidade dos motores
    velocidade(-64);
  }
}


//Funçao para controle dos movimentos Frente, Ré, Direita, Esquerda e Parado
void movimento(int a,int b,int c,int d) {
  analogWrite(dirA, a); 
  analogWrite(esqA, b);
  analogWrite(dirB, c); 
  analogWrite(esqB, d);
  ultimoEstado = estado;
}

void velocidade(signed int a){
  if (vel==192){
    if(a == +64){vel = 255;}
    else{vel = vel + a;}
  }
  else if (vel>=255){
    if(a == -64){vel = vel + a;} 
  }
  else if (vel<=0){
    if(a == +64){vel = vel + a;}  
  }  
  else{
    vel = vel + a;
    if (vel <=0) {vel = 0;}
    else if (vel >=255){vel = 255;}
  }
  Serial.print("Velocidade: ");
  Serial.println(vel);
  estado = ultimoEstado;
}

void serialEvent() {
  while (Serial.available()) {
    estado = Serial.read(); // recebe novo dado até receber \n
//    if (inChar == '\n') {
//      flagSerial = true;
//    }
//    else {estado = inChar;}
  }
}



// //===========================================================================
// //Constantes
// //===========================================================================

// # define pinoEncoderEsquerda 3
// # define pinoEncoderDireita 11

// //===========================================================================
// //Variaveis 
// //===========================================================================

// //Contador do numero de voltas que o encoder realizou
// unsigned int encoderCounter=0;
// //Variaveis para contagem de giros do encoder
// boolean encoderOldValue = true;
// boolean encoderNewValue = true;

// //===========================================================================
// //Funções
// //===========================================================================

// void incrementoEncoder(){
//   encoderCounter++;
// }

// void setupEncoder(){
//   //pinMode(pinoEncoderEsquerda,INPUT);  
//   pinMode(pinoEncoderDireita,INPUT);
//   attachInterrupt(1, incrementoEncoder, RISING); 
//   //if (digitalRead(pinoEncoderEsquerda) == LOW){encoderOldValue = false;} 
// }

// void leituraEncoder(){
  
//   /*encoderNewValue = digitalRead(pinoEncoderEsquerda);

//   if(digitalRead(pinoEncoderEsquerda) != encoderOldValue ){
//   encoderCounter++;
//   encoderOldValue = encoderNewValue;
//   }*/

//   encoderEsquerda = encoderCounter ; // * 0.508938 para cm
//   //Adicionando por causa do Timer
//   encoderTimer = millis();
// }

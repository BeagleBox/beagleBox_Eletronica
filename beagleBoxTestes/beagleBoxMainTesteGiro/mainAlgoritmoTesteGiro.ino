
// //===========================================================================
// //Constantes
// //===========================================================================

// #define linhas 8
// #define colunas 8
// //===========================================================================
// //Variaveis
// //===========================================================================
// int numeroDaRota;

// int mapa[linhas][colunas] = {{0, 0, 0, 0, 0, 0, 0},
//   {0, 5, 4, 3, 2, 1, 0},
//   {0, 6, 5, 4, 3, 2, 0},
//   {0, 0, 6, 5, 4, 3, 0},
//   {0, 8, 7, 0, 0, 0, 0},
//   {0, 9, 8, 0, 0, 0, 0},
//   {0, 255, 9, 0, 0, 0, 0},
//   {0, 0, 0, 0, 0, 0, 0}
// };

// //===========================================================================
// //Funções
// //===========================================================================
void rosaDosVentos() {
  if (bussola > -1 && bussola < 1) {
    orientacao = 'N';
  }
  else if (bussola > 89 && bussola < 91) {
    orientacao = 'L';
  }
  else if ((bussola > 179 && bussola < 180) || (bussola < -179 && bussola > -180)) {
    orientacao = 'S';
  }
  else if (bussola < -89 && bussola > -91) {
    orientacao = 'O';
  }
  else {
    orientacao = 'Z';
  }
}

// void calculoNumeroDaRota () {
//   for (int i = 0; i < linhas; i++) {
//     for (int j = 0; j < colunas; j++) {
//       if (mapa[i][j] > numeroDaRota && mapa[i][j] != 255) numeroDaRota = mapa[i][j];
//     }
//   }
// }

// void posicaoRobo() {
//   for (int i = 0; i < linhas; i++) {
//     for (int j = 0; j < colunas; j++) {
//       if (mapa[i][j] == 255) {
//         roboI = i;
//         roboJ = j;
//         break;
//       }
//     }
//   }
// }

// void wavefront() {
//   if (numeroDaRota < 1){ 
//     controle('s');
//     // Serial.print("Cheguei ao destino.");
//     while(1);
//   }
//   else {
//     rosaDosVentos();
//     switch (orientacao) {
//       case 'N':
//         if (mapa[roboI - 1][roboJ] == numeroDaRota ) {
//           // Serial.print("In: wavefront N frente  \t");
//           moverParaFrente();
//         }
//         else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
//           // Serial.print("In: wavefront N girar D  \t");
//           girar('D');
//         }
//         else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
//           girar('E');
//         }
//         else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
//           girar('T');
//         }
//         break;
//       case 'S':
//         if (mapa[roboI + 1][roboJ] == numeroDaRota ) {
//           moverParaFrente();
//         }
//         else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
//           girar('D');
//         }
//         else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
//           girar('E');
//         }
//         else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
//           girar('T');
//         }
//         break;

//       case 'L':
//         if (mapa[roboI][roboJ + 1] == numeroDaRota ) {
//           sSerial.print("In: wavefront L frente  \t");
//           moverParaFrente();
//         }
//         else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
//           girar('D');
//         }
//         else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
//           girar('E');
//         }
//         else if (mapa[roboI][roboJ - 1] == numeroDaRota) {
//           girar('T');
//         }
//         break;

//       case 'O':
//         if (mapa[roboI][roboJ - 1] == numeroDaRota ) {
//           moverParaFrente();
//         }
//         else if (mapa[roboI - 1][roboJ] == numeroDaRota) {
//           girar('D');
//         }
//         else if (mapa[roboI + 1][roboJ] == numeroDaRota) {
//           girar('E');
//         }
//         else if (mapa[roboI][roboJ + 1] == numeroDaRota) {
//           girar('T');
//         }
//         break;

//       default: rosaDosVentos();
//     }
//   }
// }

// void setupAlgoritmo() {
//   rosaDosVentos();
//   calculoNumeroDaRota();
//   posicaoRobo();
// }
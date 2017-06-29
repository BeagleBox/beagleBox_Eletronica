# No caso eu to mandando uma mensagem "aviso" e "Desolocamento" 
# pra identificar o tipo de dado que eu estou enviando,
# a questão do nivel de bateria, e da balança a agente vai pegar da propria placa,
# ou seja, vai tá disponível a todo momento, não vai vir do arduino 


import RPi.GPIO as GPIO
import time
import serial

#Configura a serial e a velocidade de transmissao
ser = serial.Serial("/dev/ttyAMA0", 115200)

GPIO.setmode(GPIO.BOARD)

#Entrada do sinal da balança
GPIO.setup(10,GPIO,IN)
#Entrada do sinal do nivel de bateria
GPIO.setup(12,GPIO,IN)

ser.write(identificadorDeCaminho) 

while(1):

        balanca = GPIO.input(10)

        nivelBateria = GPIO.input(12)

        resposta = ser.readline()

        if (resposta == "Aviso") :
                aviso = ser.readline() #INICIO, FIM, OBSTRUIDO
               
        if (resposta == "Deslocamento") :
                deslocamento = ser.readline() #NUMERO DE VEZES QUE DESLOCOU NO EIXO X.
        
        if (trancar == 1) :
                ser.write(trancar)
        
        time.sleep(0.5)

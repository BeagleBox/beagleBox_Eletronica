#include <I2Cdev.h>

#include <Wire.h>

#include "Thread.h"
#include "ThreadController.h"
#include "ArduinoSensors.h"
#include "sensors/MPUSensor.h"
#include "sensors/PingUltrasonic.h"


ThreadController cpu;

ThreadController sensors;

MPUSensor bussola();
PingUltrasonic sensorUltrassom(12);

Thread controller;


void setup() {
	sensors.setInterval(0);
	bussola.setInterval(50);
	sensorUltrassom.setInterval(50);

	sensors.add(&bussola);
	sensors.add(&sensorUltrassom);

	controller.setInterval(50);
	
	cpu.add(&sensors);
	cpu.add(&controller);
}

bool roboParado = true;

void loop() {

	if (roboParado) sensors.enabled = false;
	else sensors.enabled = true;
	
	cpu.run();

	Serial.print("Sensor MPU: ");
	Serial.println(bussola.getAngle());

	Serial.print("Sensor Ultrassom: ");
	Serial.println(sensorUltrassom.getDistance());
	 
}

#include "Hardware.h"

void Hardware::motorStep(){

	static unsigned char count = 0;

	if(count == 0){
		digitalWrite(ENABLE, LOW);
		digitalWrite(MOTOR_PIN1, LOW);
		digitalWrite(MOTOR_PIN2, HIGH);
		digitalWrite(MOTOR_PIN3, LOW);
		digitalWrite(MOTOR_PIN4, HIGH);
		count++;
	}else if(count == 1){
		digitalWrite(ENABLE, LOW);
		digitalWrite(MOTOR_PIN1, HIGH);
		digitalWrite(MOTOR_PIN2, LOW);
		digitalWrite(MOTOR_PIN3, LOW);
		digitalWrite(MOTOR_PIN4, HIGH);
		count++;
	}else if(count == 2){
		digitalWrite(ENABLE, LOW);
		digitalWrite(MOTOR_PIN1, HIGH);
		digitalWrite(MOTOR_PIN2, LOW);
		digitalWrite(MOTOR_PIN3, HIGH);
		digitalWrite(MOTOR_PIN4, LOW);
		count++;
	}else{
		digitalWrite(ENABLE, LOW);
		digitalWrite(MOTOR_PIN1, LOW);
		digitalWrite(MOTOR_PIN2, HIGH);
		digitalWrite(MOTOR_PIN3, HIGH);
		digitalWrite(MOTOR_PIN4, LOW);
		count = 0;
	}
	delay(MOTOR_DELAY);
}


void Hardware::motorInit(){

    wiringPiSetup(); 
	pinMode(MOTOR_PIN1, OUTPUT);
	pinMode(MOTOR_PIN2, OUTPUT);
	pinMode(MOTOR_PIN3, OUTPUT);
	pinMode(MOTOR_PIN4, OUTPUT);
	pinMode(ENABLE, OUTPUT);
}

void Hardware::laserOn(){

	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, HIGH);	     
}

void Hardware::laserOff(){

	pinMode(LASER_PIN, OUTPUT);
	digitalWrite(LASER_PIN, LOW);	     
}





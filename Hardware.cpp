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

void Hardware::motorMicroStep(){

    static unsigned char count = 0;

    if(count == 0){
        digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, LOW);//!x
        digitalWrite(MOTOR_PIN2, HIGH);//x
        digitalWrite(MOTOR_PIN3, LOW);//!y
        digitalWrite(MOTOR_PIN4, HIGH);//y
        count++;
    }else if (count == 1){
        digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, LOW);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN3, LOW);
        digitalWrite(MOTOR_PIN4, HIGH);
        count++;		
    }else if(count == 2){
        digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, HIGH);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN3, LOW);
        digitalWrite(MOTOR_PIN4, HIGH);
        count++;
    }else if (count == 3){
        digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, HIGH);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN3, LOW);
        digitalWrite(MOTOR_PIN4, LOW);
        count++;		
    }else if(count == 4){
		digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, HIGH);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN3, LOW);
        digitalWrite(MOTOR_PIN4, HIGH);
        count++;
    }else if (count == 5){
  		digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, LOW);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN3, HIGH);
        digitalWrite(MOTOR_PIN4, LOW);
        count++;		
    }else if (count == 6){
        digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, LOW);
        digitalWrite(MOTOR_PIN2, HIGH);
        digitalWrite(MOTOR_PIN3, HIGH);
        digitalWrite(MOTOR_PIN4, LOW);
        count++;		
    }else {
        digitalWrite(ENABLE, LOW);
        digitalWrite(MOTOR_PIN1, LOW);
        digitalWrite(MOTOR_PIN2, HIGH);
        digitalWrite(MOTOR_PIN3, LOW);
        digitalWrite(MOTOR_PIN4, LOW);
        count = 0;
    }
    delay(MOTOR_DELAY);
}

void Hardware::hardwareInit(){

    wiringPiSetup(); 
    pinMode(MOTOR_PIN1, OUTPUT);
    pinMode(MOTOR_PIN2, OUTPUT);
    pinMode(MOTOR_PIN3, OUTPUT);
    pinMode(MOTOR_PIN4, OUTPUT);
    pinMode(ENABLE, OUTPUT);
    pinMode(LASER2_PIN, OUTPUT);
    pinMode(LASER1_PIN, OUTPUT);
}

void Hardware::laserOn(int laser){
    
    if(laser == 1){
        digitalWrite(LASER1_PIN, LOW);
    }else{
        digitalWrite(LASER2_PIN, LOW);
    }
             
}

void Hardware::laserOff(int laser){

    if(laser == 1){
        digitalWrite(LASER1_PIN, HIGH);
    }else{
        digitalWrite(LASER2_PIN, HIGH);
    }	     
}





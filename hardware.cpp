#include "hardware.h"

int hardware:: motor_run(){



static int count =0;
        
            if(count == 0 )

               {
                digitalWrite(Enable, LOW);
                digitalWrite(MotorPin1, LOW);
		digitalWrite(MotorPin2, HIGH);
		digitalWrite(MotorPin3, LOW);
                digitalWrite(MotorPin4, HIGH);
             count ++;

                }
else if(count == 1){
                digitalWrite(Enable, LOW);
                digitalWrite(MotorPin1, HIGH);
		digitalWrite(MotorPin2, LOW);
		digitalWrite(MotorPin3, LOW);
                digitalWrite(MotorPin4, HIGH);
                 count ++;

                  }
else if(count == 2){
                digitalWrite(Enable, LOW);
                digitalWrite(MotorPin1, HIGH);
		digitalWrite(MotorPin2, LOW);
		digitalWrite(MotorPin3, HIGH);
                digitalWrite(MotorPin4, LOW);
                count ++;
                 }
else   {
                digitalWrite(Enable, LOW);
                digitalWrite(MotorPin1, LOW);
		digitalWrite(MotorPin2, HIGH);
		digitalWrite(MotorPin3, HIGH);
                digitalWrite(MotorPin4, LOW);
                count =0;

             }
         
return count;
                


}


int hardware::motor_init(){

       if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		
		return 1; 
	}
        pinMode(MotorPin1, OUTPUT);
	pinMode(MotorPin2, OUTPUT);
	pinMode(MotorPin3, OUTPUT);
        pinMode(MotorPin4, OUTPUT);
	pinMode(Enable, OUTPUT);
	
     
   
        


}
int hardware::lazer(){

 while(1){ 
                 pinMode(lazer_pin, OUTPUT);
                 digitalWrite(lazer_pin, HIGH);
	             
             }

 return 0;


}






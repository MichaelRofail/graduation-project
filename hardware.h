#include <wiringPi.h>

// connect the pins from GPIO0 TO GPIO5 
#define MotorPin1    0 // IN1
#define MotorPin2    1// IN2
#define MotorPin3    2 // IN3
#define MotorPin4    3 //IN4

#define Enable    4// ENABLE PIN
#define lazer_pin   5


class hardware{
public: 
       static int motor_run() ;
       static int motor_init();
       static int lazer();

};
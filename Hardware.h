#include <wiringPi.h>

// connect the pins from GPIO0 TO GPIO5 
#define MOTOR_PIN1    10 // IN1
#define MOTOR_PIN2    11 // IN2
#define MOTOR_PIN3    12 // IN3
#define MOTOR_PIN4    13 // IN4
#define ENABLE        14 // ENABLE PIN

#define LASER1_PIN   15
#define LASER2_PIN   16
#define MOTOR_DELAY 500


class Hardware{
public: 
    static void motorStep(void);
    static void motorMicroStep(void);
    static void hardwareInit(void);
    static void laserOn(int laser);
    static void laserOff(int laser);
};
#include <wiringPi.h>

// connect the pins from GPIO0 TO GPIO5 
#define MOTOR_PIN1    0 // IN1
#define MOTOR_PIN2    1 // IN2
#define MOTOR_PIN3    2 // IN3
#define MOTOR_PIN4    3 // IN4
#define ENABLE        4 // ENABLE PIN

#define LASER1_PIN   5
#define LASER2_PIN   6
#define MOTOR_DELAY 500


class Hardware{
public: 
    static void motorStep(void);
    static void motorMicroStep(void);
    static void hardwareInit(void);
    static void laserOn(int laser);
    static void laserOff(int laser);
    static void motorOff(void);
};
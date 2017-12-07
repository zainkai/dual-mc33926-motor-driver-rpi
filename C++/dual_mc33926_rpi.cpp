#include "dual_mc33926_rpi.hpp"

Motor::Motor(int pulsewmPin,int dirPin, int enPin){
    pwmPin = pulsewmPin;
    directionPin = dirPin;
    enablePin = enPin;
    speed = 0;

    //need eces to describe what some of this does.
    pinMode(pwmPin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(_maxSpeed);
    pwmSetClock(2);

    pinMode(directionPin,OUTPUT);
    pinMode(enablePin,OUTPUT);
}

int main(int argc, char** argv)
{
    if(wiringPiSetupGpio() == -1){
        
    }
    

    printf("wiringPi is working!\n");

    return 0;
}
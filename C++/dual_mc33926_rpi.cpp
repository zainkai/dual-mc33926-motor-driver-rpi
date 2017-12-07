#include "dual_mc33926_rpi"

Motor::Motor(int pulsewmPin,int dirPin, int enPin){
    pwmPin = pulsewmPin;
    directionPin = dirPin;
    enablePin = enPin;
    speed = 0;

    //need eces to describe what some of this does.
    pinMode(pwmPin, GPIO.PWM_OUTPUT);
    pwmSetMode(wiringpi.GPIO.PWM_MODE_MS);
    pwmSetRange(MAX_SPEED);
    pwmSetClock(2);

    pinMode(directionPin,GPIO.OUTPUT);
    pinMode(enablePin,GPIO.OUTPUT);
}

int main(int argc, char** argv)
{
    if(wiringPiSetupGpio() == -1){
        
    }
    

    printf("wiringPi is working!\n");

    return 0;
}
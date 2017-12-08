#include "dual_mc33926_rpi.hpp"

Motor::Motor(int pulsewmPin,int dirPin, int enPin){
    pwmPin = pulsewmPin;
    directionPin = dirPin;
    enablePin = enPin;

    speed = 0;
    enabled = false;
    motorDirection = FORWARD;

    //need eces to describe what some of this does.
    pinMode(pwmPin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(_maxSpeed);
    pwmSetClock(2);

    pinMode(directionPin,OUTPUT);
    pinMode(enablePin,OUTPUT);
}

Motor::enable(){
    digitalWrite(enablePin, 1);
    enabled = true;
}

Motor::disable(){
    digitalWrite(enablePin, 0);
    enabled = false;
}

Motor::setSpeed(int newSpeed, motorDirection newdir){
    direction = newdir

    if(-newSpeed > _maxSpeed || newSpeed > _maxSpeed){
        speed = _maxSpeed;
    }
    else if(newSpeed < 0){
        speed = -newSpeed;
    }
    else{
        speed = newSpeed;
    }

    digitalWrite(directionPin, direction);
    pwmWrite(pwmPin, speed);
}

Motor::getDirection(){
    return direction;
}

Motor::getSpeed(){
    return speed;
}

Motor::getEnabled(){
    return enabled;
}

int main(int argc, char** argv)
{
    if(wiringPiSetupGpio() == -1){
        
    }
    

    printf("wiringPi is working!\n");

    return 0;
}
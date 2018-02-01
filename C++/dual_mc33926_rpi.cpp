#include "dual_mc33926_rpi.hpp"

void IO_INITIALIZE() {
    //PWM
    pinMode(12, PWM_OUTPUT);
    pinMode(13, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(_MAXSPEED);
    pwmSetClock(2);

    pinMode(22,OUTPUT);
    pinMode(23,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);

}

Motor::Motor(int pulsepwmPin,int dirPin, int enPin){
    pwmPin = pulsepwmPin;
    directionPin = dirPin;
    enablePin = enPin;

    speed = 0;
    enabled = false;
    direction = FORWARD;
}

bool Motor::enable(){
    digitalWrite(enablePin, 1);
    enabled = true;

    return enabled;
}

bool Motor::disable(){
    digitalWrite(enablePin, 0);
    enabled = false;

    return enabled;
}

int Motor::setSpeed(int newSpeed, motorDirection newdir){
    direction = newdir;

    if(newSpeed > _MAXSPEED || newSpeed > _MAXSPEED){
        speed = _maxSpeed;
    }
    else if(newSpeed < -_MAXSPEED){
        speed = -_MAXSPEED;
    }

    digitalWrite(directionPin, direction);
    pwmWrite(pwmPin, speed);

    return speed;
}

motorDirection Motor::getDirection(){
    return direction;
}

int Motor::getSpeed(){
    return speed;
}

bool Motor::getEnabled(){
    return enabled;
}

//make inputs an interfact later.
motorControl::motorControl() {
    motor1 = new Motor(12,24,22);
    motor2 = new Motor(13,25,23);
}

void motorControl::enable(int speed){
    return motor1->enable() && motor2 ->enable();
}

void motorControl::disable(int speed){
    return motor1->disable() && motor2->disable();
}

void motorControl::setSpeeds(int speed1, int dir1, int speed2, int dir2){
    motor1->setSpeed(speed1,dir1);
    motor2->setSpeed(speed2,dir2);
}


int main(int argc, char** argv)
{
    if(wiringPiSetupGpio() == -1){
        printf("someting went wrong!\n");
        return 1;
    }

    IO_INITIALIZE();
    
    printf("wiringPi is working!\n");

    motorControl *driver = new motorControl();
    driver->setSpeeds(480,FORWARD,480,FORWARD);

    printf("ran some functions\n");

    return 0;
}
/**************************************************************************
** Author: Kevin Turkington
** 12/7/17
** Description: Motor driver for raspberry PI using the wiringPi library.
** For Oregon State Universitys, USLI competition rover 
** http://osuusli.com/
** Based off of https://github.com/pololu/dual-mc33926-motor-driver-rpi
**************************************************************************/

#include <stdio.h>
#include <wiringPi.h>

using namespace std;

#ifndef DUAL_MC33926_RPI
#define DUAL_MC33926_RPI

const static _maxSpeed = 480; // 19.2 MHz / 2 / 480 = 20 kHz

bool ioInitialize();

class Motor()
{
    private:
        int pwmPin;
        int directionPin;
        int enablePin;

        int speed;
        int enabled;
        int direction;
    public:
        Motor(int,int,int);
        void enable();
        void diable();
        int setSpeed(int);
        int setDirection(int);

        int getDirection();
        int getSpeed();
        int getEnabled();
}

class motorControl()
{
    private:
        Motor leftMotor;
        Motor rightMotor;
    public:
        motorControl(int,int,int,int,int,int);

        void forward(int);
        void backward(int);
        void left(int,int);
        void right(int,int);
        void stop();
}

#endif




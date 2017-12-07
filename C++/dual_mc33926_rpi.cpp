#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char** argv)
{
    if(wiringPiSetup() == -1){
        exit(1)
    }
    

    printf("wiringPi is working!\n");

    return 0;
}
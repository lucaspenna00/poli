#include "mbed.h"

InterruptIn  ENCOD1(PTD4);
InterruptIn  ENCOD2(PTA12);

DigitalOut IN1(PTC7);
DigitalOut IN2(PTC0);
DigitalOut IN3(PTC3);
DigitalOut IN4(PTC4);

void go_forward(){

     IN1 = 1;
     IN2 = 0;

     IN3 = 1;
     IN4 = 0;
}

void go_backward(){

     IN1 = 0;
     IN2 = 1;

     IN3 = 0;
     IN4 = 1;
}

void go_forward_right(){

     IN1 = 1;
     IN2 = 0;

     IN3 = 1;
     IN4 = 1;
}

void go_backward_right(){

     IN1 = 0;
     IN2 = 1;

     IN3 = 1;
     IN4 = 1;
}


void go_forward_left(){


     IN1 = 1;
     IN2 = 1;

     IN3 = 1;
     IN4 = 0;

}

void go_backward_left(){


     IN1 = 1;
     IN2 = 1;

     IN3 = 0;
     IN4 = 1;

}

void brake(){


     IN1 = 1;
     IN2 = 1;

     IN3 = 1;
     IN4 = 1;

}


int pulses1 = 0, pulses2 = 0;

void count1(){
    pulses1++;
    wait(0.005);
}


void count2(){
    pulses2++;
    wait(0.005);
}

int main()
{
    ENCOD1.rise(&count1);

    ENCOD2.rise(&count2);

    while(1){

        go_forward();

        printf("Pulses 1: %d\n\r", pulses1);
        printf("Pulses 2: %d\n\r", pulses2);
    }
}

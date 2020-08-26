#include "mbed.h"

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

int main() {

    while(1) {

        brake();

    }
}

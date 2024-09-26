#include <stdio.h>
#include "rc-switch/RCSwitch.h"


void Socket_A_on(RCSwitch *  mySwitch)
{
  mySwitch->send(8180396, 24);
  delay(10);  

  mySwitch->send(7727212, 24);
  delay(10);
  
  mySwitch->send(8368924, 24);
  delay(10);  

  mySwitch->send(7352412, 24);
  delay(10);  

}

void Socket_A_off(RCSwitch *  mySwitch)
{
  mySwitch->send(8006444, 24);
  delay(10);

  mySwitch->send(7447948, 24);
  delay(10);

  mySwitch->send(8322236, 24);
  delay(10);

  mySwitch->send(8214908, 24);
  delay(10);

}



int main(int argc, char *argv[]) {
      
    printf("Starting senddemo\n");
    int PIN = 25;

    if (wiringPiSetup () == -1) 
    {
        printf("ERROR WIRING PI SETUP \n");
        return 1;
    }
     RCSwitch mySwitch = RCSwitch();

    // Transmitter is connected
    mySwitch.enableTransmit(PIN);

    // Optional set pulse length.
    // mySwitch.setPulseLength(320);
    
    // Optional set protocol (default is 1, will work for most outlets)
    mySwitch.setProtocol(5);
    
    // Optional set number of transmission repetitions.
     mySwitch.setRepeatTransmit(15);

    Socket_A_off(&mySwitch);
    printf("done !! \n");
    return 0;
}


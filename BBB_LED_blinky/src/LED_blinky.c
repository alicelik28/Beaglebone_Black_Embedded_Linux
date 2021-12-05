#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

#define NUMBER_OF_BLINK 5

int main (void)
{
 int i  =  0;
 int LED = 0;

 // set direction out
 LED=open("/sys/class/gpio/gpio67/direction",O_RDWR);
 write(LED,"out",3);
 close(LED);
 LED=open("/sys/class/gpio/gpio67/value",O_WRONLY);

 for(i=0; i<NUMBER_OF_BLINK; i++)
 {
  // LED On
  write(LED,"1",1);
  sleep(1);
  // LED off;
  write(LED,"0",1);
  sleep(1);
 }
 close(LED);

 printf("LED Blink program is complete!\n");
} // end of main

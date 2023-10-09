/*************************************************************************************************
                            Chasing LEDs
                            ============
In this project 4 LEDs are connected to PORTB of a PIC18F4520 microcontroller
and the microcontroller is operated from a 4MHz resonator. The program turns on
the LEDs in an anti-clockwise manner with one second delay between each output.
The net result is that the LEDs seem to be chasing each other.


 * File:   main.c
 * Author: Ahmad Rashed
 * Created on 8. Oktober 2023
***************************************************************************************************/

#include <xc.h>

#pragma config OSC = XT
#pragma config WDT = OFF
#pragma config LVP = OFF

void delay_seconds(unsigned int seconds) {
  //  Approximate delay
  unsigned int iterations = seconds * 10000;
  for (unsigned int i = 0; i < iterations; i++) {
    __asm__(
        "counter_l      equ                 0x24\n\t"
        "movlw          0x1D\n\t"
        "movwf          counter_l\n\t"
        "inner:         decfsz              counter_l\n\t"
        "bra		    inner\n\t"
        "nop");
  }
}

void main(void) {
  TRISB = 0;
  PORTB = 0;
  int i = 1;
  while (1) {
    while (i < 16) {
      PORTB = i;
      i = i << 1;
      if (i < 16) {
        delay_seconds(1);
      }
    }
    while (i > 1) {
      i = i >> 1;
      PORTB = i;
      if (i > 1) {
        delay_seconds(1);
      }
    }
  }

  return;
}

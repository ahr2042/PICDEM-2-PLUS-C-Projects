/************************************************************************************************
                                SIMPLE DICE
                                ===========
In this project 7 LEDs are connected to PORTC of a PIC18F4520 microcontroller
and the microcontroller is operated from a 4MHz resonator. The LEDs are
organized as the faces of a real dice. When a push-button switch connected to
RB0 is pressed a dice pattern is displayed on the LEDs. The display remains in
this state for 3 seconds and after this period the LEDs all turn OFF to indicate
that the system is ready for the button to be pressed again..


 * File:   main.c
 * Author: Ahmad Rashed
 * Created on 9. Oktober 2023
*************************************************************************************************/

#include <stdlib.h>
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

unsigned random_fun(unsigned x) {
  srand(x);

  return rand() % 6;
}

void main(void) {
  unsigned char pattern[] = {0b00001000, 0b00100010, 0b00101010,
                             0b01010101, 0b01011101, 0b01110111};
  TRISD = 0;  // LEDs connected to RD0 to RD6
  PORTD = 0;
  unsigned i = 0;

  // INITIALIZING PORTB
  __asm__(
      "CLRF PORTB\n\t"
      "CLRF LATB\n\t"
      "MOVLW 0Fh\n\t"
      "MOVWF ADCON1\n\t"
      "MOVLW 0CFh\n\t"
      "MOVWF TRISB");  // Set RB<3:0> as inputs

  while (1) {
    while (PORTB % 2 != 0) {
    }

    PORTD = pattern[random_fun(i++)];
    delay_seconds(3);
    PORTD = 0;
  }

  return;
}

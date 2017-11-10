#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


void main(void){
    configureClocks();
    switch_init(); //to make the switches work with the leds, we call switch_init 
    led_init();     //calls led_init to make the leds work with the buttons
    buzzer_init();  //call to buzzer_init to make the buzzer work 
    or_sr(0x18);  // CPU off, GIE on
} 

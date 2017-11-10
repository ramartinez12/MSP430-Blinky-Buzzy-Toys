#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  //led_update();
  dim_update(); // this method changes dinamically the leds of the board when bottons pressed
}

void dim_update(){ //this method is based on the original code but it has if and else statements that make the leds change, from bright to dimmed
    if(switch_state_changed){
      if(dim_state_down){
      char ledFlags = 1; /* by default, no LEDs on */

    ledFlags |= dim_state_down ? LED_GREEN : 0;
    ledFlags |= dim_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
      } else {
          char ledFlags = 0; /* by default, no LEDs on */

    ledFlags |= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    
    if(switch_state_down){
        P1OUT ^= ledFlags; // used xor to dim the leds
    } else if(dim_state_down && switch_state_down){
        P1OUT |= ledFlags;
    }

    }
}
  switch_state_changed = 0;
}

void led_update(){
  if (switch_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */

    ledFlags ^= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : LED_RED;

    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  
  switch_state_changed = 0;
}


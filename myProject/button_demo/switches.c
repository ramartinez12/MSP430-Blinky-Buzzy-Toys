#include <msp430.h>
#include "switches.h"
#include "led.h"

char switch_state_down, switch_state_changed, dim_state_down; /* effectively boolean */
char S1, S2, S3, S4; /*these variables are used for the buzzer tone of each button*/

static char 
switch_update_interrupt_sense()
{
  char p1val = P2IN; //used P2IN to bridge the 4 buttons to the msp430
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();	/* to initially read the switches */
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  dim_state_down |= (p1val & SW1) ? 0 : 1;   /* 0 when SW1 is up */
  switch_state_down |= (p1val & SW2) ? 0 : 1; // had to create other lines of the same code for the other 3 buttons
  dim_state_down |= (p1val & SW3) ? 0 : 1;
  switch_state_down |= (p1val & SW4) ? 0 : 1;
  S1 = (p1val & SW1) ? 0 : 1; //the variables used here are used for the buzzer file to know which tone to play for the given button
  S2 = (p1val & SW2) ? 0 : 1;
  S3 = (p1val & SW3) ? 0 : 1;
  S4 = (p1val & SW4) ? 0 : 1;
  switch_state_changed = 1;
  dim_update();
  //led_update();
    
}

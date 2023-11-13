#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"

#define LED_RED BIT6               // P1.6
#define LED_GREEN BIT0             // P1.0
#define LEDS (BIT0 | BIT6)

// define switches
#define SW1 BIT0
#define SWITCHES (BIT0)

void main(void)
{

  P1DIR |= LEDS;
  P1OUT &= ~LEDS;/* leds initially off */

  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */

  configureClocks();
  enableWDTInterrupts();
  or_sr(0x18);  // CPU off, GIE on
}

void
switch_interrupt_handler()
{
  char p2val = P2IN;/* switch is in P1 */

  //update switches on press
  P2IES |= (p2val & SWITCHES);

  P2IES &= (p2val | ~SWITCHES);


  if (p2val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {    
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

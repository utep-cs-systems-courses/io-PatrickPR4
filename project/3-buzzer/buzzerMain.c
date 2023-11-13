#include <msp430.h>
#include "../../demos/timerLib/libTimer.h"
#include "buzzer.h"

int main() {
  configureClocks();
  buzzer_init();
  buzzer_set_period(1000);/* start buzzing!!! 2MHz/1000 = 2kHz*/

  or_sr(0x18);          // CPU off, GIE on
}

int cycles, cyclesMin = 1000, cyclesMax = 2500;
int tone1Time = 0, tone1Min = 100, tone1Max = 200;
void tone1()
{
  //change pitch of tone 1
  if (tone1Time <= tone1Min) cycles = cyclesMin;
  else if (tone1Time  <= tone1Max) cycles = cyclesMax;
}

int tone2Time = 0, tone2Min = 1500, tone2Max = 3500;

void tone2()
{
  //tone2 intervals
  if(tone2Time >= tone2Min && tone2Time <= tone2Max){
    if(cycles <= cyclesMin) cycles = cyclesMax; //reset low pitch
    else cycles -=5;      
  }

void
__interrupt_vec(WDT_VECTOR) WDT()
{
  tone1();
  if(tone1Interval > tone1Max) tone2();

  tone1Interval++; //increase for tone2 to happen

  tone2Time++;
  buzzer_set_period(cycles);
}

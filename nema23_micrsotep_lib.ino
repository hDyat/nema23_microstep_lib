#include "NEMA23.h"
#define step_pin 7
#define dir_pin 8

NEMA23 nema23(step_pin, dir_pin);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    nema23.setInstr();
  }
  
  Serial.println(nema23.getInstr());
  nema23.controller();
  delay(20);
}

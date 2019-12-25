#include <TM1637Display.h>

//#define _TM1637Display

const int DIO = 6;
const int CLK = 5;

double rez = 314;

TM1637Display display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
  display.setBrightness(7);
  display.showNumberDec(rez);
}

void loop() {
  // put your main code here, to run repeatedly:
  display.showNumberDec(rez);
}

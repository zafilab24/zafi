#include <TimedAction.h>

  const int trig = 9;
  const int echo = 10;

  long d = -1, t;

  const int c = 343; // [m/s]
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(trig, LOW);
}

  TimedAction acq = TimedAction(5000,acquisition);
  TimedAction comp = TimedAction(1, computing);

void acquisition() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(trig, LOW);
  t = pulseIn(echo, HIGH);
}

void computing() {
  d = c*t/20000; // [cm]
  Serial.println(d);
}

void loop() { 
  
  acq.check();
  comp.check();
  // delay(1000);
}

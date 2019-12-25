#include <TimedAction.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

TimedAction pantaThread = TimedAction(3000,Panta);

void Kole() {
  Serial.println("Ja sam Kole");
 /* for (int i = 0; i < 1000; i++) {
    Serial.println("Ne dam nikom procesor");
    pantaThread.check();
  } */ 
}

void Panta() {
    Serial.println("Ja sam Panta");
}

TimedAction koleThread = TimedAction(700,Kole);


void loop() {
    koleThread.check();
    pantaThread.check();
    Serial.println("Cofi");
    delay(50);
}

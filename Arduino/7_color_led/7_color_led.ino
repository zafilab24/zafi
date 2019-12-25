int neg =  13;    // +LED connected to digital pin 13
int pos =  12;    // -LED connected to digital pin 12
int crtl =  11;  // control coonected to digital pin 11

// The setup() method runs once, when the sketch starts

void setup()   {                
  // initialize the digital pin as an output:
  pinMode(neg, OUTPUT);
  pinMode(pos, OUTPUT);
  pinMode(crtl, OUTPUT);
  digitalWrite(pos, HIGH);    // set the LED on
  digitalWrite(neg, LOW);   // set the LED off
  digitalWrite(crtl,LOW);  //ser the crtl off
  delay(15000);                  // wait for 15 second
}
// the loop() method runs over and over again,
// as long as the Arduino has power

void loop()                     
{
digitalWrite(crtl, HIGH);
delay(250);
digitalWrite(crtl, LOW);
delay(250);

  

}

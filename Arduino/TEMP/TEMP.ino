float t;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  t = analogRead(A2);
  Serial.println(t);
  delay(500);
}

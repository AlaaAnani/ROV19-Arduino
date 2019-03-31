void setup() {
  // put your setup code here, to run once:
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
pinMode(23, OUTPUT);
pinMode(25, OUTPUT);

pinMode(27, OUTPUT);
pinMode(29, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//digitalWrite(10, HIGH);
//digitalWrite(11, HIGH);
//digitalWrite(12, HIGH);
digitalWrite(13, HIGH);
//digitalWrite(23, HIGH);
//digitalWrite(25, LOW);

//digitalWrite(27, HIGH);
//digitalWrite(29, LOW);

delay(1000);
//digitalWrite(10, LOW);
//digitalWrite(11, LOW);
//digitalWrite(12, LOW);
digitalWrite(13, LOW);
//digitalWrite(23, LOW);
//digitalWrite(25, HIGH);

//digitalWrite(27, LOW);
//digitalWrite(29, HIGH);
delay(1000);

}

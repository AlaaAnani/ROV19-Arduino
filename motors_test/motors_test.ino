#include "Servo.h"

Servo A, B, C, D, E, F;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
A.attach(2);
B.attach(3);
C.attach(4);
D.attach(5);
E.attach(6);
F.attach(7);

A.writeMicroseconds(1500);
B.writeMicroseconds(1500);
C.writeMicroseconds(1500);
D.writeMicroseconds(1500);
E.writeMicroseconds(1500);
F.writeMicroseconds(1500);
delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
/*A.writeMicroseconds(1600);
B.writeMicroseconds(1600);
C.writeMicroseconds(1600);
D.writeMicroseconds(1600);
E.writeMicroseconds(1600);
F.writeMicroseconds(1600);*/
}

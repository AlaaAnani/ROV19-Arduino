#define MAX_BUF 128

#include "Servo.h"
Servo left, right;
int motor_l= 1450 , motor_r= 1450;


char buffer[MAX_BUF];
int i = 0;
char c = 'K';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  left.attach(2);
  right.attach(3);

  left.writeMicroseconds(1450);
  right.writeMicroseconds(1450);
  delay(1000);
}

void loop() 
{
    if (Serial.available())
    {      
      Serial.println("Im in serial");
      c = Serial.read();

      if (i< MAX_BUF -1)
      buffer[i++] = c;
             
      
      if (c== 'K')
      {
        i=0;          
        ParseString(buffer);
        Serial.println(buffer);
        move_micro();
      }
    }
    
    
}


void ParseString(String inp) 
{
  motor_l = (inp.substring(inp.indexOf('X') + 1, inp.indexOf('Y'))).toInt(); // Left Micro
  motor_r = (inp.substring(inp.indexOf('Y') + 1, inp.indexOf('K'))).toInt(); // Right Micro
}

void move_micro()
{
  left.writeMicroseconds(motor_l);
  right.writeMicroseconds(motor_r);
  //Serial.println(motor_l);
  //Serial.println(motor_r);
  
}

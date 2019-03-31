#include <Wire.h>
#include "Servo.h"
//#include "MPU6050.h"
#include "Declarations.h"


//SERIAL
Servo A, B, C, D, E, F;
#define MAX_BUF 128
char buffer[MAX_BUF];
//int i = 0, r=0;
//char c, d;
char rec[MAX_BUF];
int motorvalA = 1500, motorvalB = 1500, motorvalC = 1500, motorvalD = 1500, motorvalE = 1500, motorvalF = 1500;
String rec_str, req_sensors, sensors_str;
char Z[] = "Z";
//END OF SERIAL

#define DC_motor_pin1 23
#define DC_motor_pin2 25
//if not, 27 and 29
#define ARM_pin 10
#define led 13

char arm_prev_state = '0';
char led_prev_state = '0';

void setup(void) 
{
  Serial.begin(57600);
  Serial1.begin(57600);
   
  
    init_thrusters();
    pinMode(DC_motor_pin1, OUTPUT);
    pinMode(DC_motor_pin2, OUTPUT);
    pinMode(ARM_pin, OUTPUT); //ARM
    pinMode(led,OUTPUT);

}





void loop(void) 
{
    // Read serially from ros and write to the motors
    read_from_ros();
    
    
    //Metal Sensor
    Metal_Sensor_Value = analogRead(Metal_Sensor_Pin);
    Metal_Sensor_Value = (float) Metal_Sensor_Value*100/1024.0;
 


    String ToSendSerially = 'A'  + String(Metal_Sensor_Value)+ 'B';
    

    //1000 => Right
     if(receivedrqs[0]=='1')
      {  
         digitalWrite(DC_motor_pin1, HIGH);
         digitalWrite(DC_motor_pin2, LOW);
        
      }
      else
      {
        digitalWrite(DC_motor_pin1, LOW);
         digitalWrite(DC_motor_pin2, LOW);
      }
      
    //0100 => Left
     if(receivedrqs[1]=='1')
      {  
         digitalWrite(DC_motor_pin1, LOW);
         digitalWrite(DC_motor_pin2, HIGH);
      }
      else
      {
        digitalWrite(DC_motor_pin1, LOW);
        digitalWrite(DC_motor_pin2, LOW);
      }
     
      
    //0010 => Arm
     if(receivedrqs[2]=='1' && arm_prev_state == '0' ) //if rising edge
      {
          digitalWrite(ARM_pin, !digitalRead(ARM_pin));
      }
  
    //0001 => mag
     if(receivedrqs[3]=='1' && led_prev_state == '0')
     {
        digitalWrite(led, !digitalRead(led));
     }

     
     
     
    // ToSendSerially += Metal_Sensor_Value + 'H'; 
    arm_prev_state = receivedrqs[2];
    led_prev_state = receivedrqs[3];
      

    if(ToSendSerially.length() >0)
    {
      rec_str = ToSendSerially;
      rec_str += 'Z';
      Serial1.print(rec_str);
    }

  
    
}


// PH Data Fun
double avergearray(int* arr, int number)
{
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    //Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}



 
void read_from_ros()
{
    while (Serial1.available())
    {      
      c = Serial1.read();

      if (i< MAX_BUF -1)
      buffer[i++] = c;
      else break;
             
      
      if (c== 'K')
      {
        i=0;          
        ParseString(buffer);
        moveROV();
      }
    }
}

void init_thrusters()
{
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
   digitalWrite(13, HIGH);
  //END OF THRUSTERS
}

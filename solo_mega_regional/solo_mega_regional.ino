#include <Wire.h>
#include "Servo.h"
#include "MPU6050.h"
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

//Actuators
#define DC_motor_pin1 13
#define DC_motor_pin2 10
#define ARM_pin 11
#define led 12
char arm_prev_state = '0';
char led_prev_state = '0';


void setup(void) 
{

    Serial1.begin(57600);
    Serial2.begin(57600);
    Serial.begin (57600);  
    init_thrusters();
    init_mpu6050(); 

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
         
    //Temp Sensor
    readTemp();
  
    //input PH 
    readPH();


    //*********MPU6050    *********//
    timer = millis();
    // Read normalized values
    Vector norm = mpu.readNormalizeGyro();
    Vector normAccel = mpu.readNormalizeAccel();
    //Calculate Pitch, Roll and Yaw
    pitch = pitch + norm.YAxis * timeStep;
    roll = roll + norm.XAxis * timeStep;
    yaw = yaw + norm.ZAxis * timeStep;
    if(roll>360)    roll -= 360; //care for the change from 0-->360 or 360-->0 near to north
    if(roll<0)      roll    +=   360;
    if(yaw >360)    yaw  -= 360;
    if(yaw <0)      yaw  += 360;
    if(pitch > 360) pitch -= 360;
    if(pitch < 0)   pitch += 360;
    acc_x = normAccel.XAxis - 9.5;
    acc_y = normAccel.YAxis;
    acc_z = normAccel.ZAxis+ 2;
    
    //*********END OF MPU6050*********//


    ToSendSerially = 'A'  + String(pitch) + 'B' + String(roll)+ 'C' + String(Metal_Sensor_Value)+ 'D' + String(pHValue) + 'E';
    
/*
 100000 Right (T shapes)
 010000 Left  (T shapes) 
 001000 Arm 
 000100 LED  
 000010 Temp
 000001 Metal
 
 */

    //000010 => Temp
     if(receivedrqs[4]=='1')
        ToSendSerially += String(Tsensor) + 'G';
    //000001 => mag
     if(receivedrqs[5]=='1')
        ToSendSerially += pHValue + 'H'; 

    T_Shapes();
    //001000 ARM
    if(receivedrqs[2]=='1' && arm_prev_state == '0' ) //if rising edge
    {
          digitalWrite(ARM_pin, !digitalRead(ARM_pin));
    } 
      
    //000100 LED
    if(receivedrqs[3]=='1' && led_prev_state == '0')
    {
        digitalWrite(led, !digitalRead(led));
    }
    arm_prev_state = receivedrqs[2];
    led_prev_state = receivedrqs[3];

      

    if(ToSendSerially.length() >0)
    {
      rec_str = ToSendSerially;
      rec_str += 'Z';
      Serial.print(rec_str);
    }
    
    delay((timeStep*1000) - (millis() - timer));  
    
}
void readTemp()
{
    Vo = analogRead(ThermistorPin);
    R2 = R1 * (1023.0 / (float)Vo - 1.0);
    logR2 = log(R2);
    T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
    Tsensor = T - 273.15;
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
void T_Shapes()
{
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
}

 
void read_from_ros()
{
    while (Serial.available())
    {      
      c = Serial.read();

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
void readPH()
{
    static unsigned long samplingTime = millis();
    static unsigned long printTime = millis();   

    if(millis()-samplingTime > samplingInterval)
    {
        pHArray[pHArrayIndex++]=analogRead(SensorPin);
        if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
        //voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
        pHValue = 3.5*avergearray(pHArray, ArrayLenth)*5.0/1024+Offset;
        samplingTime=millis();
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

void init_dig_compus()
{
    Wire.beginTransmission(addr); //start talking
    Wire.write(0x0B);             // Tell the HMC5883 to Continuously Measure
    Wire.write(0x01);             // Set the Register
    Wire.endTransmission();
    Wire.beginTransmission(addr); //start talking
    Wire.write(0x09);             // Tell the HMC5883 to Continuously Measure
    Wire.write(0x1D);             // Set the Register
    Wire.endTransmission();
}

void init_mpu6050()
{
  if(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
   {   Serial.println("Could not find a valid MPU6050 sensor, check wiring!Z");
    delay(500);
  } 
  mpu.calibrateGyro();
  mpu.setThreshold(3);  
  checkSettings();
}

#define addr 0x0D                 //I2C Address for The HMC5883
#define SensorPin A1              //pH meter Analog output to Arduino Analog Input 
#define Offset 0.00               //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;   


/*MPU6050
MPU6050 mpu;
unsigned long timer = 0;
float timeStep = 0.01;
*/

// Temperature input
#define ThermistorPin 0
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
//END OF TEMPRATURE



//SERIAL
char Requested[7];
int i = 0;
String RequestedSensors = "";
String ToSendSerially = "";
String receivedrqs = "00000";
//char buffer[128];
char c;
//END OF SERIAL
// pHValue
float pHValue =0;


// Water Sensor 
float WaterSensor = 2;

  
// TEMPERATURE SENSOR
  float Tsensor = 0;
  
//Magnetometer
#define Metal_Sensor_Pin A3
int Metal_Sensor_Value = 0;

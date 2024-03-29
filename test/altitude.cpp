//code and walkthrough from https://how2electronics.com/how-to-use-tfmini-s-lidar-distance-sensor-with-arduino/#Overview
  //sensor documentation available here: https://www.sparkfun.com/products/16977 
  //  

#include <SoftwareSerial.h>
#include "TFMini.h"
TFMini tfmini;
 
SoftwareSerial SerialTFMini(2, 3);          //The only value that matters here is the first one, 2, Rx
  //pin related stuff

float wrapper_distance = -1;//global vars updated by wrapper function, -1 placeholder, hopefully the code isnt too sketchy
  //dist is in cm
float wrapper_signal_strength = -1;
  //strength can be ignored

//important computations
  //edited this function to make it a wrapper function
void getTFminiData(int* distance, int* strength)
{
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9];
  //Serial.println("Pain2");

  if (SerialTFMini.available())
  {
    rx[i] = SerialTFMini.read();
    if (rx[0] != 0x59)
    {
      i = 0;
    }
    else if (i == 1 && rx[1] != 0x59)
    {
      i = 0;
    }
    else if (i == 8)
    {
      for (j = 0; j < 8; j++)
      {
        checksum += rx[j];
      }
      if (rx[8] == (checksum % 256))
      {
        *distance = rx[2] + rx[3] * 256;
        *strength = rx[4] + rx[5] * 256;
      }
      i = 0;
    }
    else
    {
      Serial.println("Pain");
      i++;
    }
  }
  //added code to make the function a wrapper function: 
  wrapper_distance=*distance;
  wrapper_signal_strength=*strength;//updates global vars
  
}
 
 //resend ir=t
void setup()
{
  Serial.begin(115200);       //Initialize hardware serial port (serial debug port)
  while (!Serial);            // wait for serial port to connect. Needed for native USB port only
  Serial.println ("Initializing...");
  SerialTFMini.begin(TFMINI_BAUDRATE);    //Initialize the data rate for the SoftwareSerial port
  tfmini.begin(&SerialTFMini);            //Initialize the TF Mini sensor  
}
 
void loop()
{
  int distance = 0;
  int strength = 0;
 
  Serial.println("Test");
  getTFminiData(&distance, &strength);
  while (!distance)
  {
    getTFminiData(&distance, &strength);
    Serial.println(distance);
    //Serial.println(distance);

    if (distance)
    {
      Serial.println("Test distance");

      Serial.print(distance);//dist to object
      Serial.print("cm\t");
      Serial.print("signal strength: "); //signal strength (mostly ignore)
      Serial.println(strength);
      
      Serial.println(wrapper_distance);
      //(wrapper testing)
      /*Serial.println(wrapper_distance);
      Serial.println(wrapper_signal_strength);*/
    }
      //Serial.println("Test2");

  }
  delay(100);
}




//Example code for Benewake TFMini time-of-flight distance sensor. 
//library by Peter Jansen (December 11/2017)
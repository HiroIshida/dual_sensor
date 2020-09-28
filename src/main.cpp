#include "Arduino.h"
#include "ros.h"
#include <i2c_t3.h>     // Use <i2c_t3.h> for Teensy and <Wire.h> for Arduino
#include <SparkFun_LPS25HB_Arduino_Library.h> 
#include <math.h>
#include <ros.h>
#include <array>
#include "std_msgs/String.h"

LPS25HB sensor1, sensor2; // Create an object of the LPS25HB class

// ros
ros::NodeHandle  nh;
std_msgs::String hoge;
ros::Publisher pub("chatter", &hoge);

void setup()
{

  nh.getHardware()->setBaud(57600);
  nh.initNode();
  nh.advertise(pub);

  while(!nh.connected())
  {
    nh.spinOnce();
  }

  Serial.begin(9600);
  Serial.println("LPS25HB Pressure Sensor Example 3 - Checking the Connection");
  Serial.println();

  Wire.begin();
  Wire1.begin();
  sensor1.begin(Wire, LPS25HB_I2C_ADDR_DEF); 
  sensor2.begin(Wire1, LPS25HB_I2C_ADDR_DEF); 
}

void common_procedure(LPS25HB& sensor){
  if (sensor.isConnected() == true)
  {
    if (sensor.getStatus() == 0x00)
    {
      sensor.begin();
    } // If it is connected but not responding (for example after a hot-swap) then it may need to be re-initialized
    Serial.print("Connected. Sensor Status: ");
    Serial.print(sensor.getStatus(), HEX); // Read the sensor status, the datasheet can explain what the various codes mean
    Serial.print(", Pressure (hPa): ");
    Serial.print(sensor.getPressure_hPa()); // Get the pressure reading in hPa as determined by dividing the number of ADC counts by 4096 (according to the datasheet)
    Serial.print(", Temperature (degC): ");
    Serial.println(sensor.getTemperature_degC()); // Get the temperature in degrees C by dividing the ADC count by 480
  }
  else
  {
    Serial.println("Disconnected");
    sensor.begin();
  }
}

void loop()
{
    Serial.println("testing sensor1\n");
    common_procedure(sensor1);

    Serial.println("testing sensor2\n");
    common_procedure(sensor1);
    hoge.data = "unko";
    pub.publish(&hoge);
    delay(100);
    nh.spinOnce();
}

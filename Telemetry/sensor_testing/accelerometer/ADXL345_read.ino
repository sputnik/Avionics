
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(1111);

void setup()
{
  accelerometerSetup(16, 3200);//setup sensor, range and frequency
  calibrateAccel(1);//1 runs calibration, 0 skips, do not have to run
}  
void loop() 
{
  sensors_event_t accelEvent;
  accel.getEvent(&accelEvent);
  accelEvent.acceleration.x
  delay(100);
}
void accelerometerSetup(int range, int rate)
{
#ifndef ESP8266
  while (!Serial);
#endif
  Serial.begin(9600);
  if(!accel.begin())
  {
    Serial.println("Error in connecting with ADXL345 Accelerometer");
    while(1);
  }
  switch(range)
  {
    case 16:
      accel.setRange(ADXL345_RANGE_16_G);
      break;
    case 8:
      accel.setRange(ADXL345_RANGE_8_G);
      break;
    case 4:
      accel.setRange(ADXL345_RANGE_4_G);
      break;
    case 2:
      accel.setRange(ADXL345_RANGE_2_G);
      break;
    default:
      accel.setRange(ADXL345_RANGE_16_G);
      break;
  }
  switch(rate)
  {
    case 3200:
      accel.setDataRate(ADXL345_DATARATE_3200_HZ);
      break;
    case 1600:
      accel.setDataRate(ADXL345_DATARATE_1600_HZ);
      break;
    case 800:
      accel.setDataRate(ADXL345_DATARATE_800_HZ);
      break;
    case 400:
      accel.setDataRate(ADXL345_DATARATE_400_HZ);
      break;
    case 200:
      accel.setDataRate(ADXL345_DATARATE_200_HZ);
      break;
    case 100:
      accel.setDataRate(ADXL345_DATARATE_100_HZ);
      break;
    case 50:
      accel.setDataRate(ADXL345_DATARATE_50_HZ);
      break;
    case 25:
      accel.setDataRate(ADXL345_DATARATE_25_HZ);
      break;
    default:
      accel.setDataRate(ADXL345_DATARATE_3200_HZ);
      break;
  }
}

void calibrateAccel(int calibrate)
{
  if(calibrate)
  {
    float AccelMinX =0;
    float AccelMaxX =0;
    float AccelMinY =0;
    float AccelMaxY =0;
    float AccelMinZ =0;
    float AccelMaxZ =0;
    
    for(int i=0;i<=2;i++)
    {
      Serial.println("Type key when ready..."); 
      while (!Serial.available()){}
      
      sensors_event_t accelTestEvent;
      accel.getEvent(&accelTestEvent);
      
      if (accelTestEvent.acceleration.x < AccelMinX) AccelMinX = accelTestEvent.acceleration.x;
      if (accelTestEvent.acceleration.x > AccelMaxX) AccelMaxX = accelTestEvent.acceleration.x;
    
      if (accelTestEvent.acceleration.y < AccelMinY) AccelMinY = accelTestEvent.acceleration.y;
      if (accelTestEvent.acceleration.y > AccelMaxY) AccelMaxY = accelTestEvent.acceleration.y;
  
      if (accelTestEvent.acceleration.z < AccelMinZ) AccelMinZ = accelTestEvent.acceleration.z;
      if (accelTestEvent.acceleration.z > AccelMaxZ) AccelMaxZ = accelTestEvent.acceleration.z;
  
      Serial.print("Accel Minimums: "); Serial.print(AccelMinX); Serial.print("  ");Serial.print(AccelMinY); Serial.print("  "); Serial.print(AccelMinZ); Serial.println();
      Serial.print("Accel Maximums: "); Serial.print(AccelMaxX); Serial.print("  ");Serial.print(AccelMaxY); Serial.print("  "); Serial.print(AccelMaxZ); Serial.println();
 
      while (Serial.available())
      {
        Serial.read();  // clear the input buffer
      }
    }
  }
}

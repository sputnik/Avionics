
#include "Adafruit_MCP9808.h"
#include <Adafruit_MPL115A2.h>

Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
Adafruit_MPL115A2 mpl115a2;

void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");

  if (!tempsensor.begin()) {
    Serial.println("Couldn't find MCP9808!");
  }
  Serial.println("Getting barometric pressure ...");
  mpl115a2.begin();
}

void loop() {
   //ADXL377
   int ADXL377_X_axis = analogRead(A0);
   int ADXL377_Y_axis = analogRead(A1);
   int ADXL377_Z_axis = analogRead(A2);
   Serial.print("ADXL377: \t");
   Serial.print("X Axis: "); Serial.print(ADXL377_X_axis);
   Serial.print("\t Y Axis: "); Serial.print(ADXL377_Y_axis);
   Serial.print("\t Z Axis: "); Serial.println(ADXL377_Z_axis);

  //MCP9808
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("MCP9808 \t");
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  Serial.print(f); Serial.println("*F");

  //MPL115A2
  float pressureKPA = 0, temperatureC = 0;  
  mpl115a2.getPT(&pressureKPA,&temperatureC);
  Serial.print("MPL115A2: \t");
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.print(" kPa  ");
  Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");




  delay(1000);
}

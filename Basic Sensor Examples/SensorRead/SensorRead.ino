
<<<<<<< HEAD
void setup() {
  

=======
#include "Adafruit_MCP9808.h"
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup() {
  Serial.begin(9600);
  Serial.println("MCP9808 demo");
>>>>>>> ec1bfdf0f9c1c1d1a89ed126c4b4a5cb512ef4d9

  if (!tempsensor.begin()) {
    Serial.println("Couldn't find MCP9808!");
  }
}

void loop() {
<<<<<<< HEAD
    int ADXL377_X_axis = analogRead(A0);
    int ADXL377_Y_axis = analogRead(A1);
    int ADXL377_Z_axis = analogRead(A3);
=======
  // put your main code here, to run repeatedly:

  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  Serial.print(f); Serial.println("*F");

  delay(1000);

>>>>>>> ec1bfdf0f9c1c1d1a89ed126c4b4a5cb512ef4d9
}

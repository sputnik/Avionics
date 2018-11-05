#include <Arduino.h>
#include "Wire.h"
#include "Adafruit_BNO055.h"
#include "utility/imumaths.h"
#include "IMUSensor.h"

IMUSensor bno = IMUSensor(55, 0x28);

void setup() {
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
    bno.updateData();
    bno.getVertAccel();
    bno.getCalibration();
    bno.getEuler();
}

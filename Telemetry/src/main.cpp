#include <Arduino.h>
#include <Wire.h>
#include "IMUSensor.h"
#include "PTSensor.h"
#include "GPSSensor.h"

IMUSensor bno = IMUSensor(55, 0x28);
PTSensor pt = PTSensor();
GPSSensor gps = GPSSensor();

void setup() {
    // put your setup code here, to run once:
}

void loop() {
    // put your main code here, to run repeatedly:
    bno.updateData();
    bno.getVertAccel();
    bno.getCalibration();
    bno.getEuler();
    pt.getTemp();
    pt.getPress();
    gps.getLong();
    gps.getLat();
    gps.connected();
}

#include <Arduino.h>
#include <Wire.h>
#include "IMUSensor.h"
#include "PTSensor.h"
#include "GPSSensor.h"
#include "RTCSensor.h"

IMUSensor bno;
PTSensor pt;
GPSSensor gps;
RTCSensor rtc;

void setup() {
    // put your setup code here, to run once:
    bno = IMUSensor(55, 0x28);
    pt = PTSensor();
    gps = GPSSensor();
    rtc = RTCSensor();
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
    gps.speed();
    gps.alt();
    rtc.seconds();
}

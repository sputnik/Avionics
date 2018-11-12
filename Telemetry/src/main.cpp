#include <Arduino.h>
#include <Wire.h>
#include "IMUSensor.h"
#include "PTSensor.h"
#include "GPSSensor.h"
#include "RTCSensor.h"

IMUSensor bno;
PTSensor  pt;
GPSSensor gps;
RTCSensor rtc;

void setup() {
    // put your setup code here, to run once:
    bno = IMUSensor();
    pt = PTSensor();
    gps = GPSSensor();
    rtc = RTCSensor();
}

// Currently just testing to make sure classes compile
void loop() {
    // put your main code here, to run repeatedly:
    // IMU testing
    bno.updateData();
    bno.getVertAccel();
    bno.getCalibration();
    bno.getEuler();

    // PT Sensor testing
    pt.getTemp();
    pt.getPress();

    // GPS testing
    gps.getLong();
    gps.getLat();
    gps.connected();
    gps.speed();
    gps.alt();

    // RTC Testing
    rtc.seconds();
}

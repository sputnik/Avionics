#include <Arduino.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <TinyGPS++.h>
#define REC_LAT 45.0560
#define REC_LON -92.8088

#define RFM95_CS 9
#define RFM95_RST 10
#define RFM95_INT 11

#define RF95_FREQ 915.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);
TinyGPSPlus gps;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  delay(100);

  Serial.println("Feather LoRa TX Test!");
  // manual reset
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1)
      ;
  }
  Serial.println("LoRa radio init OK!");
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1)
      ;
  }
  Serial.print("Set Freq to: ");
  Serial.println(RF95_FREQ);
  // put your setup code here, to run once:
}

void loop() {
  if (rf95.available()) {
    digitalWrite(LED_BUILTIN, HIGH);
    // Should be a message for us now
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    // Should be a reply message for us now
    if (rf95.recv(buf, &len)) {
      Serial.println((char *)buf);
      char *ch = (char *)buf;
      char *str = (char *)buf;
      ch = strtok(str, " ");
      double lat = atof(ch);
      ch = strtok(NULL, " ");
      double lon = atof(ch);
      Serial.print("Lat = ");
      Serial.print(lat);
      Serial.print(" Lon = ");
      Serial.println(lon);
      unsigned long distanceToGps = (unsigned long)TinyGPSPlus::distanceBetween(
          lat, lon, REC_LAT, REC_LON);
      // TODO : Do the math for alt of GPS? Need to send alt as well
      Serial.print("dist = ");
      Serial.print(distanceToGps);
      Serial.println("(m)");
    } else {
      Serial.println("recv failed");
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}

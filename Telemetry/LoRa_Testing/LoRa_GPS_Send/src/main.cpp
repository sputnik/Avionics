#include <Arduino.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <TinyGPS++.h>

#define RFM95_CS 9
#define RFM95_RST 10
#define RFM95_INT 11

#define RF95_FREQ 915.0
RH_RF95 rf95(RFM95_CS, RFM95_INT);
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
void ftoa(float n, char *res, int afterpoint);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(9600);
  Serial1.begin(GPSBaud);
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
  rf95.setTxPower(23, false);
  // put your setup code here, to run once:
}

int16_t packetnum = 0; // packet counter, we increment per xmission
bool valid = false;
unsigned long startTime = millis();
void loop() {

  while (Serial1.available()) {
    if (gps.encode(Serial1.read())) {
      valid = true;
    }
  }
  if (millis() - startTime > 2000) {
    startTime = millis();
    digitalWrite(LED_BUILTIN, HIGH);
    char radiopacket[30];
    Serial.print("Sending...\n");
    if (gps.location.isValid()) {
      char lat[10];
      char lon[10];
      char alt[10];
      ftoa(gps.location.lat(), lat, 6);
      ftoa(gps.location.lng(), lon, 6);
      ftoa(gps.altitude.meters(), alt, 6);
      sprintf(radiopacket, "%s %s %s", lat, lon, alt);
      Serial.print("Lat=");
      Serial.print(gps.location.lat());
      Serial.print("Lon = ");
      Serial.println(gps.location.lng());
    } else {
      sprintf(radiopacket, "%s%d", "Loc Invalid", packetnum++);
    }
    Serial.println(radiopacket);
    delay(10);
    radiopacket[29] = 0;
    rf95.send((uint8_t *)radiopacket, 30);
    delay(10);
    rf95.waitPacketSent();
    digitalWrite(LED_BUILTIN, LOW);
  }
}
// reverses a string 'str' of length 'len'
void reverse(char *str, int len) {
  int i = 0, j = len - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}
// puts an int into the supplied str, up to length d
int intToStr(int x, char str[], int d) {
  int i = 0;
  bool neg = false;
  if (x < 0) {
    neg = true;
    x *= -1;
  }
  while (x) {
    str[i++] = (x % 10) + '0';
    x = x / 10;
  }

  // If negative, put negative sign at beginning of the string
  if (neg) {
    str[i++] = '-';
  }
  // If number of digits required is more, then
  // add 0s at the beginning
  while (i < d)
    str[i++] = '0';

  reverse(str, i);
  str[i] = '\0';
  return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint) {
  // Extract integer part
  int ipart = (int)n;

  // Extract floating part
  float fpart;
  if (n > 0) {
    fpart = n - (float)ipart;
  } else {
    fpart = fabs(n - (float)ipart);
  }

  // convert integer part to string
  int i = intToStr(ipart, res, 0);

  // check for display option after point
  if (afterpoint != 0) {
    res[i] = '.'; // add dot

    // Get the value of fraction part upto given no.
    // of points after dot. The third parameter is needed
    // to handle cases like 233.007
    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);
  }
}

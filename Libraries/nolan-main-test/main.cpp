//change this to the location of the Arduino.h file on your machine
#include "/usr/share/arduino/hardware/arduino/cores/arduino/Arduino.h"

int main(){
  init();//required when you're using main() instead of setup()/loop()
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  //blink a light on and off, works on the UNO
  while(1){
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}

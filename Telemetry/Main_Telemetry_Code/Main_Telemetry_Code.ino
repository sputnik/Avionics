//include all of the libraries that are needed



//include declarations for the fuctions that are going to be called
//formatted as follows without the "//"
// void get_pressure();
















void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // code calling each function to gather the values needed
  // code to feed those values to functions that calculate altitude and velocity
  // code to send values including, altitude, velocity, acceleration, gps position, time, etc
  float time_now;
  float time_last_transmit = 0;
  time_now = millis();
  // only code for transmiting or saving data will be contained within this if
  //all other code should go before this if statement
    if (time_now > (time_last_transmit + 40)) {
      Serial.println("printing");
      time_last_transmit = time_now;
    }
}

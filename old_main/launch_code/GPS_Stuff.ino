////Refer to "gps_tiny_works" for example stuff
//
//void get_GPS_data() {
//  // This sketch displays information every time a new sentence is correctly encoded.
//  while (ss.available() > 0)
//    if (gps.encode(ss.read())) {
//      //Save the gps data into a string for later usage
//    }
//      
//  if (millis() > 5000 && gps.charsProcessed() < 10)
//  {
//    Serial.println(F("No GPS detected: check wiring."));
//    while(true);
//  }
//}

void write_to_SD() {
  myFile = SD.open("Telemetry.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    
    Serial.print("Writing to rocket.txt...");
    myFile.println(SD_data);
       
    // close the file:
    myFile.close();
    Serial.println("done.");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening rocket.txt");
  }


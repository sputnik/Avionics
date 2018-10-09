void write_to_SD() {
  myFile = SD.open("Telemetry.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    
    Serial.print("Writing to Telemetry.txt...");
    myFile.println(SD_data);
    // SD_data is a character array that is written to when the values that are to be saved on the sd card are printed with sprintf. The size of the character array limits how many characters can be printed
       
    // close the file:
    myFile.close();
    Serial.println("Telemetry.txt successfully closed.");
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening Telemetry.txt");
  }


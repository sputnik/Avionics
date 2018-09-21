void write_to_SD() {
  myFile = SD.open("rocket.txt", FILE_WRITE);

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

  // re-open the file for reading:
//  myFile = SD.open("rocket.txt");
//  if (myFile) {
//    Serial.println("rocket.txt:");
//
//    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
//    // close the file:
//    myFile.close();
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening rocket.txt");
//  }
}

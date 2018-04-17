void write_to_SD(char SD_info[]) {

  //Serial.print("Writing data to SD...");
  //Serial.println(SD_info);
  rocket_data = SD.open("rocket_data.txt", FILE_WRITE);
  rocket_data.println(SD_info);
  rocket_data.close();
  //Serial.println("DONE!");

}

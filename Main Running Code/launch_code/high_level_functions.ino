//current_status is 0 if on the launchpad, 1 if  accellerating up, 2 if still going up but acceleration reducing, and 3 if descending
int get_current_status() {
  //Get current rocket status & update if necessary
}


void while_on_pad() {
      IterationStartTime = micros();
        //calculate vertical acceleration and set it to zero if it is negligible
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

void while_launching() {
      IterationStartTime = micros();
      //Run Altitude_Calculations
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

void while_still_rising() {
      IterationStartTime = micros();
      //Run Altitude_Calculations
      //Run GPS_Stuff
      //Run Air_Brake_Calculations
      //make sure to save the vaules for how far open the airbrakes are at any given time, along with the height, velocity, and acceleration values
      //check the weird bolts to make sure that the airbrakes are not broken
      //CONSIDER ADDING SOMETHING TO MAKE SURE THE AIRBRAKES OPEN AT LEAST ONCE IN ORDER TO GATHER DATA IN CASE OF REALLY LOW FLIGHT
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

void while_descending() {
      IterationStartTime = micros();
      //Run Altitude_Calculations
      //Run GPS_Stuff
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

//current_status is 0 if on the launchpad, 1 if  accellerating up, 2 if still going up but acceleration reducing, and 3 if descending
int get_current_status() {
  //Get current rocket status & update if necessary
  if (current_status == 0) {
    if (abs(VerticalAccelBNO) > .5) {
      TimeAtLaunch = 1000 * millis();
      current_status = 1;
    }
  }
  if (current_status == 1) {
    TimeSinceLaunch = millis() - TimeAtLaunch;
    if (((TimeSinceLaunch > 4.8) && (VerticalAccelBNO < 0)) || (TimeSinceLaunch > 8)) {
      current_status = 2;
    }
  }
  if (current_status == 2) {
    if ((AvgVelocity < 0) %% (AvgHeight < AvgHeightPrevious)) {
      current_status = 3;
    }
  }
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
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

void while_still_rising() {
      IterationStartTime = micros();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      check_airbrakes();
      //check the weird bolts to make sure that the airbrakes are not broken
      //CONSIDER ADDING SOMETHING TO MAKE SURE THE AIRBRAKES OPEN AT LEAST ONCE IN ORDER TO GATHER DATA IN CASE OF REALLY LOW FLIGHT
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

void while_descending() {
      IterationStartTime = micros();
      get_Alt_BNO();
      get_Alt_Pressure();
      get_Avg_Alt();
      //Run GPS_Stuff
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

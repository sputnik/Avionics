//current_status is 0 if on the launchpad, 1 if  accellerating up, 2 if still going up but acceleration reducing, and 3 if descending
int get_current_status(void) {
  int return_val = 0;
  //Get current rocket status & update if necessary
  if (current_status == 0) {
    if (abs(VerticalAccelBNO) > .5) {
      TimeAtLaunch = millis();
      return_val = 1;
    }
  }
  if (current_status == 1) {
    TimeSinceLaunch = millis() - TimeAtLaunch;
    if ((((TimeSinceLaunch > 4.8) && (VerticalAccelBNO < 0))) || (TimeSinceLaunch > 8)) {
      return_val = 2;
    }
  }
  if (current_status == 2) {
	  //TODO: "Also, will velocity be negative? In a physics problem, yes. In our specific application, I can't guarantee that. After apogee, we still have a very large positive velocity, just not vertical. Just double check to be sure everything will be fine"
    if ((AvgVelocity < 0) || (AvgHeight < AvgHeightPrevious)) {
      return_val = 3;
    }
  }
  return return_val;
}


void while_on_pad() {
      IterationStartTime = micros();
	  //TODO: "This function looks like it isn't filled out...?"
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
	  //TODO: "I never see 'get_Alt_ADXL'...?"
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
	  //TODO: "maybe calculate what our highest altitude was and log that"
      //Run GPS_Stuff
      IterationEndTime = micros();
      ComputationTime = (IterationEndTime - IterationStartTime) / 1000000;
      WaitTime = TIME_DELTA - ComputationTime;
      delay(WaitTime * 1000);
}

//current_status is 0 if on the launchpad, 1 if  accellerating up, 2 if still going up but acceleration reducing, and 3 if descending
int get_current_status() {
  //Get current rocket status & update if necessary
}


void while_on_pad() {
        //calculate vertical acceleration and set it to zero if it is negligible
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
}

void while_launching() {
        /*calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      calculate height from the barometer
      calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      send gps coordinates and radio pings so the rocket can be located in case of total software failure
      */
}

void while_still_rising() {
        //calculate vertical acceleration, and calculate height and velocity from vertical acceleration
      //calculate height from the barometer
      //calculate averaged height and averaged velocity from the barometer and accererometer values, and use these values for the next iteration of calculations
      //send gps coordinates and radio pings so the rocket can be located in case of total software failure
      //compare current height and velocity to pre generated height/velocity curve to determine if the rocket should be braking
      //make sure to save the vaules for how far open the airbrakes are at any given time, along with the height, velocity, and acceleration values
      //check the weird bolts to make sure that the airbrakes are not broken
      //CONSIDER ADDING SOMETHING TO MAKE SURE THE AIRBRAKES OPEN AT LEAST ONCE IN ORDER TO GATHER DATA IN CASE OF REALLY LOW FLIGHT
   
}

void while_descending() {
  
}

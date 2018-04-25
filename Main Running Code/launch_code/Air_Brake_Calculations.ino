// inputs , AvgHeight, AvgVelocity,

void check_airbrakes() {  
    //#error "Need AvgHeight and AvgVelocity passed in. It shouldnt need them as inputs because they are global variables"
  double x = AvgHeight;
  VelocityPlot = (-.00000000000001899*x*x*x*x*x) + (.00000000015956*x*x*x*x) - (.00000051519*x*x*x) + (.00079063*x*x) - (.65635 * x) + (480.28);
  if (AvgVelocity >= VelocityPlot) {
    AirbrakeStatus = true;
    //printf("airbrakes opening\n");
  }
  else if (AvgVelocity < VelocityPlot) {
    AirbrakeStatus = false;
  }
  if (AirbrakeStatus == true) {
    if (CurrentActuationPeriod >= ActuationTime) {
      //Open Airbrakes;
      //they are all of the way open
      PercentOpen = 100;
    }
    else if (CurrentActuationPeriod < ActuationTime) {
      //Open Airbrakes;
      PercentOpen = CurrentActuationPeriod * 45.4545454545;
      CurrentActuationPeriod = CurrentActuationPeriod + TIME_DELTA;
    }
  }
  else if (AirbrakeStatus == false) {
    if (CurrentActuationPeriod <= 0) {
      //Close Airbrakes;
      //they are all of the way closed
      PercentOpen = 0;
    }
    else if (CurrentActuationPeriod >0) {
      //Close Airbrakes
      PercentOpen = CurrentActuationPeriod * 45.4545454545;
      CurrentActuationPeriod = CurrentActuationPeriod - TIME_DELTA;
    }
  }
}

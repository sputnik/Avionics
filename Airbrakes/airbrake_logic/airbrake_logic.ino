void airbrake_logic(double density, double velocity, double height, double cd_drag, double rocket_area, double mass, double goal_height) {
  double k = .5 * density * cd_drag * rocket_area;
  double qsquared = -1 * mass * 9.81 / k;
  double brake_status = 0;
  double coast_height = ((mass / (2*k)) * long((qsquared - (velocity*velocity))/qsquared)) + height;
  if (coast_height > goal_height) {
    //brake!
    brake_status = 1;
  }
  else {
    //dont brake!
    brake_status = 0;
  }
  return brake_status;
}


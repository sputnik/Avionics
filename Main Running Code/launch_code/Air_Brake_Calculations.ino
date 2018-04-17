  double y;
  double x;
  double t = 0;
  double a = 0;
  double percentopen;


    drag = drag_from_density_and_velocity(density, velocity); //newtons
void check_airbrakes() {  
  x = height;
  y = (-.00000000000001899*x*x*x*x*x) + (.00000000015956*x*x*x*x) - (.00000051519*x*x*x) + (.00079063*x*x) - (.65635 * x) + (480.28);
  if (velocity >= y) {
    a = 1;
    //printf("airbrakes opening\n");
  }
  else if (velocity < y) {
    a = 0;
    //printf("airbrakes closing");
  }
  if (a == 1) {
    if (t >= ACTUATION_TIME) {
      Open Airbrakes;
      //they are all of the way open
      percentopen = 100;
    }
    else if (t < ACTUATION_TIME) {
      Open Airbrakes;
      percentopen = t * 45.4545454545;
      t = t + TIME_DELTA;
    }
  }
  else if (a == 0) {
    if (t <= 0) {
      Close Airbrakes;
      //they are all of the way closed
      percentopen = 0;
    }
    else if (t >0) {
      Close Airbrakes
      percentopen = t * 33.33333;
      t = t - TIME_DELTA;
    }
  }
}

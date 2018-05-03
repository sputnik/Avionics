//Comment description here
void get_Alt_BNO() 
{
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

  VerticalAccelBNO = ((linear.x() * gravity.x()) + (linear.y() * gravity.y()) + (linear.z() * gravity.z())) / 9.81;
  Serial.print("VerticalAccel:, ");
  Serial.println(VerticalAccelBNO);
  if (VerticalAccelBNO >= .5) {
    LaunchValue = true ;
  }
  if (VerticalAccelBNO <= -.5) {
    LaunchValue = true ;
  }
  if (LaunchValue == false) {
    VerticalAccelBNO = 0;
    
  }
  HeightBNO = AvgHeight + (AvgVelocity * TIME_DELTA) + (.5 * VerticalAccelBNO * TIME_DELTA * TIME_DELTA);
  VelocityBNO = AvgVelocity + (VerticalAccelBNO * TIME_DELTA);

  if (LaunchValue == false) {
    HeightBNO = 0;
    VelocityBNO = 0;
  }
  
  int ADXL377_X_axis = analogRead(A2);
  int ADXL377_Y_axis = analogRead(A1);
  int ADXL377_Z_axis = analogRead(A0);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(ADXL377_X_axis, 512, 517, -1000, 1000); // Acceleration in the x direction in milli G's
  long yScaled = map(ADXL377_Y_axis, 512, 517, -1000, 1000); // Acceleration in the y direction in milli G's
  long zScaled = map(ADXL377_Z_axis, 511, 517, -1000, 1000); // Acceleration in the z direction in milli G's
//#error "Can we comment the label that everything is? IE when you initialize xScaled, comment the label for that, when you make xAccel, comment label for that"
//I Believe that the xScaled, yScaled etc are the cartesian values of acceleration in milli Gs because when they are divided by 1000 they are in terms of G's
  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;
  float ADXLRatioPart1 = (acc.x() * acc.x()) + (acc.y() * acc.y()) + (acc.z() * acc.z());
  float ADXLRatioPart2 = (xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel);
  if (LaunchValue == true) {
    VerticalAccelADXL = VerticalAccelBNO * 9.81 * sqrt(ADXLRatioPart2) / sqrt(ADXLRatioPart1);
    HeightADXL = AvgHeight + (AvgVelocity * TIME_DELTA) + (.5 * VerticalAccelADXL * TIME_DELTA * TIME_DELTA);
    //#error "Following value never used"
    //#error "assuming you did use it, you're calculating using an average velocity and a raw acceleration. I see why, but do we want that?"
    // yeah we do want it calculated this way, but it hasnt been used yet because Ive thought of two ways to calculate AvgVelocity and I think it will still work if we calculate AvgVelocity from the change in AvgHeight
    VelocityADXL = AvgVelocity + (VerticalAccelADXL * TIME_DELTA);
  }
  if (LaunchValue == false) {
    VerticalAccelADXL = 0;
    HeightADXL = 0;
    VelocityADXL = 0;
  }
}


/*
 * Function Summary:
 *    This function gets the altitude from the barometric pressure sensor through a x-point averager
 *    as defined by the PRESSURE_AVERAGING_ITERATIONS defined value.
 * 
 * Parameters:
 *    Input: Void
 *    Output: (float) altitude_from_pressure, 
 * 
 */
void get_Alt_Pressure()
{

  
  for (pressure_avg_counter = 0; pressure_avg_counter < PRESSURE_AVERAGING_ITERATIONS; pressure_avg_counter++) {
    
     mpl115a2.getPT(&pressureKPA, &temperatureC);
     pressure += pressureKPA;
     tempC += temperatureC;
  }

  pressure = pressure / PRESSURE_AVERAGING_ITERATIONS;
  tempC = tempC / PRESSURE_AVERAGING_ITERATIONS;

  pressure = pressure / 10.0; //Convert to hPa

  //Calculating Altitude from Pressure and Temperature Equation
  altitude_from_pressure = ((pow(SEA_LEVEL_PRESSURE / pressure, 1 / 5.257) - 1) * (tempC + 273.15)) / (0.0065); 
  HeightPress = altitude_from_pressure - START_ALT;
  if (current_status == 0) {
    START_ALT = altitude_from_pressure;
  }
}
void get_Avg_Alt()
/*
 * this function averages the height and velocity values, 
 * calculates AvgHeight and AvgVelocity, 
 * 
 * INPUTS(global):
 * OUTPUTS(global): AvgHeight and AvgVelocity
 */
{
  AvgHeight = (HeightBNO + HeightPress + HeightADXL) / 3;
  AvgHeightWithoutPressure = (HeightBNO + HeightADXL) / 2;
  //AvgVelocity = (AvgHeightWithoutPressure - AvgHeightPrevious) / TIME_DELTA;
  AvgVelocity = (VelocityBNO + VelocityADXL) / 2;
  //#error "Do we want to calculate velocity this way or by using the velocity from Accelerometers?"
  // Because the AvgHeight is calculated from both accelerometers, and the barometer, this method of calculation should work well
  AvgHeightPrevious = AvgHeightWithoutPressure;
}


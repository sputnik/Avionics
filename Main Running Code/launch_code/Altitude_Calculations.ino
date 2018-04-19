//Comment description here
void get_Alt_BNO() 
{
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  imu::Vector<3> acc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  imu::Vector<3> linear = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);

  VerticalAccelBNO = ((linear.x() * gravity.x()) + (linear.y() * gravity.y()) + (linear.z() * gravity.z())) / 9.81;
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
float get_Alt_Pressure()
{

  float pressureKPA = 0;
  float temperatureC = 0;
  float jpressureKPA = 0;
  float temperatureC = 0;
  float altitude_from_pressure = 0.0;

  for (pressure_avg_counter = 0; pressure_avg_counter < PRESSURE_AVERAGING_ITERATIONS; pressure_avg_counter++) {
     mpl115a2.getPT(&pressureKPA, &temperatureC);
     pressureKPA += pressureKPA;
     temperatureC += temperatureC;
  }

  pressureKPA = pressureKPA / PRESSURE_AVERAGING_ITERATIONS;
  temperatureC = temperatureC / PRESSURE_AVERAGING_ITERATIONS;

  pressure = pressure / 10.0; //Convert to hPa

  altitude_from_pressure = ((pow(Po / pressure, 1 / 5.257) - 1) * (temp + 273.15)) / (0.0065);
  HeightPress = altitude_from_pressure - START_ALT;

  return altitude_from_pressure;
}

void get_Accel_ADXL() 
/*
 * this function gets the data from the ADXL, 
 * calculates height and velocity, 
 * and puts the results in adxl_altitude and adxl_velocity
 * 
 * INPUTS(global): Analog pins for x, y, and z
 * OUTPUTS(global): bno_altitude, bno_velocity
 */
{
  int ADXL377_X_axis = analogRead(A0);
  int ADXL377_Y_axis = analogRead(A1);
  int ADXL377_Z_axis = analogRead(A2);

  // Convert raw values to 'milli-Gs"
  long xScaled = map(ADXL377_X_axis, 512, 517, -1000, 1000);
  long yScaled = map(ADXL377_Y_axis, 512, 517, -1000, 1000);
  long zScaled = map(ADXL377_Z_axis, 511, 517, -1000, 1000);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;
  float ADXLRatioPart1 = (acc.x() * acc.x()) + (acc.y() * acc.y()) + (acc.z() * acc.z());
  float ADXLRatioPart2 = (xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel);
  if (LaunchValue == true) {
    VerticalAccelADXL = VerticalAccelBN) * 9.81 * sqrt((xAccel * xAccel) + (yAccel * yAccel) + (zAccel * zAccel)) / sqrt((acc.x() * acc.x()) + (acc.y() * acc.y()) + (acc.z() * acc.z()));
    HeightADXL = AvgHeight + (AvgVelocity * TIME_DELTA) + (.5 * VerticalAccelADXL * TIME_DELTA * TIME_DELTA);
    VelocityADXL = AvgVelocity + (VerticalAccelADXL * TIME_DELTA);
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
  AvgVelocity = (AvgHeight - AvgHeightPrevious) / TIME_DELTA;
  AvgHeightPrevious = AvgHeight;
}


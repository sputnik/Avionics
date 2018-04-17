//Comment description here


void get_Alt_BNO() 
/*
 * this function gets the data from the BNO055, 
 * calculates height and velocity, 
 * and puts the results in bno_altitude and bno_velocity
 * 
 * INPUTS(global): none, have to create vectors using imu::vector
 * OUTPUTS(global): bno_altitude, bno_velocity
 */
{

}

void get_Alt_Pressure()
/*
 * this function (gets), 
 * calculates (math), 
 * and puts the results in (variables)
 * 
 * INPUTS(global/internal(passed in)): 
 * OUTPUTS(global/internal(returned)): 
 */
{

  for (pressure_avg_counter = 0; pressure_avg_counter < PRESSURE_AVERAGING_ITERATIONS; pressure_avg_counter++) {
     mpl115a2.getPT(&pressureKPA, &temperatureC);
     pressureKPA += pressureKPA;
     temperatureC += temperatureC;
  }

  pressureKPA = pressureKPA / PRESSURE_AVERAGING_ITERATIONS;
  temperatureC = temperatureC / PRESSURE_AVERAGING_ITERATIONS;

  pressure = pressure / 10.0; //Convert to hPa

  altitude_from_pressure = ((pow(Po / pressure, 1 / 5.257) - 1) * (temp + 273.15)) / (0.0065);

  return alt;
}

void get_Alt_ADXL(float accel_vals[]) 
/*
 * this function gets the data from the ADXL, 
 * calculates height and velocity, 
 * and puts the results in adxl_altitude and adxl_velocity
 * 
 * INPUTS(global): Analog pins for x, y, and z
 * OUTPUTS(global): bno_altitude, bno_velocity
 */
{
//  int ADXL377_X_axis = analogRead(A0);
//  int ADXL377_Y_axis = analogRead(A1);
//  int ADXL377_Z_axis = analogRead(A2);
//
//  // Convert raw values to 'milli-Gs"
//  long xScaled = map(ADXL377_X_axis, 512, 517, -1000, 1000);
//  long yScaled = map(ADXL377_Y_axis, 512, 517, -1000, 1000);
//  long zScaled = map(ADXL377_Z_axis, 511, 517, -1000, 1000);
//
//  // re-scale to fractional Gs
//  float xAccel = xScaled / 1000.0;
//  float yAccel = yScaled / 1000.0;
//  float zAccel = zScaled / 1000.0;
//
//  // convert linear value and euler angles to purely vertical accel
//  // float vertical_accel = xAccel * sin( invcos( (sqrt( (xAccel * cos( euler.x ))^2 + (xAccel * cos( euler.y ))^2)/ xAccel)));
//  // height = height + (velocity * time_delta) + (.5 * vertical_accel * 9.81 * time_delta * time_delta);
//  // velocity = velocity + (vertical _accel * 9.81 * time_delta);
//
//  accel_vals[0] = xAccel;
//  accel_vals[1] = yAccel;
//  accel_vals[2] = zAccel;

}

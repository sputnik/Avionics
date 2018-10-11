#include <Arduino.h>

enum State {coasting, ascending, launchPad, descending} state = launchPad;

struct Data {
  double accX = 0.0;
  double accY = 0.0;
  double accZ = 0.0;
  double velX = 0.0;
  double velY = 0.0;
  double velZ = 0.0;
  double alt  = 0.0;
  double pressure = 0.0;
  double airbreaks = 0.0;
} data;  //initialize stucture - data

// Predefining functions used
bool switchToAscending(Data data);
bool switchToCoasting(Data data);
bool checkSetUp();
void updateData();
bool checkAirbreaks(Data data);
void saveData(Data data);

void setup()
{
  if (checkSetUp())
  {

  /**
   * TODO: Insert sensor interfaces here ?
   */

 }
} //void setup


void loop()
{
 updateData();
 if (state == coasting){
    if (checkAirbreaks(data))
    { //calculate and deploy airbreaks
      state = descending; //change the state to descending
    }
    saveData(data); //save data to SD card
 }
 else if (state == ascending)
 {
    if(switchToCoasting(data))
    { //check if the rocket is coasting
      state = coasting; //change the state to coasting
    }
    saveData(data); //save data to SD card
 }
 else if (state == launchPad)
 {
    if(switchToAscending(data))
    { //check id the rocket is Ascending
      state = ascending;  // change the state to ascending
    }
    saveData(data); //save data to SD card
 }
 else
 {
  //TODO: add desending stae
 }
} //void loop

/**
 * Check the data of the rocket and determine if the rocket is ascending
 * @return bool true if the rocket is ascending
 *              false if the rocket is in any other states
 *
 * @param  State  data from the rocket's sensors
 */
bool switchToAscending(Data data)
{
  //TODO
  return false;
}

/**
 * Check the data of the rocket and determine if the rocket is coasting
 *
 * @return bool true if the rocket is ascending
 *              false if the tocket is in any other states
 *
 * @param State data from the rocket's sensors
 */
bool switchToCoasting(Data data)
{
  //TODO
  return false;
}

/**
 * Calculate and deploy airbreaks
 *
 * Check if the rocket is desending
 *
 * @return bool true if the rocket is ascending
 *              false if the rocket is in any other states
 *
 * @param State data from the rocket's sensors
 *
 */
bool checkAirbreaks(Data data)
{
  //TODO
  return false;
}


/**
 * Setup sensors used in airbrakes bay
 *
 * @return bool true if setup completed successfully
 *              false if setup failed in some way
 *
 */
bool checkSetUp()
{
	//TODO
  return false;
}

/**
 * Update global data object with new sensor information
 *
 */
void updateData()
{
  //TODO
}

/**
 * Update SD card with new sensor information
 *
 * @param data : The data to save to the SD card
 *
 */
void saveData(Data data)
{
  //TODO
}
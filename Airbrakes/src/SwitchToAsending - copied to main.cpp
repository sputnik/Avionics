#define ARDUINO_MAIN
//#include "Arduino.h"
#include <stdio.h>
#include <math.h>
#include "Data.h"

//temporary file for switchToAscending for testing and debugging purposes.

typedef enum State { launchPad, ascending, coasting, descending } state;
/*
struct Data {
  double accX ;
  double accY ;
  double accZ ;
  double velX ;
  double velY ;
  double velZ ;
  double alt ;
  double pressure ;
  double airbreaks ;
  unsigned long time;
}; // main data structure
*/
void updateData(Data *data){
  scanf("%f ", data -> accX);
  scanf("%f ", data -> accY);
  scanf("%f ", data -> accZ);
  scanf("%f ", data -> velX);
  scanf("%f ", data -> velY);
  scanf("%f ", data -> velZ);
  /*scanf("%f ", data -> alt);
  scanf("%f ", data -> pressure);
  scanf("%f ", data -> airbreaks);
  data -> time ++;*/
}

bool switchToAscending(Data *data, int *counter);
void updateData(Data *data);

int main(){
  Data data;
  int safetycounter =0;
  while (1){
    //updateData(&data);
    switchToAscending(&data, &safetycounter);
  }

}

bool switchToAscending(DataHistory *hist, int *counter){
      const double ASC_ACC_TOL = 0.0;
      const double ASC_VEL_TOL = 0.0;
	  const double ASC_ALT_TOL = 0.0;
      const int ASC_SAFE_TOL = 100; //define constants for switch to ascending
	  int token = 0; //counter to track how many of the checks are passed  if token > 2, then the rocket is accelerating
	  int arraySize = hist->getSize();

      //printf("switchToAscending\n");
      double accMag = sqrt(hist->getNewest()->accX * hist->getNewest()->accX + hist->getNewest()->accY * hist->getNewest()->accY + hist->getNewest()->accZ * hist->getNewest()->accZ); //calculate acceleration vector mag
	  
      double velMag = sqrt(hist->getNewest()->accX * hist->getNewest()->accX + hist->getNewest()->accY * hist->getNewest()->accY + hist->getNewest()->accZ * hist->getNewest()->accZ); //calculate velosity vector mag
	  
	  if ( fabs(accMag - ASC_ACC_TOL) > 0) token++;
	  if ( fabs(velMag - ASC_VEL_TOL) > 0)	  token++;
	  if ( hist->get(arraySize-1)->alt - hist->get(arraySize - 2)->alt > ASC_ALT_TOL)						  
		  token++;      //compare values to tolerance and update token count 

	  (token >= 2)? *counter + 1: 0;  //update the security counter

      if (*counter >= ASC_SAFE_TOL) return true; //return true if counter is higher than safety tolerance

      return false;
}

/*
 * mock updateData method used to update Dada for debugging purposes
 */

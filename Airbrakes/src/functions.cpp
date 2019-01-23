
#include <iostream>
#include <vector>
#include "math.h"
using namespace std;
vector<vector<double>> dataVector;

int main() {
  double getVelocityAltT(int samp);
  double getVfromAccelTime(double acceli, double accelf, double ti, double tf, double prevV, int samp);
  double getAfromTimeVel(double veli, double velf, double ti, double tf, int samp);;
  int testProjectile();
  //Vector contains time, altitude, velocity and acceleration
  testProjectile();
  return 1;
}

/*
 * @return - velocity m/s
 *
 * @param samp (int) - number of previous measurements to sample from
 * Gets Velocity from Altitude and Time, assuming data is in an array that adds elements to the end
 */
double getVelocityAltT(unsigned int samp) {
  double velocity = 0.0;
  if ( samp > dataVector.size()) {
    samp = dataVector.size();
  }
  int divisor = 0;
  for (unsigned int i = 0; i < samp; i++) {
    if (dataVector.size() >= samp + i + 1) {
      velocity = velocity + (dataVector.at(dataVector.size()-i-1).at(1) - dataVector.at(dataVector.size()-i-2).at(1)) / (dataVector.at(dataVector.size()-i-1).at(0) - dataVector.at(dataVector.size()-i-2).at(0));
      divisor++;
    } else if (dataVector.size() == 1) {
      velocity = dataVector.at(0).at(1) / dataVector.at(0).at(0);
      divisor = 1;
    }
  }
  if (!(divisor == 0)) {
    velocity = velocity/divisor;
  }
  return velocity;
}

/*
 * @return - velocity m/s
 *
 * @param samp (int) - number of previous measurements to sample from
 * Gets Velocity from Acceleration and Time, assuming data is in an array that adds elements to the end
 */
double getVelocityAccT(unsigned int samp) {
  double velocity = 0.0;
  double deltaT = 0.0;
  if (samp > dataVector.size()) {
    samp = dataVector.size();
  }
  int divisor = 0;
  for (unsigned int i = 0; i < samp; i++) {
    if (!(dataVector.size() == 1) && (dataVector.size() >= samp + i + 2)) {
      deltaT = dataVector.at(dataVector.size()-1-i).at(0) - dataVector.at(dataVector.size()-2-i).at(0);
      double acceli = dataVector.at(dataVector.size()-2-i).at(3);
      double accelf = dataVector.at(dataVector.size()-1-i).at(3);
      velocity = velocity + (0.5*(acceli+(0.5*(acceli+accelf)))*deltaT)+(0.5*(accelf+(0.5*(acceli+accelf)))*deltaT) + dataVector.at(dataVector.size()-3-i).at(2) ;
      divisor++;
    }
  }
  if (!(divisor == 0)) {
    velocity = velocity/divisor;
  }
  return velocity;
}

/*
 * @return - Acceleration in m/s/s
 *
 * @param samp (int) - number of previous measurements to sample from
 * Gets Acceleration from Velocity and Time, assuming data is in a vector that adds elements to the end
 */
 double getAccelerationVT(unsigned int samp) {
   double acceleration = 0.0;
   if (samp > dataVector.size()) {
     samp = dataVector.size();
   }
   int divisor = 0;
   double deltaT = 0.0;
   for (unsigned int i = 0; i < samp; i++) {
     if (!(dataVector.size() == 1) && (dataVector.size() >= samp + i + 2)) {
       deltaT = dataVector.at(dataVector.size()-1-i).at(0) - dataVector.at(dataVector.size()-2-i).at(0);
       double veli = dataVector.at(dataVector.size()-2-i).at(2);
       double velf = dataVector.at(dataVector.size()-1-i).at(2);
       acceleration = acceleration + (velf-veli)/(deltaT);
       divisor++;
     }
   }
   if (!(divisor == 0)) {
     acceleration = acceleration/divisor;
   }
   return acceleration;
 }

//test with projectile function
int testProjectile() {
  cout << "Test projectile motion" << '\n';
  for (int i = 0; i < 635; i++) {
    double t = i*0.01;
    double altitude = 4 + 30.48*t - 9.81*pow(t, 2.0)/2;
    double velocity = 30.48 - 9.81*t;
    double acceleration = -9.81;
    vector<double> holdVec;
    holdVec.push_back(t);
    holdVec.push_back(altitude);
    holdVec.push_back(velocity);
    holdVec.push_back(acceleration);
    dataVector.push_back(holdVec);
    cout << t << ": " << altitude << "m, ";
    cout << velocity << "m/s, ";
    cout << acceleration << "m/s/s\n";
    cout << getVelocityAltT(1) << " m/s\n";
    cout << getVelocityAltT(2) << " m/s\n";
    cout << getVelocityAltT(3) << " m/s\n";
    cout << getVelocityAltT(4) << " m/s\n";
    cout << getVelocityAccT(1) << " m/s\n";
    cout << getVelocityAccT(2) << " m/s\n";
    cout << getVelocityAccT(3) << " m/s\n";
    cout << getVelocityAccT(4) << " m/s\n";
    cout << getAccelerationVT(1) << " m/s/s\n";
    cout << getAccelerationVT(2) << " m/s/s\n";
    cout << getAccelerationVT(3) << " m/s/s\n";
    cout << getAccelerationVT(4) << " m/s/s\n";
  }
  return 1;
}

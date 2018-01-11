#include <stdio.h>
#include <math.h>

//first: ignition
	// until rocket achieves liftoff(?)
		//gathered information:?
		//calculated information:?
		
//second: thrusting period
	// until rocket engine is no longer thrusting(by time or by accelerometer)
		//gathered information: acceleration(accelerometer), time(?), pressure(barometer)
		//calculated information: velocity(acceleration), altitude(velocity), altitude(pressure)

// third: deceleration period
	// until a time at which the rocket could brake to a dicks length of goal, even if the rocket is operating at the highest simulated flight(altitude) (get from mechanical group)
		//gathered information: acceleration(accelerometer), pressure(barometer), time(?)
		//calculated information: velocity(acceleration), altitude(velocity), altitude(pressure)

// fourth: braking period
	// until a time at which the rocket is at apogee(accelerometer)
		//gathered information: altitude(accelerometer), pressure(barometer), time(?)
		//calculated information: velocity(acceleration), altitude(velocity), altitude(pressure), altitude(avg), velocity(AvgAltitude), density(AvgAltitude), DistanceToGoal(AvgAltitude), StoppingDistanceWithoutBrakes(AvgVelocity)

// fifth: drogue deployment
	// until rocket reaches main shute deployment altitude(?chute altimeter?)
		//gathered information: altitude(barometer?), location(GPS), time(?)
		//calculated information: ?

// sixth: main deployment
	// until touchdown(accelerometer)
		//gathered information: altitude(barometer?), location(GPS), time(?)
		//calculated information: ?

//Necesary sensors
	//barometer
	//accelerometer
	//time thingy
	//GPS

//Necesary calculations
	//velocity from acceleration 
		//
	//altitude from velocity
	//altitude from pressure
	//altitude from averaging the other two altitudes
	//velocity from the averaged altitude
	//density from the averaged altitude
	// ditance to the goal from the averaged altitudes
	// stopping distance without breaks, from averaged altitude and velocity
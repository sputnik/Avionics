#include <stdio.h>
#include <math.h>

//first: ignition
	// until rocket achieves liftoff(?)
		//gathered information:BNO055
		//calculated information:Calculate and look for initial launch
		
//second: thrusting period
	// until rocket engine is no longer thrusting(by time or by accelerometer)
		//gathered information: acceleration(accelerometer), time(RTC), pressure(barometer)
		//calculated information: velocity(acceleration), altitude(velocity), altitude(pressure), Average altitude(velocity) and altitude(barometer)

// third: deceleration period
	// until a time at which the rocket could brake to a dicks length of goal, even if the rocket is operating at the highest simulated flight(altitude) (get from mechanical group)
		//gathered information: acceleration(accelerometer), pressure(barometer), time(RTC)
		//calculated information: velocity(acceleration), altitude(velocity), altitude(pressure), Average altitude(velocity) and altitude(barometer), 
		//SHOULD BE USING LINE FROM MATLAB TO FIND WHEN TO BRAKE

// fourth: braking period
	// until a time at which the rocket is at apogee(accelerometer)
		//gathered information: altitude(accelerometer), pressure(barometer), time(RTC)
		//calculated information: velocity(acceleration), altitude(velocity), altitude(pressure), altitude(avg), velocity(AvgAltitude), density(AvgAltitude), DistanceToGoal(AvgAltitude), StoppingDistanceWithoutBrakes(AvgVelocity)
		//MAKE SURE WE STILL NEED TO BRAKE

// fifth: drogue deployment
	// until rocket reaches main shute deployment altitude(?chute altimeter?)
		//gathered information: altitude(barometer?), location(GPS), time(RTC)
		//calculated information: sending GPS via RTC

// sixth: main deployment
	// until touchdown(accelerometer)
		//gathered information: altitude(barometer?), location(GPS), time(RTC)
		//calculated information: sending GPS via RTC

//Necesary sensors
	//barometer(MCP9808)
	//accelerometer(BNO055)
	//RTC(DS3231)
	//GPS(Ultimate GPS)

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
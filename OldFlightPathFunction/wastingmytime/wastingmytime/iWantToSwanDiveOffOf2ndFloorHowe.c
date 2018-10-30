#include <stdio.h>
#include <math.h>

#define G 9.81 //meters per second squared
#define SEA_DENSITY 1.225 //kg per cubic meter
#define TIME_DELTA 0.01 //seconds
#define CD_BRAKE 1.28
#define CD_DRAG 0.42
#define AREA_ROCKET .00872677 //meters squared
#define AREA_BRAKE .002419 //meters squared
//#define AREA_BRAKE .001978 //meters squared
#define START_ALT 1219.2 //meters
#define GOAL_HEIGHT 9144 //meters
#define WEIGHT_I 355.858 //newtons
#define WEIGHT_F 253.549 //newtons
//#define START_THRUST 1561.4 //newtons
#define START_THRUST 1800 //newtons
#define FUEL_BURN_RATE 9.4730555556 //newtons per second
#define ACTUATION_TIME .1 // secs
// N2850

double density_from_altitude(double altitude) //density equation
{
	return SEA_DENSITY * pow(1 + (-.0065 * altitude / 287), 4.25363734);
}
double drag_from_density_and_velocity(double dense, double vel) //drag equation for rocket
{
	return .5 * dense * vel * vel * CD_DRAG * AREA_ROCKET;
}
double brake_from_density_and_velocity(double dense, double vel) //drag equation for airbrakes
{
	return .5 * dense * vel * vel * CD_BRAKE * AREA_BRAKE;
}

int main(void)
{
	FILE* logfile;	//create log file
	logfile = fopen("logfile.txt", "w");	//set that file to writeable named logfile.txt

	double time; //seconds
	double alt = START_ALT; //meters
	double height = 0; //meters
	double velocity = 0; //meters per second
	double mass; //kg
	double density; //kg per cubic meter
	double drag; //newtons
	double weight; //newtons
	double force; //newtons
	double thrust; //newtons
	double brake; //newtons
	double tend; //seconds
	double fneed; //newtons
	double y;
	double x;
	double z;
	double t = 0;
	double a = 0;
	double b = 0;
	double percentopen;
	double k;
	double qsquared;
	double hc;


	thrust = START_THRUST; //newtons
	weight = WEIGHT_I; //newtons
	for (time = 0; time < 10.8; time += TIME_DELTA) {
		if (time <= 10.8) {
			thrust = START_THRUST;
		}
		//else if (time > 4.0) {
		//	thrust -= (3750) * TIME_DELTA;
		//} //thrust equation

		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		weight -= FUEL_BURN_RATE * TIME_DELTA; //newtons
		force = thrust - drag - weight; //newtons
		mass = weight / G; //kg
		velocity += force / mass * TIME_DELTA; //meters per second
		fprintf(logfile, "height = %f\nvelocity = %f\nthrust = %f\ndrag = %f\ntime = %f\n\n", height, velocity, thrust, drag, time);
	}

	weight = WEIGHT_F; //newtons
	mass = weight / G; //kg
	//for (; time < 4.8; time += TIME_DELTA) {
	//	alt += velocity * TIME_DELTA; //meters
	//	height = alt - START_ALT; //meters
	//	density = density_from_altitude(alt); //kg per cubic meter
	//	drag = drag_from_density_and_velocity(density, velocity); //newtons
	//	brake = brake_from_density_and_velocity(density, velocity); //newtons
	//	force = -drag - weight; //newtons
	//	fprintf(logfile, "airbrakes off\n");
	//	velocity += force / mass * TIME_DELTA; //meters per second
	//	fprintf(logfile, "height = %f\nvelocity = %f\nbrake = %f\nthrust = %f\ntime = %f\n\n", height, velocity, brake, thrust, time);
	//}
	for (; velocity > 0; time += TIME_DELTA) {
		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		brake = brake_from_density_and_velocity(density, velocity); //newtons
		k = .5 * density * CD_DRAG * AREA_ROCKET;
		qsquared = -1 * mass * 9.81 / k;
		hc = ((mass / (2 * k)) * log((qsquared - (velocity*velocity)) / qsquared)) + height;
		fprintf(logfile, "hc is %f\n", hc);
		if (hc > GOAL_HEIGHT) {
			force = -weight - drag - brake;
			fprintf(logfile, "airbrakes open\n");
		}
		else {
			force = -weight - drag;
			fprintf(logfile, "airbrakes closed\n");
		}
		velocity += force / mass * TIME_DELTA; //meters per second
		fprintf(logfile, "height = %f\nvelocity = %f\nbrake = %f\ndrage = %f\ntime = %f\n\n", height, velocity, brake, drag, time);
	}
	fclose(logfile);
	return 0;
}
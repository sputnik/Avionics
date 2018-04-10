#include <stdio.h>
#include <math.h>

#define G 9.81 //meters per second squared
#define SEA_DENSITY 1.225 //kg per cubic meter
#define TIME_DELTA 0.01 //seconds
#define CD_BRAKE 1.28
#define CD_DRAG 0.42
#define AREA_ROCKET .0182414692 //meters squared
#define AREA_BRAKE .00692 //meters squared
#define START_ALT 1219.2 //meters
#define GOAL_HEIGHT 3048 //meters
#define WEIGHT_I 422.581 //newtons
#define WEIGHT_F 354.256 //newtons
#define START_THRUST 2500 //newtons
#define FUEL_BURN_RATE 14.22991494 //newtons per second
#define ACTUATION_TIME 3 // secs
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

	thrust = START_THRUST; //newtons
	weight = WEIGHT_I; //newtons
	for (time = 0; time < 4.8; time += TIME_DELTA) {
		if (time <= 4.0) {
			thrust = 3000;
		}
		else if (time > 4.0) {
			thrust -= (3750) * TIME_DELTA;
		} //thrust equation

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
	for (; time < 4.8; time += TIME_DELTA) {
		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		brake = brake_from_density_and_velocity(density, velocity); //newtons
		force = -drag - weight; //newtons
		fprintf(logfile, "airbrakes off\n");
		velocity += force / mass * TIME_DELTA; //meters per second
		fprintf(logfile, "height = %f\nvelocity = %f\nbrake = %f\nthrust = %f\ntime = %f\n\n", height, velocity, brake, thrust, time);
	}
	for (; velocity > 0; time += TIME_DELTA) {
		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		brake = brake_from_density_and_velocity(density, velocity); //newtons
		x = height;
		if (height <= 2500) {
			y = (-.000000000000019001*x*x*x*x*x) + (.00000000015977*x*x*x*x) - (.00000051643*x*x*x) + (.0007944*x*x) - (.66328 * x) + (486.62);
			//y = (-.00000000000001899*x*x*x*x*x) + (.00000000015956*x*x*x*x) - (.00000051519*x*x*x) + (.00079063*x*x) - (.65635 * x) + (480.28);
		}
		else if (height >= 2500) {
			y = (-.000000000000019001*x*x*x*x*x) + (.00000000015977*x*x*x*x) - (.00000051643*x*x*x) + (.0007944*x*x) - (.66328 * x) + (486.62);
			//y = (-.00000000000001899*x*x*x*x*x) + (.00000000015956*x*x*x*x) - (.00000051519*x*x*x) + (.00079063*x*x) - (.65635 * x) + (480.28);
		}
		fprintf(logfile, "velocity = %f\n", velocity);
		fprintf(logfile, "y = %f\n", y);
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
				force = -drag - brake - weight; //newtons
				fprintf(logfile, "airbrakes open\n");
			}
			else if (t < ACTUATION_TIME) {
				brake = brake * t / ACTUATION_TIME;
				force = -drag - brake - weight; //newtons
				percentopen = t * 33.33333;
				fprintf(logfile, "airbrakes opening\nairbrakes %f percent open\n", percentopen);
				t = t + TIME_DELTA;
			}
		}
		else if (a == 0) {
			if (t <= 0) {
				force = -drag - weight;
				fprintf(logfile, "airbrakes closed\n");
			}
			else if (t >0) {
				brake = brake * t / ACTUATION_TIME;
				force = -drag - brake - weight; //newtons
				percentopen = t * 33.33333;
				fprintf(logfile, "airbrakes closing\nairbrakes %f percent open\n", percentopen);
				t = t - TIME_DELTA;
			}
		}
		//force = -drag - weight;
		velocity += force / mass * TIME_DELTA; //meters per second

		fprintf(logfile, "height = %f\nvelocity = %f\nbrake = %f\ndrage = %f\ntime = %f\n\n", height, velocity, brake, drag, time);
	}
	fclose(logfile);
	return 0;
}
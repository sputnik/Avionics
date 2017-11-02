#include <stdio.h>
#include <math.h>

#define G 9.81 //meters per second squared
#define SEA_DENSITY 1.225 //kg per cubic meter
#define TIME_DELTA 0.1 //seconds
#define CD_BRAKE 1.28
#define CD_DRAG 0.75
#define AREA_ROCKET .0248286665 //meters squared
#define AREA_BRAKE .01032256 //meters squared
#define START_ALT 1219.2 //meters
#define GOAL_HEIGHT 7000 //meters
#define WEIGHT_I 380.75175 //newtons
#define WEIGHT_F 198.18765 //newtons
#define START_THRUST 8500 //newtons
#define FUEL_BURN_RATE 34.446 //newtons per second


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
	return .5 * dense * vel * vel * CD_BRAKE * AREA_ROCKET;
}

int main(void)
{
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

	thrust = START_THRUST; //newtons
	weight = WEIGHT_I; //newtons
	for (time = 0; time < 5.3; time += TIME_DELTA) {
		if (time >= 2.5) {
			thrust -= (time < 4.9 ? 400 : 18750) * TIME_DELTA;
		} //thrust equation

		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		weight -= FUEL_BURN_RATE * TIME_DELTA; //newtons
		force = thrust - drag - weight; //newtons
		mass = weight / G; //kg
		velocity += force / mass * TIME_DELTA; //meters per second

		printf("height = %f\nvelocity = %f\ntime = %f\n\n", height, velocity, time);
	}

	weight = WEIGHT_F; //newtons
	mass = weight / G; //kg
	for (; velocity > 0; time += TIME_DELTA) {
		tend = (GOAL_HEIGHT - height) * 2  / velocity; //seconds
		fneed = velocity * mass / tend; //newtons
		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		brake = brake_from_density_and_velocity(density, velocity); //newtons

		if (drag + weight < fneed) {
			force = -drag - brake - weight; //newtons
			printf("airbrakes on\n");
		}
		else {
			if (height >= GOAL_HEIGHT) {
				force = -drag - brake - weight; //newtons
				printf("airbrakes on\n");
			}
			else if (height < GOAL_HEIGHT) {
				force = -drag - weight; //newtons
				printf("airbrakes off\n");
			}
		}

		velocity += force / mass * TIME_DELTA; //meters per second

		printf("height = %f\nvelocity = %f\ntime = %f\n\n", height, velocity, time);
	}
	return 0;
}
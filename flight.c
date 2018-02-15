#include <stdio.h>
#include <math.h>

#define G 9.81 //meters per second squared
#define SEA_DENSITY 1.225 //kg per cubic meter
#define TIME_DELTA 0.1 //seconds
#define CD_BRAKE 1
#define CD_DRAG 0.4
#define AREA_ROCKET .0182414692 //meters squared
#define AREA_BRAKE .0174 //meters squared
#define START_ALT 1219.2 //meters
#define GOAL_HEIGHT 3048 //meters
#define WEIGHT_I 373.651 //newtons
#define WEIGHT_F 306.927 //newtons
#define START_THRUST 2500 //newtons
#define FUEL_BURN_RATE 15.44504651 //newtons per second


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
	for (time = 0; time < 4.4; time += TIME_DELTA) {
		if (time <= 2.0) {
			thrust += 250 * TIME_DELTA;
		}
		else if (time > 2.0) {
			thrust -= (time < 4.0 ? 250 : 6250) * TIME_DELTA;
		} //thrust equation

		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		weight -= FUEL_BURN_RATE * TIME_DELTA; //newtons
		force = thrust - drag - weight; //newtons
		mass = weight / G; //kg
		velocity += force / mass * TIME_DELTA; //meters per second

		printf("height = %f\nvelocity = %f\nthrust = %f\ntime = %f\n\n", height, velocity, thrust, time);
	}

	weight = WEIGHT_F; //newtons
	mass = weight / G; //kg
	for (; time < 7.3; time += TIME_DELTA) {
		tend = (GOAL_HEIGHT - height) * 2 / velocity; //seconds
		fneed = velocity * mass / tend; //newtons
		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		brake = brake_from_density_and_velocity(density, velocity); //newtons
		force = -drag - weight; //newtons
		printf("airbrakes off\n");
		velocity += force / mass * TIME_DELTA; //meters per second
		printf("height = %f\nvelocity = %f\nbrake = %f\nthrust = %f\ntime = %f\n\n", height, velocity, brake, thrust, time);
	}
	for (; velocity > 0; time += TIME_DELTA) {
		tend = (GOAL_HEIGHT - height) * 2  / velocity; //seconds
		fneed = velocity * mass / tend; //newtons
		alt += velocity * TIME_DELTA; //meters
		height = alt - START_ALT; //meters
		density = density_from_altitude(alt); //kg per cubic meter
		drag = drag_from_density_and_velocity(density, velocity); //newtons
		brake = brake_from_density_and_velocity(density, velocity); //newtons
		x = height;
		if (height <= 2500) {
			//y = (-.00000000000000000000071763*x*x*x*x*x*x*x) + (.0000000000000000078672*x*x*x*x*x*x) - (.000000000000037169*x*x*x*x*x) + (.000000000096678*x*x*x*x) - (.0000001528*x*x*x) + (.0001648*x*x) - (0.2431*x) + (447.04);
			y = (.0000067304*x*x) - (.13644*x) + 412.04;
		}
		else if (height >= 2500) {
			//y = (-.000000000016705*x*x*x*x*x) + (.0000002291*x*x*x*x) - (.0012558*x*x*x) + (3.4389*x*x) - (4705*x) + (2572900);
			//y = (-.00000000000000044502*x*x*x*x*x*x*x) + (.0000000000085817*x*x*x*x*x*x) - (.000000070877*x*x*x*x*x) + (.00032499*x*x*x*x) - (.89351*x*x*x) + (1472.9*x*x) - (1348000*x) + (528380000);
			z = (x - 2852.4) / 167.86;
			y = (-2.2266*z*z*z*z*z) - (7.2645*z*z*z*z) - (4.8687*z*z*z) + (0.00029288*z*z) - (26.425*z) + 62.608;
		}
		//y = (-0.11493 * x) + 395.26;
		//y = (-.12299 * x) + 407.94;
		//y = (-.00000000000000000005112*x*x*x*x*x*x*x) + (.00000000000000067005*x*x*x*x*x*x) - (.0000000000036784*x*x*x*x*x) + (.000000010943*x*x*x*x) - (.000019025*x*x*x) + (.019321*x*x) - (10.737*x) + (2839);
		//y = (-.000000000000029742*x*x*x*x*x) + (.00000000027068*x*x*x*x) - (.00000096078*x*x*x) + (.0016631*x*x) - (1.5184*x) + 856.86;
		//y = ((-.00000000000000000005112*x*x*x*x*x*x*x) + (.00000000000000067005*x*x*x*x*x*x) - (.0000000000036784*x*x*x*x*x) + (.000000010943*x*x*x*x) - (.000019025*x*x*x) + (.019321*x*x) - (10.737*x) + (2839) + (-.000000000000029742*x*x*x*x*x) + (.00000000027068*x*x*x*x) - (.00000096078*x*x*x) + (.0016631*x*x) - (1.5184*x) + 856.86) / 2;
		printf("velocity = %f\n", velocity);
		printf("y = %f\n", y);
		if (velocity >= y) {
			a = 1;
			//printf("airbrakes opening\n");
		}
		else if (velocity < y) {
			a = 0;
			//printf("airbrakes closing");
		}
		if (a == 1) {
			if (t >= 2) {
				force = -drag - brake - weight; //newtons
				printf("airbrakes open\n");
			}
			else if (t < 2) {
				force = -drag - brake - weight; //newtons
				force = force * t / 2;
				percentopen = t * 50;
				printf("airbrakes opening\nairbrakes %f percent open\n", percentopen);
				t = t + TIME_DELTA;
			}
		}
		else if (a == 0) {
			if (t <= 0) {
				force = -drag - weight;
				printf("airbrakes closed\n");
			}
			else if (t >0) {
				force = -drag - brake - weight; //newtons
				force = force * t / 2;
				percentopen = t * 50;
				printf("airbrakes closing\nairbrakes %f percent open\n", percentopen);
				t = t - TIME_DELTA;
			}
		}

		velocity += force / mass * TIME_DELTA; //meters per second

		printf("height = %f\nvelocity = %f\nbrake = %f\ntime = %f\n\n", height, velocity, brake, time);
	}
	return 0;
}
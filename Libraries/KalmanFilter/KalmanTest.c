#include <stdio.h>
#include <stdlib.h>

//global variables needed 
#define R 0.15 //noise covariance (i think that's what it's called)

double P = 1;
/*
 * This method uses a kalman filter to elimate signal noise and provide a estimation on what the actual measurement is. Becomes more accurate after more iteration. 
 *
 * Inputs: 
 * double Measurement is the current reading from the sensor 
 *
 * P is prior error covariance, updated during each iteration
 * P should be defaulted to 1 
 * 
 * prevXHat is the estimation from last iteration
 * prevXHat should be defaulted to 0
 * 
 * Outputs:
 * double xHat : current estimation
*/
double kalman(double measurement, double prevXHat, double *P){
	//equations can be found at http://bilgin.esme.org/BitsAndBytes/KalmanFilterforDummies
	
	double xHat; //current estimation
	double K; //current Kalman Gain (i think that's what it is)
	
	double prevP = *P; //used for debugging only
	K = *P/(*P + R); // calculate the current Kalman Gain 
	xHat = prevXHat + K * ( measurement - prevXHat); //calculate current XHat
	*P = (1 - K) * *P; //update P
	
	//printf("%.6f, %.6f, %.6f, %.6f, %.6f, %.6f\n", measurement, prevXHat, prevP, xHat, *P,K);
	
	return xHat;
}

void main(int argc, char* argv[]) {
	if (argc < 1) printf("Invaild Input\n");
	FILE * fp = fopen(argv[1], "r");
	if (fp == NULL) printf("Invaild Input\n");
	
	
	double pressure;
	double temp;
	double processed = 0;
	int counter = 0;
	while (!feof(fp)){
		fscanf(fp, "%lf , %lf", &pressure, &temp);
		processed = kalman(pressure, processed, &P);
		printf("%d: Input: %.3f, Output: %.3f\n", counter, pressure, processed);
		counter++;
	}
	
	printf("Final Processed is %.3f", processed);
	fclose(fp);
	
}
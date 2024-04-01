/*
* kernels.c
* - Holds all the function implementations for the kernels
*/
// Pre-defined libraries
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// for random number generation
#include <time.h>

void displayTableHeader() {
	printf("---------------------------------------------\n");
	printf("%5s | %15s | %15s\n", "Index", "Vector Z (C)", "Vector Z (x86-64)");
	printf("---------------------------------------------\n");
}

void displayTableBody(float* z, float* asmZ) {
	for (int i = 0; i < 10; i++) {
		printf("%5.0d | %15.6f | %15.6f\n", i + 1, z[i], asmZ[i]);
	}
}

void displayTableFooter() {
	printf("=============================================\n");
}


float random_float_generator(float min, float max) {
	return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}


/***** SAXPY Operation *****/
void saxpyC(int n, float a, float* x, float* y, float* z) {
	for (int i = 0; i < n; i++) {
		z[i] = a * x[i] + y[i];
	}
}


void computeAveTime(double* time, int iterations, double* totalTime, double* averageTime, char mode) {
	// Compute the total time
	for (int i = 0; i < iterations; i++) {
		*totalTime += time[i];
	}

	// Compute the average time
	*averageTime = *totalTime / iterations;

	// Display the average time
	switch(mode) {
		case 'C':
			printf("Average time (for C)\t: %f\n", *averageTime);
			break;
		case 'A':
			printf("Average time (for ASM)\t: %f\n", *averageTime);
			break;
	}
}
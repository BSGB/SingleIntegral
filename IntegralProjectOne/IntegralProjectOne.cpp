// IntegralProjectOne.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <conio.h>
#include <time.h>
#include <omp.h>
#include <iostream>

using namespace std;

float internal_function(float x, int k) {
	return sin(sqrt(k) * x) / (1 + x);
}

void tictac(int miliseconds) {
	clock_t endwait;
	endwait = clock() + miliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < endwait) {}
}

double workTime(clock_t time) {
	return static_cast<double> (time) / CLOCKS_PER_SEC;
}

int main()
{
	omp_set_nested(1);
	int k, j;

	float start = 0;
	float end = 10 * M_PI;

	float number_of_chunks = 10000;

	float dx = (end - start) / number_of_chunks;
	float sum = 0;


#pragma omp parallel for default(shared) private(k, sum) schedule(static)
	for (k = 1; k <= 100; k++) {
		//tictac(50);
		sum = 0;
#pragma omp parallel for default(shared) private(j) reduction(+:sum) schedule(static)
		for (j = 1; j < 10000; j++) {
			//tictac(50);
			float x = start + j * dx;

			sum += internal_function(x, k);
		}
		sum += internal_function(start, k) / 2;
		sum += internal_function(end, k) / 2;
		sum = sum * dx;

		cout << "Dla k = " << k << " calka wynosi: " << sum << endl;
	}
	cout << "Czas pracy: " << workTime(clock()) << endl;

	return 0;
}




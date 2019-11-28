#include "progeny.h"
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

void dot_mut(progeny &pr, int size, double **R);
void saltation(progeny &pr, int size, double **R);
void inversion(progeny &pr, int size, double **R);
void translocation(progeny &pr, int size, double **R);
void chosen_mut(int meth, progeny &pr, int size, double **R);
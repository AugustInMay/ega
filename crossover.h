#include "progeny.h"
#include <time.h>
#include <set>
#include <map>
#include <iostream>
using namespace std;

void OX_crossover(progeny *par, progeny *ch, int size, double **R);
void PMX_crossover(progeny *par, progeny *ch, int size, double **R);
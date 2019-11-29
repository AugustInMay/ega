#include "progeny.h"
#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

void random_ch(progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R, bool *emerg);
void assort_plus(progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R, bool *emerg);
void assort_minus(progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R, bool *emerg);
void procreator_choice_process(int meth, progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R, bool *emerg);
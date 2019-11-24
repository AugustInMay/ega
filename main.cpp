#include "crossover.h"
#include "procreator_choice.h"
#include "mutation.h"
#include <fstream>

int main() {
    srand(time(NULL));
    double **R=new double*[15];
    for(int i=0; i<15; i++){
        R[i]=new double[15];
    }
    ifstream out("input");
    for(int i=0; i<15; i++) {
        for (int j = 0; j < 15; j++) {
            if (i == j) {
                R[i][j] = 0;
            } else {
                out >> R[i][j];
            }
        }
    }
    progeny pop[10], par[2], ch[2];
    cout<<"The 0 generation is: "<<endl;
    for(int i=0; i<10; i++){
        pop[i]=*new progeny(0, 15, NULL, true, false, true, 3, R);
        pop[i].show_gen();
    }
    cout<<endl;
    cout<<"Choosing parents with positive assortment method: "<<endl;
    assort_plus(pop, 10, 15, par, R);
    par[0].show_gen();
    par[1].show_gen();
    cout<<endl;
    cout<<"PMX crossover in process..."<<endl;
    PMX_crossover(par, ch, 15, R);
    ch[0].show_gen();
    ch[1].show_gen();
    cout<<endl;
    cout<<"Inversion mutation occured:"<<endl;
    inversion(ch[0], 15, R);
    ch[0].show_gen();
    cout<<endl;
    cout<<"Translocation mutation occured:"<<endl;
    translocation(ch[1], 15, R);
    ch[1].show_gen();
    return 0;
}
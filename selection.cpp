#include "selection.h"

int overlap_num(double coef, int size_of_pop){
    return floor((coef*size_of_pop)+0.5);
}

void overlap(int ov_num, progeny *pop, int size_of_pop, progeny *pot, bool elitist){
    set<int> ran_over;
    if(elitist){
        double tmp=0;
        int best_ind;
        for(int i=0; i<size_of_pop; i++){
            if(pop[i].get_dist()>tmp){
                best_ind=i;
            }
        }
        for(int i=0; i<ov_num; i++){
            if(pot[i].get_dist()>tmp){
                best_ind=i;
            }
        }
        ran_over.insert(best_ind);
    }
    int tmp=rand()%size_of_pop, cnt=0;
    while(ran_over.size()!=ov_num){
        ran_over.insert(tmp);
        tmp=rand()%size_of_pop;
    }
    for(auto it=ran_over.begin(); it!=ran_over.end(); ++it){
        pop[*it]=*new progeny(pot[cnt]);
        cnt++;
    }
}

void B_tournament(int ov_num, progeny *ch, int size_of_pop, int B){
    int *duel=new int[B];
    for(int i=0; i<size_of_pop; i++){

    }
}
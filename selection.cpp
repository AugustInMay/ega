#include "selection.h"

int overlap_num(double coef, int size_of_pop){
    return floor((coef*size_of_pop)+0.5);
}

void overlap(int ov_num, progeny *pop, int size_of_pop, progeny *pot, bool elitist){
    set<int> ran_over;
    progeny el_copy;
    int best_ind;
    bool pot_best=false;
    if(elitist){
        double tmp=100000;
        for(int i=0; i<size_of_pop; i++){
            if(pop[i].get_dist()<tmp){
                best_ind=i;
                tmp=pop[i].get_dist();
            }
        }
        for(int i=0; i<ov_num; i++){
            if(pot[i].get_dist()<tmp){
                best_ind=i;
                tmp=pot[i].get_dist();
                pot_best=true;
            }
        }
        el_copy=*new progeny(pop[best_ind]);
        if(pot_best){el_copy=*new progeny(pot[best_ind]);}
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
    if(elitist){
        while(ran_over.find(tmp)==ran_over.end()){
            tmp=rand()%size_of_pop;
        }
        pop[tmp]=*new progeny(el_copy);
    }
}

void B_tournament(int ov_num, progeny *ch, int size_of_ch, int B, progeny *pot){
    progeny *duel=new progeny[B];
    int tmp;
    set<int> visited;
    progeny winner;
    for(int i=0; i<ov_num; i++){
        for(int j=0; j<B; j++){
            tmp=rand()%size_of_ch;
            while(visited.find(tmp)!=visited.end()){
                tmp=rand()%size_of_ch;
            }
            visited.insert(tmp);
            duel[j]=*new progeny(ch[tmp]);
            if(j==0){
                winner=*new progeny(duel[0]);
            }
            else{
                if(winner>=duel[j]){
                    winner=*new progeny(duel[j]);
                }
            }
        }
        visited.clear();
        pot[i]=*new progeny(winner);
    }
}

void roulete(int ov_num, progeny *ch, int size_of_ch, progeny *pot){
    double *ver=new double[size_of_ch];
    double sum_dist=0, tmp;
    for(int i=0; i<size_of_ch; i++){
        sum_dist+=(1/ch[i].get_dist());
    }
    for(int i=0; i<size_of_ch; i++){
        ver[i]=((((1/ch[i].get_dist())/sum_dist)*100));
        if(i!=0){
            ver[i]+=ver[i-1];
        }
        ver[i] = floor(ver[i] + 0.5);
    }
    for(int j=0; j<ov_num; j++){
        tmp=(rand()%101);
        for(int i=0; i<size_of_ch; i++){
            if(tmp<=ver[i]){
                pot[j]=*new progeny(ch[i]);
                break;
            }
        }
    }
}
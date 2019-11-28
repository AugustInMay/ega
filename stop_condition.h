#include "progeny.h"
#include <set>
using namespace std;

double av_dist(progeny *pop, int size_of_pop){
    double ret=0;
    for(int i=0; i<size_of_pop; i++){
        ret+=pop[i].get_dist();
    }
    return ret/size_of_pop;
}

double min_dist(progeny *pop, int size_of_pop){
    double ret=100000;
    for(int i=0; i<size_of_pop; i++){
        if(pop[i].get_dist()<ret){
            ret=pop[i].get_dist();
        }
    }
    return ret;
}

int genetic_dif(progeny *pop, int size_of_pop){
    int ret=size_of_pop;
    set<int> vis;
    for(int i=0; i<size_of_pop; i++){
        for(int j=i+1; j<size_of_pop; j++){
            if(vis.find(j)==vis.end()){
                if(pop[j]==pop[i]){
                    vis.insert(j);
                    ret--;
                }
            }
        }
    }
    return ret;
}

bool stop_cond(int sw, int max_all, int *cur_all, double *prev_val, progeny *pop, int size_of_pop){
    switch(sw){
        case 1:{
            //сur is cur step
            //max is max step
            if(*cur_all==max_all){
                return true;
            }
            break;
        }
        case 2:{
            //cur is cur iterations without min changing
            //max is max -//-
            //prev_val is the global min
            if(*prev_val<=min_dist(pop, size_of_pop)){
                *cur_all+=1;
                if(*cur_all==max_all){
                    return true;
                }
            }
            else{
                *prev_val=min_dist(pop, size_of_pop);
                *cur_all=0;
                cout<<"!!!"<<endl;
                return false;
            }
            break;
        }
        case 3:{
            //cur is cur iterations without average changing
            //max is max -//-
            //prev val is the best average
            if(*prev_val<=av_dist(pop, size_of_pop)){
                *cur_all+=1;
                if(*cur_all==max_all){
                    return true;
                }
            }
            else{
                *prev_val=av_dist(pop, size_of_pop);
                *cur_all=0;
                return false;
            }
            break;
        }
        case 4:{
            //max is min  allowed difference
            if(genetic_dif(pop, size_of_pop)<max_all){
                return true;
            }
            else{
                return false;
            }
            break;
        }
        case 5:{
            //max is min  allowed difference
            //cur is cur iteration without dif changing
            //prev is max iteration -//-
            if(genetic_dif(pop, size_of_pop)<max_all){
                *cur_all+=1;
                if(*cur_all==*prev_val){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                *cur_all=0;
                return false;
            }
            break;
        }
        default:{
            break;
        }
    }
    return false;
}
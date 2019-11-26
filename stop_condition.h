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

bool stop_cond(int sw, int max_all, int *cur_all, double *prev_val, progeny *pop, int size_of_pop, int max_all_nondif){
    switch(sw){
        case 1:{
            if(*cur_all==max_all){
                return true;
            }
            return false;
        }
        case 2:{
            if(*cur_all==max_all){
                return true;
            }
            return false;
        }
        case 3:{
            if(*prev_val<=av_dist(pop, size_of_pop)){
                *cur_all++;
                if(*cur_all==max_all){
                    return true;
                }
            }
            else{
                *cur_all=0;
                return false;
            }
            break;
        }
        case 4:{
            if(genetic_dif(pop, size_of_pop)<max_all){
                return true;
            }
            else{
                return false;
            }
        }
        case 5:{
            if(genetic_dif(pop, size_of_pop)<max_all){
                *cur_all++;
                if(*cur_all==*prev_val){
                    return true;
                }
                else{
                    return false;
                }
            }
            else{
                return false;
            }
        }
        default:{
            break;
        }
    }
    return false;
}
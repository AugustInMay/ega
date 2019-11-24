//
// Created by augustinmay on 18.11.19.
//

#include "procreator_choice.h"

void random_ch(progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R){
    int tmp=rand()%size_of_pop;
    int *tmp_ar=new int[size_of_gen];
    for(int i=0; i<size_of_gen; i++){
        tmp_ar[i]=pop[tmp][i];
    }
    par[0]=*new progeny(pop[tmp].get_gener(), size_of_gen, tmp_ar, R);
    tmp=rand()%size_of_pop;
    while(par[0]==pop[tmp]){
        tmp=rand()%size_of_pop;
    }
    for(int i=0; i<size_of_gen; i++){
        tmp_ar[i]=pop[tmp][i];
    }
    par[1]=*new progeny(pop[tmp].get_gener(), size_of_gen, tmp_ar, R);
}

void assort_plus(progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R){
    double *ver=new double[size_of_pop];
    double sum_dist=0, tmp1=(rand()%100)+1, tmp2=(rand()%100)+1;
    int *tmp_ar1=new int[size_of_gen], *tmp_ar2=new int[size_of_gen];
    for(int i=0; i<size_of_pop; i++){
        sum_dist+=(1/pop[i].get_dist());
    }
    for(int i=0; i<size_of_pop; i++){
        ver[i]=((((1/pop[i].get_dist())/sum_dist)*100));
        if(i!=0){
            ver[i]+=ver[i-1];
        }
        ver[i] = floor(ver[i] + 0.5);
    }
    for(int i=0; i<size_of_pop; i++){
        if(tmp1<=ver[i]){
            for(int j=0; j<size_of_gen; j++){
                tmp_ar1[j]=pop[i][j];
            }
            par[0]=*new progeny(pop[0].get_gener(), size_of_gen, tmp_ar1, R);
            break;
        }
    }
    for(int i=0; i<size_of_pop; i++){
        if(tmp2<=ver[i]){
            for(int j=0; j<size_of_gen; j++){
                tmp_ar2[j]=pop[i][j];
            }
            par[1]=*new progeny(pop[0].get_gener(), size_of_gen, tmp_ar2, R);
            if(par[0]==par[1]){
                tmp2=(rand()%100)+1;
                i=-1;
                continue;
            }
            break;
        }
    }
    delete[] ver;
}

void assort_minus(progeny *pop, int size_of_pop, int size_of_gen, progeny *par, double **R){
    double *ver1=new double[size_of_pop], *ver2=new double[size_of_pop];
    double sum_dist1=0, sum_dist2=0, tmp1=(rand()%100)+1, tmp2=(rand()%100)+1;
    int *tmp_ar1=new int[size_of_gen], *tmp_ar2=new int[size_of_gen];
    for(int i=0; i<size_of_pop; i++){
        sum_dist1+=(1/pop[i].get_dist());
    }
    for(int i=0; i<size_of_pop; i++){
        sum_dist2+=pop[i].get_dist();
    }
    for(int i=0; i<size_of_pop; i++){
        ver1[i]=((((1/pop[i].get_dist())/sum_dist1)*100));
        ver2[i]=((pop[i].get_dist()/sum_dist2)*100);
        if(i!=0){
            ver1[i]+=ver1[i-1];
            ver2[i]+=ver2[i-1];
        }
        ver1[i] = floor(ver1[i] + 0.5);
        ver2[i]=floor(ver2[i]+0.5);
    }
    for(int i=0; i<size_of_pop; i++){
        if(tmp1<=ver1[i]){
            for(int j=0; j<size_of_gen; j++){
                tmp_ar1[j]=pop[i][j];
            }
            par[0]=*new progeny(pop[0].get_gener(), size_of_gen, tmp_ar1, R);
            break;
        }
    }
    for(int i=0; i<size_of_pop; i++){
        if(tmp2<=ver2[i]){
            for(int j=0; j<size_of_gen; j++){
                tmp_ar2[j]=pop[i][j];
            }
            par[1]=*new progeny(pop[0].get_gener(), size_of_gen, tmp_ar2, R);
            if(par[0]==par[1]){
                tmp2=(rand()%100)+1;
                i=0;
                continue;
            }
            break;
        }
    }
}
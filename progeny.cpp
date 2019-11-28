//
// Created by augustinmay on 08.11.19.
//

#include "progeny.h"
#include <iostream>
#include <time.h>
#include <set>
#include <algorithm>
using namespace std;

void closest_n_alg(double **R, int size, int *gen, bool check){
    int next=size-1, cur=rand()%size, step=1;
    double tmp=100000, dist=0;
    set<int> visited;
    gen[0]=cur;
    visited.insert(cur);
    if(check){cout<<"--STEP 1\nRandom city, that  was chosen is CITY-"<<cur+1<<endl;}
    while(visited.size()!=size){
        for(int i=0; i<size; i++){
            if(R[cur][i]<tmp&&(visited.find(i)==visited.end())){
                next=i;
                tmp=R[cur][i];
            }
        }
        tmp=100000;
        gen[step]=next;
        step++;
        dist+=R[cur][next];
        visited.insert(next);
        if(check){
            cout<<"\n\n---STEP "<<step<<"\nCurrent city is CITY-"<<cur+1<<". The closest is CITY-"<<next+1
                <<" with distance to it "<<R[cur][next]<<"\nCurrent chain is: {";
            for(int i=0; i<step; i++){
                cout<<gen[i]+1;
                if(i!=step-1){
                    cout<<", ";
                }
            }
            cout<<"}. Total distance is "<<dist<<endl;
        }
        cur=next;
        next=size-1;
    }
    if(check){
        cout<<"\nThe final track is {";
        for(int i=0; i<size; i++){
            cout<<gen[i]+1;
            cout<<", ";
            if(i!=size-1){
                if(gen[i+1]==-1) {
                    break;
                }
            }
        }
        cout<<gen[0]+1<<"}, with total distance = "<<dist+R[gen[size-1]][gen[0]]<<endl;
    }
}

void closest_c_alg(double **R, int size, int *gen, bool check){
    double dist=0, cur_dist;
    int step=1, next, cur_index, cur=rand()%size, *desired=new int[size];
    set<int> visited;
    visited.insert(cur);
    gen[0]=cur;
    if(check){cout<<"--STEP 1\nRandom city, that was chosen is CITY-"<<cur+1<<endl;}
    while(visited.size()!=size){
        int from_c, to_c;
        double temp=100000;
        for(int i=0; i<size; i++){
            if(visited.find(i)!=visited.end()){
                for(int j=0; j<size; j++){
                    if(i!=j && R[i][j]<temp&&visited.find(j)==visited.end()){
                        temp=R[i][j];
                        from_c=i;
                        to_c=j;
                    }
                }
                desired[from_c]=to_c;
                temp=100000;
            }
        }
        to_c=0;
        from_c=1;
        int from_c_index;
        for(int i=0; i<size; i++){
            if(visited.find(i)==visited.end()){
                for(int j=0; j<size; j++){
                    if(R[from_c][to_c]>R[j][i]&&visited.find(j)!=visited.end()){
                        from_c=j;
                        to_c=i;
                    }
                }
            }
        }
        for(int i=0; i<size; i++){
            if(gen[i]==from_c){
                from_c_index=i;
                break;
            }
        }
        for(int i=size; i>from_c_index+1; i--){
            gen[i]=gen[i-1];
        }
        gen[from_c_index+1]=to_c;
        cur_index=from_c_index;
        cur=gen[cur_index];
        next=gen[cur_index+1];
        step++;
        cur_dist=R[cur][next];
        visited.insert(next);
        if(check){
            cout<<"\n\n---STEP "<<step<<"\nCurrent city is CITY-"<<cur+1<<
                ". The closest is CITY-"<<next+1<<" with distance to it "<<cur_dist<<"\nHere are the candidates:"<<endl;
            for(int i=0; i<size; i++){
                if(visited.find(i)!=visited.end()&&i!=next&&step!=2){
                    cout<<"\nFrom CITY-"<<i+1<<" to CITY-"<<desired[i]+1<<" with distance="<<R[i][desired[i]]<<endl;
                }
            }
        }
        if(check){
            cout<<"\nCurrent chain is: {";
            for(int i=0; i<step; i++){
                cout<<gen[i]+1;
                if(i!=step-1){
                    cout<<", ";
                }
            }
            cout<<"}. Total distance is ";
        }
        dist=0;
        for(int i=0; i<step-1; i++){
            dist+=R[gen[i]][gen[i+1]];
        }
        if(check){cout<<dist<<endl;}
    }
    if(check){
        cout<<"\nThe final track is {";
        for(int i=0; i<size; i++){
            cout<<gen[i]+1;
            cout<<", ";
            if(i!=size-1){
                if(gen[i+1]==-1) {
                    break;
                }
            }
        }
        cout<<gen[0]+1<<"}, with total distance = "<<dist+R[gen[size-1]][gen[0]]<<endl;
    }
}

progeny::progeny(void) {
    generation=0;
    size=3;
    gen=new int[3];
}

progeny::progeny(int g, int s, int *gen, bool first, bool rnd, bool bef, int entry, double **R, bool show_proc):generation(g), size(s){
    this->gen=new int[size];
    if(first){
        int tmp;
        bool ch=true;
        if(!rnd&&!entry){cout<<"Enter the method of generating the first generation:\n"
              "1) Randomly 2) Method of the closest neighbour 3) Method of the closest city."<<endl;
        cin>>tmp;}
        else if(rnd){
            tmp=(rnd%3)+1;
        }
        if(bef){
            tmp=entry;
        }
        while(ch){
            switch(tmp){
                case 1:{
                    this->ran_gen();
                    ch=false;
                    break;
                }
                case 2:{
                    if(!bef){cout<<"---Method of the closest neighbour---\n\nWould you like to see the process of generating? y/n"<<endl;}
                    char ans='n';
                    if(!bef){cin>>ans;}
                    if(show_proc){ans='y';}
                    if(ans=='Y'||ans=='y'){
                        closest_n(R, true);
                    }
                    else if(ans=='N'||ans=='n'){
                        closest_n(R, false);
                    }
                    else{
                        cout<<"Wrong input. Please try again."<<endl;
                        break;
                    }
                    ch=false;
                    break;
                }
                case 3:{
                    if(!bef){cout<<"---Method of the closest city---\n\nWould you like to see the process of generating? y/n"<<endl;}
                    char ans='n';
                    if(!bef){cin>>ans;}
                    if(show_proc){ans='y';}
                    if(ans=='Y'||ans=='y'){
                        closest_c(R, true);
                    }
                    else if(ans=='N'||ans=='n'){
                        closest_c(R, false);
                    }
                    else{
                        cout<<"Wrong input. Please try again."<<endl;
                        break;
                    }
                    ch=false;
                    break;
                }
                default:{
                    cout<<"Wrong input! Try again."<<endl;
                    break;
                }
            }
        }
    }
    else if(!first){
        for(int i=0; i<size; i++){
            this->gen[i]=gen[i];
        }
    }
    this->dist_cnt(R);
}

progeny::~progeny(void) {
    delete[] gen;
}

void progeny::dist_cnt(double **R) {
    double tmp=0;
    for(int i=0; i<size-1; i++){
        tmp+=R[gen[i]][gen[i+1]];
    }
    tot_dist=(tmp+R[gen[size-1]][gen[0]]);
}

void progeny::ran_gen() {
    set<int> visited;
    int temp=rand()%size;
    for(int i=0; i<size; i++){
        while(visited.find(temp)!=visited.end()){
            temp=rand()%size;
        }
        visited.insert(temp);
        gen[i]=temp;
    }
}

void progeny::closest_n(double **R, bool pre) {
    if(pre){
        closest_n_alg(R, size, gen, true);
    }
    else{
        closest_n_alg(R, size, gen, false);
    }
}

void progeny::closest_c(double **R, bool pre) {
    if(pre){
        closest_c_alg(R, size, gen, true);
        return;
    }
    else{
        closest_c_alg(R, size, gen, false);
        return;
    }
}

void progeny::show_gen() {
    for(int i=0; i<size; i++){
        cout<<gen[i]+1<<"-";
    }
    cout<<gen[0]+1<<"   Its distance is "<<tot_dist<<endl;
}


bool progeny::operator==(const progeny &r) {
    if(this->size==r.size){
        for(int i=0; i<this->size; i++){
            if(this->gen[i]!=r.gen[i]){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

bool progeny::operator>=(const progeny &r){
    if(this->tot_dist>=r.tot_dist){
        return true;
    }
    return false;
}

bool progeny::operator>=(const int &r) {
    if(this->tot_dist>=r){
        return true;
    }
    return false;
}

bool progeny::operator!=(const progeny &r) {
    return !(this->operator==(r));
}

int& progeny::operator[](int x) {
    return gen[x];
}

int progeny::get_gener() {
    return generation;
}

double progeny::get_dist() {
    return tot_dist;
}

bool progeny::operator==(const int *r) {
    for(int i=0; i<size; i++){
        if(r[i]!=gen[i]){
            return false;
        }
    }
    return true;
}

progeny::progeny(const progeny &pr){
    generation=pr.generation;
    size=pr.size;
    tot_dist=pr.tot_dist;
    gen=new int[size];
    for(int i=0; i<size; i++){
        gen[i]=pr.gen[i];
    }
}
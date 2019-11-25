#include "crossover.h"
#include "procreator_choice.h"
#include "mutation.h"
#include "selection.h"
#include <fstream>

int factorial(int i){
    if (i==0) return 1;
    else return i*factorial(i-1);
}

int main() {
    srand(time(NULL));
    double **R=new double*[15];
    int init_pop_meth, num_of_pop;
    char proc_of_gen_ans;
    bool init_pop_check=true, proc_of_gen;
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
    cout<<"First things first. By which method will the INITIAL POPULATION be built?\n1)Randomly 2)Greedy algorithm "
          "(closest neighbour) 3) Greedy algorithm (closest city)\n!WARNING! The chosen method will effect the ammount "
          "of population."<<endl;
    cin>>init_pop_meth;
    while(init_pop_check){
        switch(init_pop_meth){
            case 1:{
                cout<<"\nRandom method was chosen;\nNow choose the number of population. You can choose from 2 to "
                      ""<<factorial(15)<<". However it is recommended not to take a big population."<<endl;
                cin>>num_of_pop;
                while(num_of_pop<2||num_of_pop>factorial(15)){
                    cout<<"Wrong input! Try again..."<<endl;
                    cin>>num_of_pop;
                }
                init_pop_check=false;
                break;
            }
            case 2:{
                cout<<"\nGreedy algorithm (closest neighbour) was chosen;\nNow choose the number of population. "
                      "You can choose from 2 to 15"<<endl;
                cin>>num_of_pop;
                while(num_of_pop<2||num_of_pop>15){
                    cout<<"Wrong input! Try again..."<<endl;
                    cin>>num_of_pop;
                }
                cout<<"\nWould you like to see the process of generating? \n1) yes 2) no"<<endl;
                cin>>proc_of_gen_ans;
                while(proc_of_gen_ans!='y'&&proc_of_gen_ans!='Y'&&proc_of_gen_ans!='n'&&proc_of_gen_ans!='N'){
                    cout<<"Wrong input! Try again..."<<endl;
                    cin>>proc_of_gen_ans;
                }
                if(proc_of_gen_ans=='y'||proc_of_gen_ans=='Y'){
                    proc_of_gen=true;
                }
                else{
                    proc_of_gen=false;
                }
                init_pop_check=false;
                break;
            }
            case 3:{
                cout<<"\nGreedy algorithm (closest city) was chosen;\nNow choose the number of population. "
                      "You can choose from 2 to 15"<<endl;
                cin>>num_of_pop;
                while(num_of_pop<2||num_of_pop>15){
                    cout<<"Wrong input! Try again..."<<endl;
                    cin>>num_of_pop;
                }
                cout<<"\nWould you like to see the process of generating? \n1) yes 2) no"<<endl;
                cin>>proc_of_gen_ans;
                while(proc_of_gen_ans!='y'&&proc_of_gen_ans!='Y'&&proc_of_gen_ans!='n'&&proc_of_gen_ans!='N'){
                    cout<<"Wrong input! Try again..."<<endl;
                    cin>>proc_of_gen_ans;
                }
                if(proc_of_gen_ans=='y'||proc_of_gen_ans=='Y'){
                    proc_of_gen=true;
                }
                else{
                    proc_of_gen=false;
                }
                init_pop_check=false;
                break;
            }
            default:{
                cout<<"Wrong input! Try again..."<<endl;
                break;
            }
        }
    }
    progeny *population=new progeny[num_of_pop];
    for(int i=0; i<num_of_pop; i++){
        population[i]=*new progeny(0, 15, NULL, true, false, true, init_pop_meth, R, proc_of_gen);
        for(int j=0; j<i; j++){
            if(population[j]==population[i]){
                i--;
                continue;
            }
        }
    }
    for(int i=0; i<num_of_pop; i++){
        population[i].show_gen();
    }
    return 0;
}
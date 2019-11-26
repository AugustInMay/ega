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
    int init_pop_meth, num_of_pop, mut_procent=10, mut_rand=rand()%101, mut_ind;
    char proc_of_gen_ans;
    bool init_pop_check=true, proc_of_gen, crossover_ind;
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
                cout<<"\n-----Random method was chosen-----\nNow choose the number of population. You can choose from 2 to "
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
                cout<<"\n-----Greedy algorithm (closest neighbour) was chosen-----\nNow choose the number of population. "
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
                cout<<"\n-----Greedy algorithm (closest city) was chosen-----\nNow choose the number of population. "
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
    init_pop_check=true;
    cout<<"Now choose the crossover:\n1) OX-crossover 2) PMX-crossover"<<endl;
    while(init_pop_check){
        cin>>init_pop_meth;
        switch(init_pop_meth){
            case 1:{
                crossover_ind=true;
                init_pop_check=false;
                cout<<"\n-----OX-crossover was chosen-----"<<endl;
                break;
            }
            case 2:{
                crossover_ind=false;
                init_pop_check=false;
                cout<<"\n-----PMX-crossover was chosen-----"<<endl;
                break;
            }
            default:{
                cout<<"Wrong input! Try again..."<<endl;
                break;
            }
        }
    }
    init_pop_check=true;
    cout<<"Now choose the mutation:\n1) Dot mutation 2) Saltation 3) Inversion 4) Translocation"<<endl;
    while(init_pop_check){
        cin>>mut_ind;
        switch(mut_ind){
            case 1:{
                init_pop_check=false;
                cout<<"\n-----Dot mutation was chosen-----"<<endl;
                break;
            }
            case 2:{
                init_pop_check=false;
                cout<<"\n-----Saltation was chosen-----"<<endl;
                break;
            }
            case 3:{
                init_pop_check=false;
                cout<<"\n-----Inversion was chosen-----"<<endl;
                break;
            }
            case 4:{
                init_pop_check=false;
                cout<<"\n-----Translocation was chosen-----"<<endl;
                break;
            }
            default:{
                cout<<"Wrong input! Try again..."<<endl;
                break;
            }
        }
    }
    cout<<"Current possibility of mutation is 10%. However you can change it. Would you like to do it? y/n"<<endl;
    cin>>proc_of_gen_ans;
    while(proc_of_gen_ans!='y'&&proc_of_gen_ans!='Y'&&proc_of_gen_ans!='n'&&proc_of_gen_ans!='N'){
        cout<<"Wrong input! Try again..."<<endl;
        cin>>proc_of_gen_ans;
    }
    if(proc_of_gen_ans=='y'||proc_of_gen_ans=='Y'){
        cout<<"Please, enter the possibility of mutation (from 0 to 100)";
        cin>>mut_procent;
        while(mut_procent<=-1||mut_procent>=101){
            cout<<"Wrong input! Try again..."<<endl;
            cin>>mut_procent;
        }
    }
    progeny *population=new progeny[num_of_pop];
    for(int i=0; i<num_of_pop; i++){
        if(proc_of_gen){
            cout<<"\n\n-----"<<i+1<<"-species-----"<<endl;
        }
        population[i]=*new progeny(0, 15, NULL, true, false, true, init_pop_meth, R, proc_of_gen);
        for(int j=0; j<i; j++){
            if(population[j]==population[i]){
                if(proc_of_gen){
                    cout<<"\n!!!However, there is this gen already. Retrying..."<<endl;
                }
                i--;
                continue;
            }
        }
    }
    return 0;
}
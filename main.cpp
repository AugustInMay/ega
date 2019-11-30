#include "crossover.h"
#include "procreator_choice.h"
#include "mutation.h"
#include "selection.h"
#include "stop_condition.h"
#include <fstream>

int factorial(int i){
    if (i==0) return 1;
    else return i*factorial(i-1);
}

int main() {
    ofstream outdata, out_more_data;
    outdata.open("Table.csv");
    srand(time(NULL));
    double **R=new double*[15], prev_stop_cond_val=0;
    int init_pop_meth=1, mut_procent=10, mut_rand=rand()%101, cross_meth=1, cur_stop_cond_val=0, stop_cond_meth=1,
    num_of_iterations=1, best_ind, global_ind, iteration_overall=0;
    char proc_of_gen_ans;
    bool init_pop_check=true, proc_of_gen=false, elitist=false, emergency_stop=false;
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
    int num_of_pop[4];
    num_of_pop[0]=10;
    num_of_pop[1]=30;
    num_of_pop[2]=50;
    num_of_pop[3]=100;
    double G_coef[3];
    G_coef[0]=(1.0)/double(num_of_pop[0]);
    G_coef[1]=0.5;
    G_coef[2]=1;
    int mut_ind[4];
    mut_ind[0]=1;
    mut_ind[1]=2;
    mut_ind[2]=3;
    mut_ind[3]=4;
    int procreator_pairs_num[3];
    procreator_pairs_num[0]=5;
    procreator_pairs_num[1]=10;
    procreator_pairs_num[2]=num_of_pop[0]/2;
    int selec_method[2];
    selec_method[0]=1;
    selec_method[1]=2;
    int B[2];
    B[0]=2;
    B[1]=num_of_pop[0]/5;
    bool crossover_ind[2];
    crossover_ind[0]=true;
    crossover_ind[1]=false;
    int max_stop_cond_val[3];
    max_stop_cond_val[0]=10;
    max_stop_cond_val[1]=50;
    max_stop_cond_val[2]=100;
    int procr_choice[3];
    procr_choice[0]=1;
    procr_choice[1]=2;
    procr_choice[2]=3;
    /*cout<<"First things first. By which method will the INITIAL POPULATION be built?\n1)Randomly 2)Greedy algorithm "
          "(closest neighbour) 3) Greedy algorithm (closest city)\n!WARNING! The chosen method will effect the ammount "
          "of population."<<endl;
    while(init_pop_check){
        cin>>init_pop_meth;
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
        cin>>cross_meth;
        switch(cross_meth){
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
    cout<<"Now choose the number of procreator pairs (twice of that is the number of children). You can choose from 1 to "<<num_of_pop*(num_of_pop-1)/2<<endl;
    while(true){
        cin>>procreator_pairs_num;
        if(procreator_pairs_num<1||procreator_pairs_num>(num_of_pop*(num_of_pop-1)/2)){
            cout<<"Wrong input! Try again..."<<endl;
        }
        else{
            break;
        }
    }
    init_pop_check=true;
    cout<<"There are now "<<procreator_pairs_num<<" pairs of procreators, and "<<procreator_pairs_num*2<<" possible children"<<endl;
    cout<<"Choose by which method will the procreators be chosen:\n1) Randomly 2) Positive associative mating 3) Negative associative mating"<<endl;
    while(init_pop_check){
        cin>>procr_choice;
        switch(procr_choice){
            case 1:{
                init_pop_check=false;
                cout<<"\n-----Random method was chosen-----"<<endl;
                break;
            }
            case 2:{
                init_pop_check=false;
                cout<<"\n-----Positive associative mating was chosen-----"<<endl;
                break;
            }
            case 3:{
                init_pop_check=false;
                cout<<"\n-----Negative associative mating was chosen-----"<<endl;
                break;
            }
            default:{
                cout<<"Wrong input! Try again..."<<endl;
                break;
            }
        }
    }
    cout<<"Now enter the g coefficient (0;1] to choose the number of procreators which will be replaced by the progenies:"<<endl;
    while(true){
        cin>>G_coef;
        if(G_coef<=0||G_coef>1){
            cout<<"Wrong input! Try again..."<<endl;
        }
        else{
            cout<<"The overlap number is "<<overlap_num(G_coef, num_of_pop)<<". Is this acceptable? y/n";
            cin>>proc_of_gen_ans;
            while(proc_of_gen_ans!='y'&&proc_of_gen_ans!='Y'&&proc_of_gen_ans!='n'&&proc_of_gen_ans!='N'){
                cout<<"Wrong input! Try again..."<<endl;
                cin>>proc_of_gen_ans;
            }
            if(proc_of_gen_ans=='y'||proc_of_gen_ans=='Y'){
                break;
            }
            else{
                cout<<"Please, enter another coefficient..."<<endl;
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
    init_pop_check=true;
    cout<<"Please choose the selection method:\n1) Proportional method 2) B-tournament"<<endl;
    while(init_pop_check){
        cin>>selec_method;
        switch(selec_method){
            case 1:{
                cout<<"\n-----Proportional method was chosen-----"<<endl;
                init_pop_check=false;
                break;
            }
            case 2:{
                cout<<"\n-----B-tournament was chosen-----\nNow enter B (from 2 to "<<procreator_pairs_num*2<<"):"<<endl;
                cin>>B;
                while(B<2||B>procreator_pairs_num*2){
                    cout<<"Wrong input! Try again..."<<endl;
                    cin>>B;
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
    cout<<"Would you like it to be an elitist one? y/n"<<endl;
    cin>>proc_of_gen_ans;
    while(proc_of_gen_ans!='y'&&proc_of_gen_ans!='Y'&&proc_of_gen_ans!='n'&&proc_of_gen_ans!='N'){
        cout<<"Wrong input! Try again..."<<endl;
        cin>>proc_of_gen_ans;
    }
    if(proc_of_gen_ans=='y'||proc_of_gen_ans=='Y'){
        elitist=true;
    }
    else{
        elitist=false;
    }
    init_pop_check=true;
    cout<<"Finally choose the stop condition\n1) Iteration condition 2) Number of generations without "
          "max improvement 3) Number of generations without average improvement 4) Low difference in population "
          "immediately 5) Low difference in population for a period of time"<<endl;
    while(init_pop_check){
        cin>>stop_cond_meth;
        switch(stop_cond_meth){
            case 1:{
                cout<<"\n-----Iteration condition was chosen-----\nEnter the maximum iteration"<<endl;
                cin>>max_stop_cond_val;
                init_pop_check=false;
                break;
            }
            case 2:{
                cout<<"\n-----Number of generations without max improvement was chosen-----\nEnter the number:"<<endl;
                cin>>max_stop_cond_val;
                init_pop_check=false;
                break;
            }
            case 3:{
                cout<<"\n-----Number of generations without average improvement was chosen-----\nEnter the number:"<<endl;
                cin>>max_stop_cond_val;
                init_pop_check=false;
                break;
            }
            case 4:{
                cout<<"\n-----Low difference in population immediately was chosen-----\nEnter the min difference:"<<endl;
                cin>>max_stop_cond_val;
                init_pop_check=false;
                break;
            }
            case 5:{
                cout<<"\n-----Low difference in population for a period of time was chosen-----\nEnter the min difference:"<<endl;
                cin>>max_stop_cond_val;
                cout<<"\nEnter the number of iterations:"<<endl;
                cin>>prev_stop_cond_val;
                init_pop_check=false;
                break;
            }
            default:{
                cout<<"Wrong input! Try again..."<<endl;
                break;
            }
        }
    }*/
    for(int cross_ind=0; cross_ind<2; cross_ind++){
        for(int num_of_pop_ind=0; num_of_pop_ind<4; num_of_pop_ind++){
            for(int G_coef_ind=0; G_coef_ind<3; G_coef_ind++){
                G_coef[0]=(1.0)/double(num_of_pop[num_of_pop_ind]);
                for(int ind_of_mut=0; ind_of_mut<4; ind_of_mut++){
                    for(int procr_pairs_ind=0; procr_pairs_ind<3; procr_pairs_ind++){
                        procreator_pairs_num[2]=num_of_pop[num_of_pop_ind]/2;
                        for(int selec_meth_ind=0; selec_meth_ind<2; selec_meth_ind++){
                            if(selec_meth_ind==1){
                                for(int B_ind=0; B_ind<2; B_ind++){
                                    B[1]=(procreator_pairs_num[procr_pairs_ind]*2)/5;
                                    for(int step_max_ind=0; step_max_ind<3; step_max_ind++){
                                        for(int procr_choice_ind=0; procr_choice_ind<3; procr_choice_ind++){
                                            iteration_overall++;
                                            progeny *ch=new progeny[procreator_pairs_num[procr_pairs_ind]*2];
                                            progeny *population=new progeny[num_of_pop[num_of_pop_ind]];
                                            progeny *pot=new progeny[overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind])];
                                            emergency_stop=false;
                                            for(int i=0; i<num_of_pop[num_of_pop_ind]; i++){
                                                /*if(proc_of_gen){
                                                    cout<<"\n\n-----"<<i+1<<"-species-----"<<endl;
                                                }*/
                                                population[i]=*new progeny(0, 15, NULL, true, false, true, init_pop_meth, R, proc_of_gen);
                                                for(int j=0; j<i; j++){
                                                    if(population[j]==population[i]){
                                                        /*if(proc_of_gen){
                                                            cout<<"\n!!!However, there is this gen already. Retrying..."<<endl;
                                                        }*/
                                                        i--;
                                                        continue;
                                                    }
                                                }
                                            }
                                            /*switch(stop_cond_meth){
                                                case 2:{
                                                    prev_stop_cond_val=min_dist(population, num_of_pop);
                                                    break;
                                                }
                                                case 3:{
                                                    prev_stop_cond_val=av_dist(population, num_of_pop);
                                                    break;
                                                }
                                            }*/
                                            double ret=100000;
                                            cout<<"CR-"<<cross_ind<<", PN-"<<num_of_pop[num_of_pop_ind]<<", G-"<<overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind])<<", MT-"<<mut_ind[ind_of_mut]<<", PP-"<<procreator_pairs_num[procr_pairs_ind]<<", SM-"<<selec_method[selec_meth_ind]<<", B-"<<B[B_ind]<<", MAX_STEP"<<max_stop_cond_val[step_max_ind]<<", PC-"<<procr_choice[procr_choice_ind]<<endl;
                                            //cout<<"\n\n-----The 0 generation-----"<<endl;
                                            for(int i=0; i<num_of_pop[num_of_pop_ind]; i++){
                                                //population[i].show_gen();
                                                if(population[i].get_dist()<=ret){
                                                    ret=population[i].get_dist();
                                                    global_ind=i;
                                                }
                                            }
                                            progeny par_per_it[2], ch_per_it[2], solution=*new progeny(population[global_ind]);
                                            cout<<"\nThe initial global solution is:"<<endl;
                                            solution.show_gen();
                                            while(true){
                                                //cout<<"\n\n-----The "<<num_of_iterations<<" generation-----"<<endl;
                                                num_of_iterations++;
                                                int j=0;
                                                for(int i=0; i<procreator_pairs_num[procr_pairs_ind]; i++){
                                                    procreator_choice_process(procr_choice[procr_choice_ind], population, num_of_pop[num_of_pop_ind], 15, par_per_it, R, &emergency_stop);
                                                    if(emergency_stop){
                                                        goto Finished1;
                                                    }
                                                    crossover(par_per_it, ch_per_it, 15, R, crossover_ind[cross_ind]);
                                                    ch[j]=*new progeny(ch_per_it[0]);
                                                    ch[j+1]=*new  progeny(ch_per_it[1]);
                                                    j+=2;
                                                }
                                                /*cout<<"\n\nCreated children:"<<endl;
                                                for(int i=0; i<procreator_pairs_num[procr_pairs_ind]*2; i++){
                                                    ch[i].show_gen();
                                                }*/
                                                for(int i=0; i<procreator_pairs_num[procr_pairs_ind]*2; i++){
                                                    mut_rand=rand()%101;
                                                    if(mut_rand<=mut_procent){
                                                        //cout<<"Mutation occured!!!"<<endl;
                                                        //ch[i].show_gen();
                                                        chosen_mut(mut_ind[ind_of_mut], ch[i], 15, R);
                                                        //cout<<"Changed to..."<<endl;
                                                        //ch[i].show_gen();
                                                    }
                                                }
                                                B_tournament(overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind]), ch, procreator_pairs_num[procr_pairs_ind]*2, B[B_ind], pot);
                                                if(stop_cond_meth==1){
                                                    cur_stop_cond_val++;
                                                }
                                                overlap(overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind]), population, num_of_pop[num_of_pop_ind], pot, elitist);
                                                //cout<<"\n!!!The new generation is:"<<endl;
                                                double ret=100000;
                                                for(int i=0; i<num_of_pop[num_of_pop_ind]; i++){
                                                    //population[i].show_gen();
                                                    if(population[i].get_dist()<=ret){
                                                        ret=population[i].get_dist();
                                                        best_ind=i;
                                                    }
                                                }
                                                if(solution.get_dist()>population[best_ind].get_dist()){
                                                    solution=*new progeny(population[best_ind]);
                                                }
                                                if(stop_cond(stop_cond_meth, max_stop_cond_val[step_max_ind], &cur_stop_cond_val, &prev_stop_cond_val, population, num_of_pop[num_of_pop_ind])){
                                                    break;
                                                }

                                            }
                                            Finished1:
                                            cout<<"-----The end best solution is:"<<endl;
                                            solution.show_gen();
                                            num_of_iterations=1;
                                            cur_stop_cond_val=0;
                                            delete[] pot;
                                            delete[] ch;
                                            delete[] population;
                                            cout<<iteration_overall<<endl;
                                        }
                                    }
                                }
                            }
                            else{
                                for(int step_max_ind=0; step_max_ind<3; step_max_ind++){
                                    for(int procr_choice_ind=0; procr_choice_ind<3; procr_choice_ind++){
                                        cout<<"CR-"<<cross_ind<<", PN-"<<num_of_pop[num_of_pop_ind]<<", G-"<<overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind])<<", MT-"<<mut_ind[ind_of_mut]<<", PP-"<<procreator_pairs_num[procr_pairs_ind]<<", SM-"<<selec_method[selec_meth_ind]<<", MAX_STEP"<<max_stop_cond_val[step_max_ind]<<", PC-"<<procr_choice[procr_choice_ind]<<endl;
                                        iteration_overall++;
                                        progeny *ch=new progeny[procreator_pairs_num[procr_pairs_ind]*2];
                                        progeny *population=new progeny[num_of_pop[num_of_pop_ind]];
                                        progeny *pot=new progeny[overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind])];
                                        emergency_stop=false;
                                        //cout<<"\n\n-----The 0 generation-----"<<endl;
                                        for(int i=0; i<num_of_pop[num_of_pop_ind]; i++){
                                            /*if(proc_of_gen){
                                                cout<<"\n\n-----"<<i+1<<"-species-----"<<endl;
                                            }*/
                                            population[i]=*new progeny(0, 15, NULL, true, false, true, init_pop_meth, R, proc_of_gen);
                                            for(int j=0; j<i; j++){
                                                if(population[j]==population[i]){
                                                    /*if(proc_of_gen){
                                                        cout<<"\n!!!However, there is this gen already. Retrying..."<<endl;
                                                    }*/
                                                    i--;
                                                    continue;
                                                }
                                            }
                                        }
                                        /*switch(stop_cond_meth){
                                            case 2:{
                                                prev_stop_cond_val=min_dist(population, num_of_pop);
                                                break;
                                            }
                                            case 3:{
                                                prev_stop_cond_val=av_dist(population, num_of_pop);
                                                break;
                                            }
                                        }*/
                                        double ret=100000;
                                        for(int i=0; i<num_of_pop[num_of_pop_ind]; i++){
                                            //population[i].show_gen();
                                            if(population[i].get_dist()<=ret){
                                                ret=population[i].get_dist();
                                                global_ind=i;
                                            }
                                        }
                                        progeny par_per_it[2], ch_per_it[2], solution=*new progeny(population[global_ind]);
                                        cout<<"\nThe initial global solution is:"<<endl;
                                        solution.show_gen();
                                        while(true){
                                            //cout<<"\n\n-----The "<<num_of_iterations<<" generation-----"<<endl;
                                            num_of_iterations++;
                                            int j=0;
                                            for(int i=0; i<procreator_pairs_num[procr_pairs_ind]; i++){
                                                procreator_choice_process(procr_choice[procr_choice_ind], population, num_of_pop[num_of_pop_ind], 15, par_per_it, R, &emergency_stop);
                                                if(emergency_stop){
                                                    goto Finished2;
                                                }
                                                crossover(par_per_it, ch_per_it, 15, R, crossover_ind[cross_ind]);
                                                ch[j]=*new progeny(ch_per_it[0]);
                                                ch[j+1]=*new  progeny(ch_per_it[1]);
                                                j+=2;
                                            }
                                            /*cout<<"\n\nCreated children:"<<endl;
                                            for(int i=0; i<procreator_pairs_num[procr_pairs_ind]*2; i++){
                                                ch[i].show_gen();
                                            }*/
                                            for(int i=0; i<procreator_pairs_num[procr_pairs_ind]*2; i++){
                                                mut_rand=rand()%101;
                                                if(mut_rand<=mut_procent){
                                                    //cout<<"Mutation occured!!!"<<endl;
                                                    //ch[i].show_gen();
                                                    chosen_mut(mut_ind[ind_of_mut], ch[i], 15, R);
                                                    //cout<<"Changed to..."<<endl;
                                                    //ch[i].show_gen();
                                                }
                                            }
                                            roulete(overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind]), ch, procreator_pairs_num[procr_pairs_ind]*2, pot);
                                            if(stop_cond_meth==1){
                                                cur_stop_cond_val++;
                                            }
                                            overlap(overlap_num(G_coef[G_coef_ind], num_of_pop[num_of_pop_ind]), population, num_of_pop[num_of_pop_ind], pot, elitist);
                                            //cout<<"\n!!!The new generation is:"<<endl;
                                            double ret=100000;
                                            for(int i=0; i<num_of_pop[num_of_pop_ind]; i++){
                                                //population[i].show_gen();
                                                if(population[i].get_dist()<=ret){
                                                    ret=population[i].get_dist();
                                                    best_ind=i;
                                                }
                                            }
                                            if(solution.get_dist()>population[best_ind].get_dist()){
                                                solution=*new progeny(population[best_ind]);
                                            }
                                            if(stop_cond(stop_cond_meth, max_stop_cond_val[step_max_ind], &cur_stop_cond_val, &prev_stop_cond_val, population, num_of_pop[num_of_pop_ind])){
                                                break;
                                            }

                                        }
                                        Finished2:
                                        cout<<"-----The end best solution is:"<<endl;
                                        solution.show_gen();
                                        num_of_iterations=1;
                                        cur_stop_cond_val=0;
                                        delete[] pot;
                                        delete[] ch;
                                        delete[] population;
                                        cout<<iteration_overall<<endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    delete[] R;
    return 0;
}
//
// Created by augustinmay on 24.11.19.
//

#include "mutation.h"

void dot_mut(progeny &pr, int size, double **R){
    int tmp=rand()%(size-1), tmp_ind;
    cout<<pr[tmp]+1<<" and "<<pr[tmp+1]+1<<endl;
    tmp_ind=pr[tmp];
    pr[tmp]=pr[tmp+1];
    pr[tmp+1]=tmp_ind;
    pr.dist_cnt(R);
}

void saltation(progeny &pr, int size, double **R){
    int tmp1=rand()%size, tmp2=rand()%size, tmp_ind;
    while(tmp1==tmp2){
        tmp2=rand()%size;
    }
    cout<<pr[tmp1]+1<<" and "<<pr[tmp2]+1<<endl;
    tmp_ind=pr[tmp1];
    pr[tmp1]=pr[tmp2];
    pr[tmp2]=tmp_ind;
    pr.dist_cnt(R);
}
void inversion(progeny &pr, int size, double **R){
    int tmp1=rand()%size, tmp2=rand()%size, *tmp_ar, cnt;
    while(tmp1==tmp2){
        tmp2=rand()%size;
    }
    cout<<pr[tmp1]+1<<" and "<<pr[tmp2]+1<<endl;
    tmp_ar=new int[(abs(tmp1-tmp2))+1];
    if(tmp2>tmp1){
        cnt=tmp2;
        for(int i=0; i<((abs(tmp1-tmp2))+1); i++){
            tmp_ar[i]=pr[cnt];
            cnt--;
        }
        cnt=0;
        for(int i=tmp1; i<=tmp2; i++){
            pr[i]=tmp_ar[cnt];
            cnt++;
        }
    }
    else if(tmp1>tmp2){
        cnt=tmp1;
        for(int i=0; i<(abs(tmp1-tmp2)+1); i++){
            tmp_ar[i]=pr[cnt];
            cnt--;
        }
        cnt=0;
        for(int i=tmp2; i<=tmp1; i++){
            pr[i]=tmp_ar[cnt];
            cnt++;
        }
    }
    pr.dist_cnt(R);
}

void translocation(progeny &pr, int size, double **R){
    int tmp1=rand()%size, tmp2=rand()%size, *tmp_ar1, *tmp_ar2, cnt1, cnt2;
    while(tmp1==tmp2){
        tmp2=rand()%size;
    }
    cout<<pr[tmp1]+1<<" and "<<pr[tmp2]+1<<endl;
    if(tmp2>tmp1){
        cnt1=tmp1;
        cnt2=size-1;
        tmp_ar1=new int[tmp1+1];
        tmp_ar2=new int[(size-tmp2)];
        for(int i=0; i<tmp1+1; i++){
            tmp_ar1[i]=pr[cnt1];
            cnt1--;
        }
        for(int i=0; i<tmp1+1; i++){
            pr[i]=tmp_ar1[i];
        }
        for(int i=0; i<(size-tmp2); i++){
            tmp_ar2[i]=pr[cnt2];
            cnt2--;
        }
        cnt2=0;
        for(int i=tmp2; i<size; i++){
            pr[i]=tmp_ar2[cnt2];
            cnt2++;
        }
    }
    else if(tmp1>tmp2){
        cnt1=tmp2;
        cnt2=size-1;
        tmp_ar1=new int[tmp2+1];
        tmp_ar2=new int[(size-tmp1)];
        for(int i=0; i<tmp2+1; i++){
            tmp_ar1[i]=pr[cnt1];
            cnt1--;
        }
        for(int i=0; i<tmp2+1; i++){
            pr[i]=tmp_ar1[i];
        }
        for(int i=0; i<(size-tmp1); i++){
            tmp_ar2[i]=pr[cnt2];
            cnt2--;
        }
        cnt2=0;
        for(int i=tmp1; i<size; i++){
            pr[i]=tmp_ar2[cnt2];
            cnt2++;
        }
    }
    pr.dist_cnt(R);
}
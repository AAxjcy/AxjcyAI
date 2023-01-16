#include<bits/stdc++.h>

#ifndef _UNIVERSAL_HPP_
#define _UNIVERSAL_HPP_

#define MAIN_FIRST_NUMBER 3000
#define MAIN_SECOND_NUMBER 4000
#define MAIN_THIRD_NUMBER 3000

#define AAI_FLAGS_INIT 0
#define AAI_FLAGS_COMPUTE 1
#define AAI_FLAGS_FINISH 2

#define AAI_STATUS_SUCCESS 0
#define AAI_STATUS_REPEAT_INIT 1
#define AAI_STATUS_FULL_QUEUE 2
#define AAI_STATUS_NULL_QUEUE 3

#define MAX_TIME 100

typedef class AAI_QUEUE{
public:
    AAI_QUEUE():top(0),bottom(0),empty(1){num_queue=new double[MAX_TIME];}
    ~AAI_QUEUE(){delete[] num_queue;}
    char is_empty(){return empty;}
    int time_length(){return empty?0:(bottom+MAX_TIME-top+1)%MAX_TIME;}
    int push(double x){
        if(empty){empty=0;num_queue[bottom]=x;}
        else if((bottom+1)%MAX_TIME!=top)num_queue[(++bottom)%=MAX_TIME]=x;
        else return AAI_STATUS_FULL_QUEUE;
        return AAI_STATUS_SUCCESS;
    }
    double pop(int &status){
        if(empty){status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(top==bottom)return num_queue[top]*(empty=1)+(status=AAI_STATUS_SUCCESS);
        return num_queue[(++top)%=MAX_TIME]+(status=AAI_STATUS_SUCCESS);
    }
    double shorter(double t,int &status){
        if(empty){status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(t<0)return -longer(-t,status);
        int need=t;need=min(need,time_length()-1);
        double sum=0;
        for(int i=0;i<need;i++)sum+=pop(status);
        push_top(sum);
        return t-need+(status=AAI_STATUS_SUCCESS);
    }
    double longer(double t,int &status){
        if(empty){status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(t<0)return -shorter(-t,status);
        int need=t;need=min(need,MAX_TIME-time_length()-1);
        for(int i=0;i<need;i++)push_top(0);
        return t-need+(status=AAI_STATUS_SUCCESS);
    }
private:
    double *num_queue;
    int top,bottom;
    char empty;
    int min(int x,int y){return x<y?x:y;}
    void push_top(double x){num_queue[((--top)+=MAX_TIME)%=MAX_TIME]=x;}
}aai_queue;

#endif
#include<bits/stdc++.h>

#ifndef _UNIVERSAL_HPP_
#define _UNIVERSAL_HPP_


#ifdef DLL_EXPORTS
    #define AAI_DLL_EXPORT __declspec(dllexport)
#else
    #define AAI_DLL_EXPORT __declspec(dllimport)
#endif

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
#define AAI_STATUS_NO_MODULE 4
#define AAI_STATUS_NO_DLL 5
#define AAI_STATUS_NO_FUNCTION 6

#define MAX_TIME 100
#define MAX_LENGTH 200

typedef class AAI_QUEUE{
public:
    AAI_QUEUE():top(0),bottom(0),empty(1){num_queue=new double[MAX_LENGTH];}
    ~AAI_QUEUE(){delete[] num_queue;}
    char is_empty(){return empty;}
    int time_length(){return empty?0:(bottom+MAX_LENGTH-top)%MAX_LENGTH+1;}
    int push(double x){
        if(empty){empty=0;num_queue[bottom]=x;}
        else if((bottom+1)%MAX_LENGTH!=top)num_queue[(++bottom)%=MAX_LENGTH]=x;
        else return AAI_STATUS_FULL_QUEUE;
        return AAI_STATUS_SUCCESS;
    }
    double pop(int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(status)*status=AAI_STATUS_SUCCESS;
        if(top==bottom)return num_queue[top]*(empty=1);
        return num_queue[(++top)%=MAX_LENGTH];
    }
    double shorter(double t,int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(t<0)return -longer(-t,status);
        int need=t/100;need=min(need,time_length()-1);
        double sum=0;
        for(int i=0;i<need;i++)sum+=pop(status);
        push_top(sum);if(status)*status=AAI_STATUS_SUCCESS;
        return t-need*100;
    }
    double longer(double t,int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(t<0)return -shorter(-t,status);
        int need=t/100;need=min(need,MAX_TIME-time_length()-1);
        for(int i=0;i<need;i++)push_top(0);
        if(status)*status=AAI_STATUS_SUCCESS;
        return t-need*100;
    }
private:
    double *num_queue;
    int top,bottom;
    char empty;
    int min(int x,int y){return x<y?x:y;}
    void push_top(double x){num_queue[((--top)+=MAX_LENGTH)%=MAX_LENGTH]=x;}
}aai_queue;

#endif
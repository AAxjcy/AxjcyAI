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
#define AAI_FLAGS_PUNISH 3
#define AAI_FLAGS_REWARD 4

#define AAI_STATUS_SUCCESS 0
#define AAI_STATUS_REPEAT_INIT 1
#define AAI_STATUS_FULL_QUEUE 2
#define AAI_STATUS_NULL_QUEUE 3
#define AAI_STATUS_NO_MODULE 4
#define AAI_STATUS_NO_DLL 5
#define AAI_STATUS_NO_FUNCTION 6
#define AAI_STATUS_ADJUST_FAILED 7

#define AAI_COMPUTE_NONE 0
#define AAI_COMPUTE_FIRST 1
#define AAI_COMPUTE_SECOND 2
#define AAI_COMPUTE_THIRD 3

#define MAX_TIME 100
#define MAX_INIT_WEIGHT 10
#define MAX_LENGTH 200
#define SCALING_RATIO 100

typedef class AAI_QUEUE{
public:
    AAI_QUEUE():top(0),bottom(0),empty(1),sum_value(0){num_queue=new double[MAX_LENGTH];}
    ~AAI_QUEUE(){delete[] num_queue;}
    char is_empty(){return empty;}
    int time_length(){return empty?0:(bottom+MAX_LENGTH-top)%MAX_LENGTH+1;}
    void print(){
        if(empty){puts("NONE");return;}
        for(int p=top;p!=bottom;p++)std::cout<<num_queue[p]<<' ';
        std::cout<<num_queue[bottom]<<' ';
        std::cout<<std::endl;
    }
    int push(double x){
        if(empty){empty=0;num_queue[bottom]=x;}
        else if((bottom+1)%MAX_LENGTH!=top)num_queue[(++bottom)%=MAX_LENGTH]=x;
        else return AAI_STATUS_FULL_QUEUE;
        sum_value+=x;
        return AAI_STATUS_SUCCESS;
    }
    double pop(int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(status)*status=AAI_STATUS_SUCCESS;
        double ans=num_queue[top];
        (top==bottom)?empty=1:((++top)%=MAX_LENGTH);
        return ans;
    }
    int shorter(){
        if(empty)return AAI_STATUS_NULL_QUEUE;
        sum_value=queue_short(sum_value);
        return AAI_STATUS_SUCCESS;
    }
    int longer(){
        if(empty)return AAI_STATUS_NULL_QUEUE;
        sum_value=queue_long(sum_value);
        return AAI_STATUS_SUCCESS;
    }
private:
    double *num_queue,sum_value;
    int top,bottom;
    char empty;
    int min(int x,int y){return x<y?x:y;}
    void push_top(double x){num_queue[((--top)+=MAX_LENGTH)%=MAX_LENGTH]=x;}
    double queue_short(double t){
        if(t<0)return -queue_long(-t);
        int need=t/SCALING_RATIO;need=min(need,time_length()-1);
        double sum=0;
        for(int i=0;i<need;i++)sum+=pop(NULL);
        push_top(sum);
        return t-need*SCALING_RATIO;
    }
    double queue_long(double t){
        if(t<0)return -queue_short(-t);
        int need=t/SCALING_RATIO;need=min(need,MAX_TIME-time_length()-1);
        for(int i=0;i<need;i++)push_top(0);
        return t-need*SCALING_RATIO;
    }
}aai_queue;

double sigma(double x){return 1/(1+exp(-x));}

#endif
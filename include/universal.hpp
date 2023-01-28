#include<bits/stdc++.h>

#ifndef _UNIVERSAL_HPP_
#define _UNIVERSAL_HPP_


#ifdef DLL_EXPORTS
    #define AAI_DLL_EXPORT __declspec(dllexport)
#else
    #define AAI_DLL_EXPORT __declspec(dllimport)
#endif

#define MAIN_FIRST_NUMBER 2000
#define MAIN_SECOND_NUMBER 3000
#define MAIN_THIRD_NUMBER 2000

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
#define DECAY_RATE 0.02

const double eps=1e-6;
const double pow_p=log(1-DECAY_RATE);
const double pow_r=log(1+DECAY_RATE);

// double *decay_pow;

typedef class AAI_QUEUE{
public:
    static void init(){
        // decay_pow=new double[MAX_TIME];
        decay_pow[0]=1;
        for(int t=1;t<MAX_TIME;t++)decay_pow[t]=decay_pow[t-1]*(1-DECAY_RATE);
    }
    static void finish(){delete[] decay_pow;}
    static void pp(){for(int t=0;t<MAX_TIME;t++)std::cout<<decay_pow[t]<<' ';std::cout<<std::endl;}
    AAI_QUEUE():top(0),bottom(0),empty(1),sum_value(0){
        num_queue=new double[MAX_LENGTH];
        memset(num_queue,0,sizeof(double)*MAX_LENGTH);
    }
    ~AAI_QUEUE(){delete[] num_queue;}
    char is_empty(){return empty;}
    int time_length(){return empty?0:(bottom+MAX_LENGTH-top)%MAX_LENGTH+1;}
    void print(){
        if(empty){puts("NONE");return;}
        std::cout<<time_length()<<':';
        for(int p=top;p!=bottom;p++)std::cout<<num_queue[p]<<' ';
        std::cout<<num_queue[bottom]<<'|'<<sum_value<<std::endl;
        // for(int p=top;p!=bottom;(++p)%=MAX_LENGTH)std::cout<<p<<' '<<num_queue[p]<<std::endl;
        // std::cout<<num_queue[bottom]<<'|'<<sum_value<<std::endl;
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
        double ans=decay_pow[time_length()-1];
        // double ans=1;
        // std::cout<<"<<<<<<<<<<<<<<<<<<<<<"<<std::endl;
        return ans*pop_queue();
    }
    double pop_no_decay(int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(status)*status=AAI_STATUS_SUCCESS;
        return pop_queue();
    }
    double get_sum(int *status){return sum_value;}
    int set_sum(double x){sum_value=x;return AAI_STATUS_SUCCESS;}
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
    double value_now(int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(status)*status=AAI_STATUS_SUCCESS;
        return num_queue[bottom];
    }
    double value_top(int *status){
        if(empty){if(status)*status=AAI_STATUS_NULL_QUEUE;return 0;}
        if(status)*status=AAI_STATUS_SUCCESS;
        // std::cout<<top<<' '<<num_queue[top]<<' '<<decay_pow[time_length()-1]<<std::endl;
        return num_queue[top]*decay_pow[time_length()-1];
        // return num_queue[top];
    }
private:
    double *num_queue,sum_value;
    int top,bottom;
    static double *decay_pow;
    // static double decay_pow[MAX_TIME];
    char empty;
    // int min(int x,int y){return x<y?x:y;}
    void push_top(double x){if(empty){empty=0;num_queue[top]=x;}
        else num_queue[((--top)+=MAX_LENGTH)%=MAX_LENGTH]=x;
    }
    double pop_queue(){
        double ans=num_queue[top];
        (top==bottom)?empty=1:((++top)%=MAX_LENGTH);
        return ans;
    }
    double queue_short(double t){
        if(t<0)return -queue_long(-t);
        int need=t/SCALING_RATIO;need=std::min(need,time_length());
        if(need){
            double sum=0,x;
            for(int i=0;i<need;i++){x=pop_queue();sum+=x;}
            push_top(sum/need);
        }
        return t-need*SCALING_RATIO;
    }
    double queue_long(double t){
        if(t<0)return -queue_short(-t);
        int need=t/SCALING_RATIO;need=std::min(need,MAX_TIME-time_length());
        for(int i=0;i<need;i++)push_top(0);
        return t-need*SCALING_RATIO;
    }
}aai_queue;

double * aai_queue::decay_pow=new double[MAX_TIME];

typedef int (*func_point)(const int flags,aai_queue *X1,aai_queue *X2,aai_queue *X3,
    double *Y,int *which,const void *modules_func,const int num_modules);

double sigma(double x){return 1/(1+exp(-x));}
double power(double x,int flags){return exp(x*((flags==AAI_FLAGS_PUNISH)?pow_p:pow_r));}

#endif
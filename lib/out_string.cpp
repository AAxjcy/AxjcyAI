#define DLL_EXPORTS

#include<bits/stdc++.h>
#include"include/universal.hpp"

#define OUTPUT_NUMBER 1
#define FIRST_NUMBER 2000
#define SECOND_NUMBER 2000
#define THIRD_NUMBER 100

using namespace std;

int string_output(wchar_t output_char){
    return AAI_STATUS_SUCCESS;
}

extern "C"{
AAI_DLL_EXPORT int out_string(const int flags,aai_queue *main1,aai_queue *main2,aai_queue *main3,
        double *Y,int *which,const void *modules_func,const int num_modules){
    srand(time(0));static int status_init=0;
    static aai_queue *first_data=new aai_queue[FIRST_NUMBER];
    static aai_queue *second_data=new aai_queue[SECOND_NUMBER];
    static aai_queue *third_data=new aai_queue[THIRD_NUMBER];
    static double **from_main,**first_to_first,**first_to_second,
        **second_to_second,**second_to_third,**third_to_third,**third_to_output;
    int status=AAI_STATUS_SUCCESS;
    switch(flags){
        case AAI_FLAGS_INIT:{
            if(status_init)return AAI_STATUS_REPEAT_INIT;
            aai_queue::init();
            status_init=1;
            FILE* f_in=fopen("module/out_string/from_main.aad","r");
            int n=FIRST_NUMBER,m=MAIN_THIRD_NUMBER;
            from_main=new double *[n];
            for(int i=0;i<n;i++)from_main[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                from_main[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&from_main[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/first_to_first.aad","r");
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            first_to_first=new double *[n];
            for(int i=0;i<n;i++)first_to_first[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                first_to_first[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&first_to_first[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/first_to_second.aad","r");
            n=SECOND_NUMBER,m=FIRST_NUMBER;
            first_to_second=new double *[n];
            for(int i=0;i<n;i++)first_to_second[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                first_to_second[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&first_to_second[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/second_to_second.aad","r");
            n=SECOND_NUMBER,m=SECOND_NUMBER;
            second_to_second=new double *[n];
            for(int i=0;i<n;i++)second_to_second[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                second_to_second[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&second_to_second[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/second_to_third.aad","r");
            n=THIRD_NUMBER,m=SECOND_NUMBER;
            second_to_third=new double *[n];
            for(int i=0;i<n;i++)second_to_third[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                second_to_third[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&second_to_third[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/third_to_third.aad","r");
            n=THIRD_NUMBER,m=THIRD_NUMBER;
            third_to_third=new double *[n];
            for(int i=0;i<n;i++)third_to_third[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                third_to_third[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&third_to_third[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/third_to_output.aad","r");
            n=OUTPUT_NUMBER,m=THIRD_NUMBER;
            third_to_output=new double *[n];
            for(int i=0;i<n;i++)third_to_output[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                third_to_output[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&third_to_output[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/out_string/first_data.aad","r");
            n=FIRST_NUMBER;
            int tim;double value;
            if(!f_in)for(int i=0;i<n;i++){
                tim=rand()%MAX_TIME+1;
                for(int j=0;j<tim;j++)first_data[i].push(0);
            }else{
                for(int i=0;i<n;i++){
                    fscanf(f_in,"%d",&tim);
                    for(int j=0;j<tim;j++){
                        fscanf(f_in,"%lf",&value);
                        first_data[i].push(value);
                    }
                    fscanf(f_in,"%lf",&value);
                    first_data[i].set_sum(value);
                }
                fclose(f_in);
            }
            f_in=fopen("module/out_string/second_data.aad","r");
            n=SECOND_NUMBER;
            if(!f_in)for(int i=0;i<n;i++){
                tim=rand()%MAX_TIME+1;
                for(int j=0;j<tim;j++)second_data[i].push(0);
            }else{
                for(int i=0;i<n;i++){
                    fscanf(f_in,"%d",&tim);
                    for(int j=0;j<tim;j++){
                        fscanf(f_in,"%lf",&value);
                        second_data[i].push(value);
                    }
                    fscanf(f_in,"%lf",&value);
                    second_data[i].set_sum(value);
                }
                fclose(f_in);
            }
            f_in=fopen("module/out_string/third_data.aad","r");
            n=THIRD_NUMBER;
            if(!f_in)for(int i=0;i<n;i++){
                tim=rand()%MAX_TIME+1;
                for(int j=0;j<tim;j++)third_data[i].push(0);
            }else{
                for(int i=0;i<n;i++){
                    fscanf(f_in,"%d",&tim);
                    for(int j=0;j<tim;j++){
                        fscanf(f_in,"%lf",&value);
                        third_data[i].push(value);
                    }
                    fscanf(f_in,"%lf",&value);
                    third_data[i].set_sum(value);
                }
                fclose(f_in);
            }
            break;
        }
        case AAI_FLAGS_COMPUTE:{
            *which=AAI_COMPUTE_NONE;
            double output_data=0;
            double *first_X=new double [FIRST_NUMBER],*first_Y=new double [FIRST_NUMBER];
            double *second_X=new double [SECOND_NUMBER],*second_Y=new double [SECOND_NUMBER];
            double *third_X=new double [THIRD_NUMBER],*third_Y=new double [THIRD_NUMBER];
            for(int i=0;i<FIRST_NUMBER;i++)first_X[i]=first_data[i].pop(NULL)+(first_Y[i]=0);
            for(int i=0;i<SECOND_NUMBER;i++)second_X[i]=second_data[i].pop(NULL)+(second_Y[i]=0);
            for(int i=0;i<THIRD_NUMBER;i++)third_X[i]=third_data[i].pop(NULL)+(third_Y[i]=0);
            int n=FIRST_NUMBER,m=MAIN_THIRD_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=from_main[i][j]*main3[j].value_top(NULL);
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=first_to_first[i][j]*first_X[j];
            for(int i=0;i<n;i++)first_data[i].push(sigma(first_Y[i]));
            n=SECOND_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)second_Y[i]+=first_to_second[i][j]*first_X[j];
            n=SECOND_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)second_Y[i]+=second_to_second[i][j]*second_X[j];
            for(int i=0;i<n;i++)second_data[i].push(sigma(second_Y[i]));
            n=THIRD_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)third_Y[i]+=second_to_third[i][j]*second_X[j];
            n=THIRD_NUMBER,m=THIRD_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)third_Y[i]+=third_to_third[i][j]*third_X[j];
            for(int i=0;i<n;i++)third_data[i].push(sigma(third_Y[i]));
            n=OUTPUT_NUMBER,m=THIRD_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)output_data+=third_to_output[i][j]*third_X[j];
            delete[] first_X;delete[] second_X;delete[] third_X;
            delete[] first_Y;delete[] second_Y;delete[] third_Y;
            wchar_t output_char=sigma(output_data)*WCHAR_MAX;
            status=string_output(output_char);
            break;
        }
        case AAI_FLAGS_FINISH:{
            aai_queue::finish();
            FILE* f_out=fopen("module/out_string/from_main.aad","w");
            int n=FIRST_NUMBER,m=MAIN_THIRD_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",from_main[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/first_to_first.aad","w");
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",first_to_first[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/first_to_second.aad","w");
            n=SECOND_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",first_to_second[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/second_to_second.aad","w");
            n=SECOND_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",second_to_second[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/second_to_third.aad","w");
            n=THIRD_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",second_to_third[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/third_to_third.aad","w");
            n=THIRD_NUMBER,m=THIRD_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",third_to_third[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/third_to_output.aad","w");
            n=OUTPUT_NUMBER,m=THIRD_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",third_to_output[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/out_string/first_data.aad","w");
            n=FIRST_NUMBER;
            int tim;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=first_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",first_data[i].pop_no_decay(NULL));
                fprintf(f_out,"%lf\n",first_data[i].get_sum(NULL));
            }
            fclose(f_out);
            f_out=fopen("module/out_string/second_data.aad","w");
            n=SECOND_NUMBER;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=second_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",second_data[i].pop_no_decay(NULL));
                fprintf(f_out,"%lf\n",second_data[i].get_sum(NULL));
            }
            fclose(f_out);
            f_out=fopen("module/out_string/third_data.aad","w");
            n=THIRD_NUMBER;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=third_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",third_data[i].pop_no_decay(NULL));
                fprintf(f_out,"%lf\n",third_data[i].get_sum(NULL));
            }
            fclose(f_out);
            delete[] first_data;
            delete[] second_data;
            delete[] third_data;
            for(int i=0;i<MAIN_FIRST_NUMBER;i++)delete[] from_main[i];delete[] from_main;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] third_to_output[i];delete[] third_to_output;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] first_to_first[i];delete[] first_to_first;
            for(int i=0;i<SECOND_NUMBER;i++)delete[] first_to_second[i];delete[] first_to_second;
            for(int i=0;i<SECOND_NUMBER;i++)delete[] second_to_second[i];delete[] second_to_second;
            for(int i=0;i<THIRD_NUMBER;i++)delete[] second_to_third[i];delete[] second_to_third;
            for(int i=0;i<THIRD_NUMBER;i++)delete[] third_to_third[i];delete[] third_to_third;
            break;
        }
        case AAI_FLAGS_PUNISH:{
            int n=FIRST_NUMBER,m=MAIN_THIRD_NUMBER;double x;
            for(int j=0;j<m;j++){
                x=power(main3[j].value_now(NULL),AAI_FLAGS_PUNISH);
                for(int i=0;i<n;i++)from_main[i][j]*=x;
            }
            m=FIRST_NUMBER;
            for(int j=0;j<m;j++){
                x=power(first_data[j].value_now(NULL),AAI_FLAGS_PUNISH);
                n=FIRST_NUMBER;
                for(int i=0;i<n;i++)first_to_first[i][j]*=x;
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)first_to_second[i][j]*=x;
            }
            m=SECOND_NUMBER;
            for(int j=0;j<m;j++){
                x=power(second_data[j].value_now(NULL),AAI_FLAGS_PUNISH);
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)second_to_second[i][j]*=x;
                n=THIRD_NUMBER;
                for(int i=0;i<n;i++)second_to_third[i][j]*=x;
            }
            m=THIRD_NUMBER;
            for(int j=0;j<m;j++){
                x=power(third_data[j].value_now(NULL),AAI_FLAGS_PUNISH);
                n=THIRD_NUMBER;
                for(int i=0;i<n;i++)third_to_third[i][j]*=x;
                n=OUTPUT_NUMBER;
                for(int i=0;i<n;i++)third_to_output[i][j]*=x;
            }
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++)first_data[i].shorter();
            n=SECOND_NUMBER;
            for(int i=0;i<n;i++)second_data[i].shorter();
            n=THIRD_NUMBER;
            for(int i=0;i<n;i++)third_data[i].shorter();
            break;
        }
        case AAI_FLAGS_REWARD:{
            int n=FIRST_NUMBER,m=MAIN_THIRD_NUMBER;double x;
            for(int j=0;j<m;j++){
                x=power(main3[j].value_now(NULL),AAI_FLAGS_REWARD);
                for(int i=0;i<n;i++)from_main[i][j]*=x;
            }
            m=FIRST_NUMBER;
            for(int j=0;j<m;j++){
                x=power(first_data[j].value_now(NULL),AAI_FLAGS_REWARD);
                n=FIRST_NUMBER;
                for(int i=0;i<n;i++)first_to_first[i][j]*=x;
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)first_to_second[i][j]*=x;
            }
            m=SECOND_NUMBER;
            for(int j=0;j<m;j++){
                x=power(second_data[j].value_now(NULL),AAI_FLAGS_REWARD);
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)second_to_second[i][j]*=x;
                n=THIRD_NUMBER;
                for(int i=0;i<n;i++)second_to_third[i][j]*=x;
            }
            m=THIRD_NUMBER;
            for(int j=0;j<m;j++){
                x=power(third_data[j].value_now(NULL),AAI_FLAGS_REWARD);
                n=THIRD_NUMBER;
                for(int i=0;i<n;i++)third_to_third[i][j]*=x;
                n=OUTPUT_NUMBER;
                for(int i=0;i<n;i++)third_to_output[i][j]*=x;
            }
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++)first_data[i].longer();
            n=SECOND_NUMBER;
            for(int i=0;i<n;i++)second_data[i].longer();
            n=THIRD_NUMBER;
            for(int i=0;i<n;i++)third_data[i].longer();
            break;
        }
    }
    return status;
}
}
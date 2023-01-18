#define DLL_EXPORTS

#include<bits/stdc++.h>
#include"include/universal.hpp"

#define FIRST_NUMBER 100
#define OUTPUT_NUMBER 1

using namespace std;

int auto_adjust(double x){return AAI_STATUS_SUCCESS;}

extern "C"{
AAI_DLL_EXPORT int auto_command(int flags,double *X1,double *X2,double *X3,double *Y,int *which){
    srand(time(0));static int status_init=0;
    static aai_queue *first_data=new aai_queue[FIRST_NUMBER];
    static aai_queue *output_data=new aai_queue[OUTPUT_NUMBER];
    static double **from_main,**first_to_output,**first_to_first;
    int status=AAI_STATUS_SUCCESS;
    switch(flags){
        case AAI_FLAGS_INIT:{
            if(status_init)return AAI_STATUS_REPEAT_INIT;
            status_init=1;
            FILE* f_in=fopen("module/auto_command/from_main.aad","r");
            int n=FIRST_NUMBER,m=FIRST_NUMBER;
            from_main=new double *[n];
            for(int i=0;i<n;i++)from_main[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                from_main[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&from_main[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/auto_command/first_to_first.aad","r");
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            first_to_first=new double *[n];
            for(int i=0;i<n;i++)first_to_first[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                first_to_first[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&first_to_first[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/auto_command/first_to_output.aad","r");
            n=OUTPUT_NUMBER,m=FIRST_NUMBER;
            first_to_output=new double *[n];
            for(int i=0;i<n;i++)first_to_output[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                first_to_output[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&first_to_output[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/auto_command/first_data.aad","r");
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
                }
                fclose(f_in);
            }
            f_in=fopen("module/auto_command/output_data.aad","r");
            n=OUTPUT_NUMBER;
            if(!f_in)for(int i=0;i<n;i++){
                tim=rand()%MAX_TIME+1;
                for(int j=0;j<tim;j++)output_data[i].push(0);
            }else{
                for(int i=0;i<n;i++){
                    fscanf(f_in,"%d",&tim);
                    for(int j=0;j<tim;j++){
                        fscanf(f_in,"%lf",&value);
                        output_data[i].push(value);
                    }
                }
                fclose(f_in);
            }
            break;
        }
        case AAI_FLAGS_COMPUTE:{
            *which=AAI_COMPUTE_NONE;
            int n=FIRST_NUMBER,m=FIRST_NUMBER;
            double *first_X=new double [n],*first_Y=new double [n];
            for(int i=0;i<n;i++)first_X[i]=first_data[i].pop(NULL)+(first_Y[i]=0);
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=from_main[i][j]*X2[j];
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=first_to_first[i][j]*first_X[j];
            for(int i=0;i<n;i++)first_data[i].push(sigma(first_Y[i]));
            n=OUTPUT_NUMBER,m=FIRST_NUMBER;
            double *output_X=new double [n],*output_Y=new double [n];
            for(int i=0;i<n;i++)output_X[i]=output_data[i].pop(NULL)+(output_Y[i]=0);
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)output_Y[i]+=first_to_output[i][j]*first_X[j];
            status=auto_adjust(output_X[0]);
            for(int i=0;i<n;i++)output_data[i].push(sigma(output_Y[i]));
            delete[] first_X;delete[] output_X;
            delete[] first_Y;delete[] output_Y;
            break;
        }
        case AAI_FLAGS_FINISH:{
            FILE* f_out=fopen("module/auto_command/from_main.aad","w");
            int n=FIRST_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",from_main[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/auto_command/first_to_first.aad","w");
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",first_to_first[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/auto_command/first_to_output.aad","w");
            n=OUTPUT_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",first_to_output[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/auto_command/first_data.aad","w");
            n=FIRST_NUMBER;
            int tim;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=first_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",first_data[i].pop(NULL));
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/auto_command/output_data.aad","w");
            n=OUTPUT_NUMBER;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=output_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",output_data[i].pop(NULL));
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            delete[] first_data;
            delete[] output_data;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] from_main[i];
            delete[] from_main;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] first_to_first[i];
            delete[] first_to_first;
            for(int i=0;i<OUTPUT_NUMBER;i++)delete[] first_to_output[i];
            delete[] first_to_output;
            break;
        }
        case AAI_FLAGS_PUNISH:{
            break;
        }
        case AAI_FLAGS_REWARD:{
            break;
        }
    }
    return status;
}
}
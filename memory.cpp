#define DLL_EXPORTS

#include<bits/stdc++.h>
#include"include/universal.hpp"

#define FIRST_NUMBER 3000
#define SECOND_NUMBER 3000
#define SHORT_LENGTH 128
#define LONG_LENGTH 131072

using namespace std;

typedef bitset<SHORT_LENGTH> short_type;

extern "C"{
AAI_DLL_EXPORT int memory(const int flags,aai_queue *main1,aai_queue *main2,aai_queue *main3,
        double *Y,int *which,const void *modules_func,const int num_modules){
    srand(time(0));static int status_init=0;
    static aai_queue *first_data=new aai_queue[FIRST_NUMBER];
    static aai_queue *second_data=new aai_queue[SECOND_NUMBER];
    static double **from_main,**first_to_first,**first_to_second,
        **second_to_second,**second_to_first,**to_main;
    static short_type *short_memory=new short_type[FIRST_NUMBER];
    int status=AAI_STATUS_SUCCESS;
    switch(flags){
        case AAI_FLAGS_INIT:{
            if(status_init)return AAI_STATUS_REPEAT_INIT;
            aai_queue::init();
            status_init=1;
            FILE* f_in=fopen("module/memory/from_main.aad","r");
            int n=FIRST_NUMBER,m=MAIN_SECOND_NUMBER;
            from_main=new double *[n];
            for(int i=0;i<n;i++)from_main[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                from_main[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&from_main[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/memory/first_to_first.aad","r");
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            first_to_first=new double *[n];
            for(int i=0;i<n;i++)first_to_first[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                first_to_first[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&first_to_first[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/memory/first_to_second.aad","r");
            n=SECOND_NUMBER,m=FIRST_NUMBER;
            first_to_second=new double *[n];
            for(int i=0;i<n;i++)first_to_second[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                first_to_second[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&first_to_second[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/memory/second_to_second.aad","r");
            n=SECOND_NUMBER,m=SECOND_NUMBER;
            second_to_second=new double *[n];
            for(int i=0;i<n;i++)second_to_second[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                second_to_second[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&second_to_second[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/memory/second_to_first.aad","r");
            n=FIRST_NUMBER,m=SECOND_NUMBER;
            second_to_first=new double *[n];
            for(int i=0;i<n;i++)second_to_first[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                second_to_first[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&second_to_first[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/memory/to_main.aad","r");
            n=MAIN_SECOND_NUMBER,m=FIRST_NUMBER;
            to_main=new double *[n];
            for(int i=0;i<n;i++)to_main[i]=new double[m];
            if(!f_in)for(int i=0;i<n;i++)for(int j=0;j<m;j++)
                to_main[i][j]=rand()%(2*MAX_INIT_WEIGHT+1)-MAX_INIT_WEIGHT;
            else{
                for(int i=0;i<n;i++)for(int j=0;j<m;j++)fscanf(f_in,"%lf",&to_main[i][j]);
                fclose(f_in);
            }
            f_in=fopen("module/memory/first_data.aad","r");
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
            f_in=fopen("module/memory/short_memory.aad","r");
            char *st=new char[SHORT_LENGTH+10];
            if(f_in){
                for(int i=0;i<n;i++){
                    fscanf(f_in,"%s",st);
                    short_type reg(strrev(st));
                    short_memory[i]|=reg;
                }
                fclose(f_in);
            }
            f_in=fopen("module/memory/second_data.aad","r");
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
            for(int i=0;i<n;i++){
                sprintf(st,"module/memory/long/%d.aad",i);
                f_in=fopen(st,"r");
                if(f_in)fclose(f_in);
                else{
                    f_in=fopen(st,"w");
                    for(int j=0;j<LONG_LENGTH;j++)fprintf(f_in,"0");
                    fprintf(f_in,"\n");
                    fclose(f_in);
                }
            }
            delete[] st;
            break;
        }
        case AAI_FLAGS_COMPUTE:{
            *which=AAI_COMPUTE_SECOND;
            double *first_X=new double [FIRST_NUMBER],*first_Y=new double [FIRST_NUMBER];
            double *second_X=new double [SECOND_NUMBER],*second_Y=new double [SECOND_NUMBER];
            for(int i=0;i<FIRST_NUMBER;i++)first_X[i]=first_data[i].pop(NULL)+(first_Y[i]=0);
            for(int i=0;i<SECOND_NUMBER;i++)second_X[i]=second_data[i].pop(NULL)+(second_Y[i]=0);
            int n=FIRST_NUMBER,m=MAIN_SECOND_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=from_main[i][j]*main2[j].value_top(NULL);
            n=MAIN_SECOND_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)Y[i]+=to_main[i][j]*first_X[j];
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=first_to_first[i][j]*first_X[j];
            n=SECOND_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)second_Y[i]+=first_to_second[i][j]*first_X[j];
            n=SECOND_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)second_Y[i]+=second_to_second[i][j]*second_X[j];
            n=FIRST_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=second_to_first[i][j]*second_X[j];
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                m=(sigma(first_Y[i])*2-1)*SHORT_LENGTH;
                if(!m){first_data[i].push(0);continue;}
                if(m<0)short_memory[i].flip((m*=-1)-1);
                first_data[i].push(short_memory[i][m-1]);
            }
            n=SECOND_NUMBER;
            fstream f_long;
            char *st=new char[50],buf;
            for(int i=0;i<n;i++){
                sprintf(st,"module/memory/long/%d.aad",i);
                m=(sigma(second_Y[i])*2-1)*LONG_LENGTH;
                if(!m){second_data[i].push(0);continue;}
                f_long.open(st,ios::binary|ios::out|ios::in);
                if(m<0){
                    f_long.seekp((m*=-1)-1,ios::beg);
                    f_long.read(&buf,sizeof(char));
                    (buf=='0')?buf='1':buf='0';
                    f_long.seekp(m-1,ios::beg);
                    f_long.write(&buf,sizeof(char));
                }
                f_long.seekp(m-1,ios::beg);
                f_long.read(&buf,sizeof(char));
                second_data[i].push(buf-'0');
                f_long.close();
            }
            delete[] first_X;delete[] second_X;
            delete[] first_Y;delete[] second_Y;
            delete[] st;
            break;
        }
        case AAI_FLAGS_FINISH:{
            aai_queue::finish();
            FILE* f_out=fopen("module/memory/from_main.aad","w");
            int n=FIRST_NUMBER,m=MAIN_SECOND_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",from_main[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/first_to_first.aad","w");
            n=FIRST_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",first_to_first[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/first_to_second.aad","w");
            n=SECOND_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",first_to_second[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/second_to_second.aad","w");
            n=SECOND_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",second_to_second[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/second_to_first.aad","w");
            n=FIRST_NUMBER,m=SECOND_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",second_to_first[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/to_main.aad","w");
            n=MAIN_SECOND_NUMBER,m=FIRST_NUMBER;
            for(int i=0;i<n;i++){
                for(int j=0;j<m;j++)fprintf(f_out,"%lf ",to_main[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/first_data.aad","w");
            n=FIRST_NUMBER;
            int tim;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=first_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",first_data[i].pop_no_decay(NULL));
                fprintf(f_out,"%lf\n",first_data[i].get_sum(NULL));
            }
            fclose(f_out);
            f_out=fopen("module/memory/short_memory.aad","w");
            for(int i=0;i<n;i++){
                for(int j=0;j<SHORT_LENGTH;j++)fprintf(f_out,"%d",short_memory[i][j]);
                fprintf(f_out,"\n");
            }
            fclose(f_out);
            f_out=fopen("module/memory/second_data.aad","w");
            n=SECOND_NUMBER;
            for(int i=0;i<n;i++){
                fprintf(f_out,"%d ",(tim=second_data[i].time_length()));
                for(int j=0;j<tim;j++)fprintf(f_out,"%lf ",second_data[i].pop_no_decay(NULL));
                fprintf(f_out,"%lf\n",second_data[i].get_sum(NULL));
            }
            fclose(f_out);
            delete[] first_data;
            delete[] second_data;
            delete[] short_memory;
            for(int i=0;i<MAIN_SECOND_NUMBER;i++)delete[] from_main[i];delete[] from_main;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] to_main[i];delete[] to_main;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] first_to_first[i];delete[] first_to_first;
            for(int i=0;i<SECOND_NUMBER;i++)delete[] first_to_second[i];delete[] first_to_second;
            for(int i=0;i<SECOND_NUMBER;i++)delete[] second_to_second[i];delete[] second_to_second;
            for(int i=0;i<FIRST_NUMBER;i++)delete[] second_to_first[i];delete[] second_to_first;
            break;
        }
        case AAI_FLAGS_PUNISH:{
            int n=FIRST_NUMBER,m=MAIN_SECOND_NUMBER;double x;
            for(int j=0;j<m;j++){
                x=power(main2[j].value_now(NULL),AAI_FLAGS_PUNISH);
                for(int i=0;i<n;i++)from_main[i][j]*=x;
            }
            m=FIRST_NUMBER;
            for(int j=0;j<m;j++){
                x=power(first_data[j].value_now(NULL),AAI_FLAGS_PUNISH);
                n=FIRST_NUMBER;
                for(int i=0;i<n;i++)first_to_first[i][j]*=x;
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)first_to_second[i][j]*=x;
                n=MAIN_SECOND_NUMBER;
                for(int i=0;i<n;i++)to_main[i][j]*=x;
            }
            m=SECOND_NUMBER;
            for(int j=0;j<m;j++){
                x=power(second_data[j].value_now(NULL),AAI_FLAGS_PUNISH);
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)second_to_second[i][j]*=x;
                n=FIRST_NUMBER;
                for(int i=0;i<n;i++)second_to_first[i][j]*=x;
            }
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++)first_data[i].shorter();
            n=SECOND_NUMBER;
            for(int i=0;i<n;i++)second_data[i].shorter();
            break;
        }
        case AAI_FLAGS_REWARD:{
            int n=FIRST_NUMBER,m=MAIN_SECOND_NUMBER;double x;
            for(int j=0;j<m;j++){
                x=power(main2[j].value_now(NULL),AAI_FLAGS_REWARD);
                for(int i=0;i<n;i++)from_main[i][j]*=x;
            }
            m=FIRST_NUMBER;
            for(int j=0;j<m;j++){
                x=power(first_data[j].value_now(NULL),AAI_FLAGS_REWARD);
                n=FIRST_NUMBER;
                for(int i=0;i<n;i++)first_to_first[i][j]*=x;
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)first_to_second[i][j]*=x;
                n=MAIN_SECOND_NUMBER;
                for(int i=0;i<n;i++)to_main[i][j]*=x;
            }
            m=SECOND_NUMBER;
            for(int j=0;j<m;j++){
                x=power(second_data[j].value_now(NULL),AAI_FLAGS_REWARD);
                n=SECOND_NUMBER;
                for(int i=0;i<n;i++)second_to_second[i][j]*=x;
                n=FIRST_NUMBER;
                for(int i=0;i<n;i++)second_to_first[i][j]*=x;
            }
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++)first_data[i].longer();
            n=SECOND_NUMBER;
            for(int i=0;i<n;i++)second_data[i].longer();
            break;
        }
    }
    return status;
}
}
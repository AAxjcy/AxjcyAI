#define DLL_EXPORTS

#include"../include/universal.hpp"

#define FIRST_NUMBER 100
#define OUTPUT_NUMBER 1

const char *str_module="auto_command";

using namespace std;

int auto_adjust(double x,const func_point *modules_func,const int num_modules){
    return AAI_STATUS_SUCCESS;
}

extern "C"{
AAI_DLL_EXPORT int auto_command(const int flags,aai_queue *main1,aai_queue *main2,aai_queue *main3,
        double *Y,int *which,const void *modules_func,const int num_modules){
    srand(time(0));static int status_init=0;
    static aai_queue *first_data;
    // static aai_queue *output_data=new aai_queue[OUTPUT_NUMBER];
    static double output_data;
    static double **from_main,**first_to_output,**first_to_first;
    int status=AAI_STATUS_SUCCESS;
    switch(flags){
        case AAI_FLAGS_INIT:{
            if(status_init)return AAI_STATUS_REPEAT_INIT;
            aai_queue::init();
            status_init=1;
            read_weight(str_module,"from_main",FIRST_NUMBER,FIRST_NUMBER,from_main);
            read_weight(str_module,"first_to_first",FIRST_NUMBER,FIRST_NUMBER,first_to_first);
            read_weight(str_module,"first_to_output",OUTPUT_NUMBER,FIRST_NUMBER,first_to_output);
            read_data(str_module,"first_data",FIRST_NUMBER,first_data);
            FILE *f_in=fopen("module/auto_command/output_data.aad","r");
            if(!f_in)output_data=0;
            else{
                fscanf(f_in,"%lf",&output_data);
                fclose(f_in);
            }
            break;
        }
        case AAI_FLAGS_COMPUTE:{
            // main2[0].print();
            // cout<<main2[0].value_top(NULL)<<endl;
            // cout<<main2<<endl;
            *which=AAI_COMPUTE_NONE;
            int n=FIRST_NUMBER,m=FIRST_NUMBER;
            double *first_X=new double [n],*first_Y=new double [n];
            for(int i=0;i<n;i++)first_X[i]=first_data[i].pop(NULL)+(first_Y[i]=0);
            // cout<<"<<<<<<<<<<<<<<<<<<<<<"<<endl;
            // for(int i=0;i<m;i++)cout<<main2[i].value_top(NULL)<<' ';cout<<endl;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=from_main[i][j]*main2[j].value_top(NULL);
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=first_to_first[i][j]*first_X[j];
            for(int i=0;i<n;i++)first_data[i].push(sigma(first_Y[i]));
            n=OUTPUT_NUMBER,m=FIRST_NUMBER;
            output_data=0;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)output_data+=first_to_output[i][j]*first_X[j];
            status=auto_adjust(output_data,(const func_point *)modules_func,num_modules);
            delete[] first_X;delete[] first_Y;
            break;
        }
        case AAI_FLAGS_FINISH:{
            aai_queue::finish();
            write_weight(str_module,"from_main",FIRST_NUMBER,FIRST_NUMBER,from_main);
            write_weight(str_module,"first_to_first",FIRST_NUMBER,FIRST_NUMBER,first_to_first);
            write_weight(str_module,"first_to_output",OUTPUT_NUMBER,FIRST_NUMBER,first_to_output);
            write_data(str_module,"first_data",FIRST_NUMBER,first_data);
            FILE *f_out=fopen("module/auto_command/output_data.aad","w");
            fprintf(f_out,"%lf\n",output_data);
            fclose(f_out);
            // delete[] first_data;
            // for(int i=0;i<FIRST_NUMBER;i++)delete[] from_main[i];delete[] from_main;
            // for(int i=0;i<FIRST_NUMBER;i++)delete[] first_to_first[i];delete[] first_to_first;
            // for(int i=0;i<OUTPUT_NUMBER;i++)delete[] first_to_output[i];delete[] first_to_output;
            break;
        }
        case AAI_FLAGS_PUNISH:{
            // cout<<"----------------"<<endl;
            int n=FIRST_NUMBER,m=FIRST_NUMBER;double x;
            for(int j=0;j<m;j++){
                x=power(main2[j].value_now(NULL),AAI_FLAGS_PUNISH);
                for(int i=0;i<n;i++)from_main[i][j]*=x;
            }
            for(int j=0;j<m;j++){
                x=power(first_data[j].value_now(NULL),AAI_FLAGS_PUNISH);
                for(int i=0;i<n;i++)first_to_first[i][j]*=x;
                n=OUTPUT_NUMBER;
                for(int i=0;i<n;i++)first_to_output[i][j]*=x;
            }
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++)first_data[i].shorter();
            // n=OUTPUT_NUMBER;
            // for(int i=0;i<n;i++)output_data[i].shorter();
            break;
        }
        case AAI_FLAGS_REWARD:{
            int n=FIRST_NUMBER,m=FIRST_NUMBER;double x;
            for(int j=0;j<m;j++){
                x=power(main2[j].value_now(NULL),AAI_FLAGS_REWARD);
                for(int i=0;i<n;i++)from_main[i][j]*=x;
            }
            for(int j=0;j<m;j++){
                x=power(first_data[j].value_now(NULL),AAI_FLAGS_REWARD);
                for(int i=0;i<n;i++)first_to_first[i][j]*=x;
                n=OUTPUT_NUMBER;
                for(int i=0;i<n;i++)first_to_output[i][j]*=x;
            }
            n=FIRST_NUMBER;
            for(int i=0;i<n;i++)first_data[i].longer();
            // n=OUTPUT_NUMBER;
            // for(int i=0;i<n;i++)output_data[i].longer();
            break;
        }
    }
    return status;
}
}
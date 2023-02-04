#define DLL_EXPORTS

#include"../include/universal.hpp"

#define INPUT_NUMBER 1
#define FIRST_NUMBER 100
#define SECOND_NUMBER 2000
#define THIRD_NUMBER 2000

const char *str_module="in_string";

using namespace std;

wchar_t string_input(int *status){
    if(status)status=AAI_STATUS_SUCCESS;
    return 0;
}

extern "C"{
AAI_DLL_EXPORT int in_string(const int flags,aai_queue *main1,aai_queue *main2,aai_queue *main3,
        double *Y,int *which,const void *modules_func,const int num_modules){
    srand(time(0));static int status_init=0;
    static aai_queue *first_data,*second_data,*third_data;
    wchar_t input_data=0;
    static double **to_main,**input_to_first,**first_to_first,**first_to_second,
        **second_to_second,**second_to_third,**third_to_third;
    int status=AAI_STATUS_SUCCESS;
    switch(flags){
        case AAI_FLAGS_INIT:{
            if(status_init)return AAI_STATUS_REPEAT_INIT;
            aai_queue::init();
            status_init=1;
            read_weight(str_module,"to_main",MAIN_FIRST_NUMBER,THIRD_NUMBER,to_main);
            read_weight(str_module,"input_to_first",FIRST_NUMBER,INPUT_NUMBER,input_to_first);
            read_weight(str_module,"first_to_first",FIRST_NUMBER,FIRST_NUMBER,first_to_first);
            read_weight(str_module,"first_to_second",SECOND_NUMBER,FIRST_NUMBER,first_to_second);
            read_weight(str_module,"second_to_second",SECOND_NUMBER,SECOND_NUMBER,second_to_second);
            read_weight(str_module,"second_to_third",THIRD_NUMBER,SECOND_NUMBER,second_to_third);
            read_weight(str_module,"third_to_third",THIRD_NUMBER,THIRD_NUMBER,third_to_third);
            read_data(str_module,"first_data",FIRST_NUMBER,first_data);
            read_data(str_module,"second_data",SECOND_NUMBER,second_data);
            read_data(str_module,"third_data",THIRD_NUMBER,third_data);
            break;
        }
        case AAI_FLAGS_COMPUTE:{
            input_data=string_input(&status);
            if(status)return status;
            *which=AAI_COMPUTE_FIRST;
            double *first_X=new double [FIRST_NUMBER],*first_Y=new double [FIRST_NUMBER];
            double *second_X=new double [SECOND_NUMBER],*second_Y=new double [SECOND_NUMBER];
            double *third_X=new double [THIRD_NUMBER],*third_Y=new double [THIRD_NUMBER];
            for(int i=0;i<FIRST_NUMBER;i++)first_X[i]=first_data[i].pop(NULL)+(first_Y[i]=0);
            for(int i=0;i<SECOND_NUMBER;i++)second_X[i]=second_data[i].pop(NULL)+(second_Y[i]=0);
            for(int i=0;i<THIRD_NUMBER;i++)third_X[i]=third_data[i].pop(NULL)+(third_Y[i]=0);
            int n=FIRST_NUMBER,m=INPUT_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=input_to_first[i][j]*input_data;
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
            n=MAIN_FIRST_NUMBER,m=THIRD_NUMBER;
            for(int i=0;i<n;i++)for(int j=0;j<m;j++)Y[i]+=to_main[i][j]*third_X[j];
            delete[] first_X;delete[] second_X;delete[] third_X;
            delete[] first_Y;delete[] second_Y;delete[] third_Y;
            break;
        }
        case AAI_FLAGS_FINISH:{
            aai_queue::finish();
            write_weight(str_module,"to_main",MAIN_FIRST_NUMBER,THIRD_NUMBER,to_main);
            write_weight(str_module,"input_to_first",FIRST_NUMBER,INPUT_NUMBER,input_to_first);
            write_weight(str_module,"first_to_first",FIRST_NUMBER,FIRST_NUMBER,first_to_first);
            write_weight(str_module,"first_to_second",SECOND_NUMBER,FIRST_NUMBER,first_to_second);
            write_weight(str_module,"second_to_second",SECOND_NUMBER,SECOND_NUMBER,second_to_second);
            write_weight(str_module,"second_to_third",THIRD_NUMBER,SECOND_NUMBER,second_to_third);
            write_weight(str_module,"third_to_third",THIRD_NUMBER,THIRD_NUMBER,third_to_third);
            write_data(str_module,"first_data",FIRST_NUMBER,first_data);
            write_data(str_module,"second_data",SECOND_NUMBER,second_data);
            write_data(str_module,"third_data",THIRD_NUMBER,third_data);
            break;
        }
        case AAI_FLAGS_PUNISH:{
            int n=FIRST_NUMBER,m=INPUT_NUMBER;double x;
            for(int i=0;i<n;i++){
                x=power(first_data[i].value_now(NULL),AAI_FLAGS_PUNISH);
                for(int j=0;j<m;j++)input_to_first[j][i]*=x;
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
                n=MAIN_FIRST_NUMBER;
                for(int i=0;i<n;i++)to_main[i][j]*=x;
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
            int n=FIRST_NUMBER,m=INPUT_NUMBER;double x;
            for(int i=0;i<n;i++){
                x=power(first_data[i].value_now(NULL),AAI_FLAGS_REWARD);
                for(int j=0;j<m;j++)input_to_first[j][i]*=x;
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
                n=MAIN_FIRST_NUMBER;
                for(int i=0;i<n;i++)to_main[i][j]*=x;
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
// #define UNICODE
// #define _UNICODE
#include"include/universal.hpp"
#include<windows.h>
using namespace std;
char **all_modules;int num_modules=0;
func_point *modules_func;
int init(){
    aai_queue::init();
    // aai_queue::decay_pow=new double[MAX_TIME];
    // aai_queue::decay_pow[0]=1;
    // for(int t=1;t<MAX_TIME;t++)aai_queue::decay_pow[t]=aai_queue::decay_pow[t-1]*(1-DECAY_RATE);
    FILE *f_in=fopen("module/module.aad","r");
    if(!f_in)return AAI_STATUS_NO_MODULE;
    int len;int n=0;
    fseek(f_in,0,SEEK_END);len=ftell(f_in);fseek(f_in,0,SEEK_SET);
    char *reg=new char[len+20];
    // wchar_t *wide_reg=new wchar_t[len+20];
    while(fscanf(f_in,"%s",reg)!=EOF){
        if(reg[0]!='/')(num_modules)++;n++;
    }all_modules=new char*[num_modules];
    fseek(f_in,0,SEEK_SET);
    for(int i=0,j=0;i<n;i++){
        fscanf(f_in,"%s",reg);
        if(reg[0]!='/'){
            all_modules[j]=new char[strlen(reg)];
            strcpy(all_modules[j++],reg);
        }
    }
    fclose(f_in);HMODULE dll_point=NULL;
    modules_func=new func_point[num_modules];
    // cout<<num_modules<<endl;
    for(int i=0;i<num_modules;i++){
        sprintf(reg,"lib/%s.dll",all_modules[i]);
        // strcpy(reg,"lib/");
        // strcat(reg,all_modules[i]);
        // strcat(reg,".dll");
        // puts(reg);
        // MultiByteToWideChar(CP_ACP,0,reg,-1,wide_reg,MultiByteToWideChar(CP_ACP,0,reg,-1,wide_reg,0));
        // puts(reg);
        // wprintf(wide_reg);puts("");
        // dll_point=LoadLibrary(reg);
        // dll_point=LoadLibrary(wide_reg);
        dll_point=LoadLibraryA(reg);
        // puts(reg);
        if(!dll_point){
            delete[] reg;
            return AAI_STATUS_NO_DLL;
        }
        // puts(reg);
        // puts(all_modules[i]);
        // modules_func[i]=(func_point)GetProcAddress(dll_point,"f");
        // modules_func[i]=(func_point)GetProcAddress(dll_point,"auto_command");
        modules_func[i]=(func_point)GetProcAddress(dll_point,all_modules[i]);
        // puts(reg);
        if(!modules_func[i]){
            delete[] reg;
            return AAI_STATUS_NO_FUNCTION;
        }
        // puts(reg);
        (*modules_func[i])(AAI_FLAGS_INIT,NULL,NULL,NULL,NULL,NULL,NULL,0);
        // puts(reg);
    }
    // puts("------------------");
    delete[] reg;
    // puts("------------------");
    // delete[] wide_reg;
    // puts("------------------");
    return AAI_STATUS_SUCCESS;
}
void finish(){
    for(int i=0;i<num_modules;i++)
        (*modules_func[i])(AAI_FLAGS_FINISH,NULL,NULL,NULL,NULL,NULL,NULL,0);
    for(int i=0;i<num_modules;i++)delete[] all_modules[i];
    delete[] all_modules;delete[] modules_func;
    aai_queue::finish();
    // delete[] aai_queue::decay_pow;
}
void err_print(int status){
    switch(status){
        case AAI_STATUS_SUCCESS:return;
        case AAI_STATUS_REPEAT_INIT:
            puts("error:重复初始化");
            break;
        case AAI_STATUS_FULL_QUEUE:
            puts("error:神经元满队列");
            break;
        case AAI_STATUS_NULL_QUEUE:
            puts("error:对空神经元进行操作");
            break;
        case AAI_STATUS_NO_MODULE:
            puts("error:找不到module/module.aad");
            break;
        case AAI_STATUS_NO_DLL:
            puts("error:找不到dll");
            break;
        case AAI_STATUS_NO_FUNCTION:
            puts("error:找不到函数");
            break;
        case AAI_STATUS_ADJUST_FAILED:
            puts("error:自动调节失败");
            break;
    }
}
int main(){
    // int xxx;
    // cin>>xxx;
    int status;{
        status=init();
        // puts("------------------");
        atexit(finish);
    }
    if(status){
        err_print(status);
        system("pause");
        return 0;
    }
    for(int i=0;i<num_modules;i++)puts(all_modules[i]);
    // double *X=new double[100];int which;aai_queue *main2=new aai_queue[100];
    // for(int i=0;i<100;i++)X[i]=0;X[0]=X[1]=X[2]=1;
    // for(int i=0;i<100;i++)main2[i].push(X[i]);
    // // main2[0].print();
    // // cout<<main2[0].value_top(NULL)<<endl;
    // // cout<<main2<<endl;
    // // cout<<"<<<<<<<<<<<<<<<<<<<<<"<<endl;
    // if(xxx==0){
    //     // cout<<123<<endl;
    //     for(int i=0;i<1000;i++)
    //         (*modules_func[0])(AAI_FLAGS_COMPUTE,NULL,main2,NULL,NULL,&which,modules_func,num_modules);
    // // cout<<"<<<<<<<<<<<<<<<<<<<<<"<<endl;
    // }
    // else if(xxx==1){
    //     (*modules_func[0])(AAI_FLAGS_PUNISH,NULL,main2,NULL,NULL,NULL,NULL,0);
    //     // cout<<456<<endl;
    // }
    // else if(xxx==2){
    //     (*modules_func[0])(AAI_FLAGS_REWARD,NULL,main2,NULL,NULL,NULL,NULL,0);
    //     // cout<<456<<endl;
    // }
    // else aai_queue::pp();
    // delete[] X;delete[] main2;
    system("pause");
    return 0;
}
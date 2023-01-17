#include"include/universal.hpp"
#include<windows.h>
using namespace std;
typedef int (*func_point)(int flags,double *X1,double *X2,double *X3,double *Y,int *which);
char **all_modules;int num_modules=0;
func_point *modules_func;
int init(){
    FILE *f_in=fopen("module/module.aad","r");
    if(!f_in)return AAI_STATUS_NO_MODULE;
    int len;int n=0;
    fseek(f_in,0,SEEK_END);len=ftell(f_in);fseek(f_in,0,SEEK_SET);
    char *reg=new char[len+20];
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
    for(int i=0;i<num_modules;i++){
        strcpy(reg,"lib/");
        strcat(reg,all_modules[i]);
        strcat(reg,".dll");
        dll_point=LoadLibrary(reg);
        // dll_point=LoadLibrary("auto_command");
        if(!dll_point){
            delete[] reg;
            return AAI_STATUS_NO_DLL;
        }
        // puts(all_modules[i]);
        // modules_func[i]=(func_point)GetProcAddress(dll_point,"f");
        // modules_func[i]=(func_point)GetProcAddress(dll_point,"auto_command");
        modules_func[i]=(func_point)GetProcAddress(dll_point,all_modules[i]);
        if(!modules_func[i]){
            delete[] reg;
            return AAI_STATUS_NO_FUNCTION;
        }
        (*modules_func[i])(AAI_FLAGS_INIT,NULL,NULL,NULL,NULL,NULL);
    }
    delete[] reg;
    return AAI_STATUS_SUCCESS;
}
void finish(){
    for(int i=0;i<num_modules;i++)
        (*modules_func[i])(AAI_FLAGS_FINISH,NULL,NULL,NULL,NULL,NULL);
    for(int i=0;i<num_modules;i++)delete[] all_modules[i];
    delete[] all_modules;delete[] modules_func;
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
    int status=init();
    if(status){
        err_print(status);
        system("pause");
        return 0;
    }
    for(int i=0;i<num_modules;i++)puts(all_modules[i]);
    double *X=new double[3];int which;
    X[0]=X[1]=X[2]=1;
    (*modules_func)(AAI_FLAGS_COMPUTE,NULL,X,NULL,NULL,&which);
    cout<<which<<endl;
    delete[] X;
    // atexit(finish);
    finish();
    system("pause");
    return 0;
}
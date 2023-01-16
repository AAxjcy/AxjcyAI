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
int main(){
    int xxx=init();
    for(int i=0;i<num_modules;i++)puts(all_modules[i]);
    if(xxx){
        cout<<xxx<<endl;
        system("pause");
        return 0;
    }
    atexit(finish);
    system("pause");
    return 0;
}
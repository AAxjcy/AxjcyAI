#include"include/universal.hpp"

#define MAIN_LIST 0
#define MAIN_BUTTON 1

const char *str_module="main";

using namespace std;
char **all_modules;int num_modules=0;
func_point *modules_func;
aai_queue *first_data,*second_data,*third_data;
double **first_to_first,**first_to_second,**second_to_second,**second_to_third,**third_to_third;
int *list_to_function,num_list=0;
int status=0;
char window_close=0,*opened_window;
int init(){
    aai_queue::init();
    if(!PathFileExistsA("./module/"))CreateDirectoryA("./module/",NULL);
    FILE *f_in=fopen("module/module.aad","a+");
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
            if(strlen(reg)>3)
                if(reg[0]=='i'&&reg[1]=='n'&&reg[2]=='_')num_list++;
            if(strlen(reg)>4)
                if(reg[0]=='o'&&reg[1]=='u'&&reg[2]=='t'&&reg[3]=='_')num_list++;
        }
    }
    fclose(f_in);HMODULE dll_point=NULL;
    modules_func=new func_point[num_modules];
    list_to_function=new int[num_list];int inl=0;
    opened_window=new char[num_list];memset(opened_window,0,sizeof(char)*num_list);
    for(int i=0;i<num_modules;i++){
        if(strlen(all_modules[i])>3)
            if(all_modules[i][0]=='i'&&all_modules[i][1]=='n'&&all_modules[i][2]=='_')list_to_function[inl++]=i;
        if(strlen(all_modules[i])>4)
            if(all_modules[i][0]=='o'&&all_modules[i][1]=='u'&&
                all_modules[i][2]=='t'&&all_modules[i][3]=='_')list_to_function[inl++]=i;
        sprintf(reg,"lib/%s.dll",all_modules[i]);
        dll_point=LoadLibraryA(reg);
        if(!dll_point){
            delete[] reg;
            return AAI_STATUS_NO_DLL;
        }
        modules_func[i]=(func_point)GetProcAddress(dll_point,all_modules[i]);
        if(!modules_func[i]){
            delete[] reg;
            return AAI_STATUS_NO_FUNCTION;
        }
    }
    for(int i=0;i<num_modules;i++){
        system("cls");
        puts("??????????????????????");
        int had=50.0*i/(num_modules+1);
        for(int j=0;j<had;j++)putchar('=');
        for(int j=had;j<50;j++)putchar(' ');
        printf("|%d/%d %s\n",i,num_modules+1,all_modules[i]);
        status=(*modules_func[i])(AAI_FLAGS_INIT,NULL,NULL,NULL,NULL,NULL,NULL,0);
        if(status)return status;
    }
    system("cls");
    puts("??????????????????????");
    int had=50.0*num_modules/(num_modules+1);
    for(int i=0;i<had;i++)putchar('=');
    for(int i=had;i<50;i++)putchar(' ');
    printf("|%d/%d main\n",num_modules,num_modules+1);
    read_weight(str_module,"first_to_first",MAIN_FIRST_NUMBER,MAIN_FIRST_NUMBER,first_to_first);
    read_weight(str_module,"first_to_second",MAIN_SECOND_NUMBER,MAIN_FIRST_NUMBER,first_to_second);
    read_weight(str_module,"second_to_second",MAIN_SECOND_NUMBER,MAIN_SECOND_NUMBER,second_to_second);
    read_weight(str_module,"second_to_third",MAIN_THIRD_NUMBER,MAIN_SECOND_NUMBER,second_to_third);
    read_weight(str_module,"third_to_third",MAIN_THIRD_NUMBER,MAIN_THIRD_NUMBER,third_to_third);
    read_data(str_module,"first_data",MAIN_FIRST_NUMBER,first_data);
    read_data(str_module,"second_data",MAIN_SECOND_NUMBER,second_data);
    read_data(str_module,"third_data",MAIN_THIRD_NUMBER,third_data);
    system("cls");
    puts("??????????????????????");
    for(int i=0;i<50;i++)putchar('=');
    printf("|%d/%d\n",num_modules+1,num_modules+1);
    puts("????????????????");
    delete[] reg;
    return AAI_STATUS_SUCCESS;
}
void compute(){
    double *first_X=new double[MAIN_FIRST_NUMBER],*first_Y=new double[MAIN_FIRST_NUMBER];
    double *second_X=new double[MAIN_SECOND_NUMBER],*second_Y=new double[MAIN_SECOND_NUMBER];
    double *third_X=new double[MAIN_THIRD_NUMBER],*third_Y=new double[MAIN_THIRD_NUMBER];
    double *Y=new double[MAIN_SECOND_NUMBER];int which=0;
    memset(first_Y,0,sizeof(double)*MAIN_FIRST_NUMBER);
    memset(second_Y,0,sizeof(double)*MAIN_SECOND_NUMBER);
    memset(third_Y,0,sizeof(double)*MAIN_THIRD_NUMBER);
    for(int i=0;i<num_modules;i++){
        memset(Y,0,sizeof(double)*MAIN_SECOND_NUMBER);
        status=(*modules_func[i])(AAI_FLAGS_COMPUTE,first_data,second_data,third_data,Y,&which,modules_func,num_modules);
        switch(which){
            case AAI_COMPUTE_NONE:break;
            case AAI_COMPUTE_FIRST:
                for(int j=0;j<MAIN_FIRST_NUMBER;j++)first_Y[j]+=Y[j];
                break;
            case AAI_COMPUTE_SECOND:
                for(int j=0;j<MAIN_SECOND_NUMBER;j++)second_Y[j]+=Y[j];
                break;
            case AAI_COMPUTE_THIRD:
                for(int j=0;j<MAIN_THIRD_NUMBER;j++)third_Y[j]+=Y[j];
                break;
        }
    }
    for(int i=0;i<MAIN_FIRST_NUMBER;i++)first_X[i]=first_data[i].pop(NULL);
    for(int i=0;i<MAIN_SECOND_NUMBER;i++)second_X[i]=second_data[i].pop(NULL);
    for(int i=0;i<MAIN_THIRD_NUMBER;i++)third_X[i]=third_data[i].pop(NULL);
    int n=MAIN_FIRST_NUMBER,m=MAIN_FIRST_NUMBER;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)first_Y[i]+=first_to_first[i][j]*first_X[j];
    for(int i=0;i<n;i++)first_data[i].push(tanh(first_Y[i]));
    n=MAIN_SECOND_NUMBER,m=MAIN_FIRST_NUMBER;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)second_Y[i]+=first_to_second[i][j]*first_X[j];
    n=MAIN_SECOND_NUMBER,m=MAIN_SECOND_NUMBER;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)second_Y[i]+=second_to_second[i][j]*second_X[j];
    for(int i=0;i<n;i++)second_data[i].push(tanh(second_Y[i]));
    n=MAIN_THIRD_NUMBER,m=MAIN_SECOND_NUMBER;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)third_Y[i]+=second_to_third[i][j]*second_X[j];
    n=MAIN_THIRD_NUMBER,m=MAIN_THIRD_NUMBER;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)third_Y[i]+=third_to_third[i][j]*third_X[j];
    for(int i=0;i<n;i++)third_data[i].push(tanh(third_Y[i]));
    delete[] first_X;delete[] second_X;delete[] third_X;
    delete[] first_Y;delete[] second_Y;delete[] third_Y;
    delete[] Y;
}
void finish(){
    for(int i=0;i<num_modules;i++)
        (*modules_func[i])(AAI_FLAGS_FINISH,NULL,NULL,NULL,NULL,NULL,NULL,0);
    for(int i=0;i<num_modules;i++)delete[] all_modules[i];
    delete[] all_modules;delete[] modules_func;delete[] list_to_function;
    write_weight(str_module,"first_to_first",MAIN_FIRST_NUMBER,MAIN_FIRST_NUMBER,first_to_first);
    write_weight(str_module,"first_to_second",MAIN_SECOND_NUMBER,MAIN_FIRST_NUMBER,first_to_second);
    write_weight(str_module,"second_to_second",MAIN_SECOND_NUMBER,MAIN_SECOND_NUMBER,second_to_second);
    write_weight(str_module,"second_to_third",MAIN_THIRD_NUMBER,MAIN_SECOND_NUMBER,second_to_third);
    write_weight(str_module,"third_to_third",MAIN_THIRD_NUMBER,MAIN_THIRD_NUMBER,third_to_third);
    write_data(str_module,"first_data",MAIN_FIRST_NUMBER,first_data);
    write_data(str_module,"second_data",MAIN_SECOND_NUMBER,second_data);
    write_data(str_module,"third_data",MAIN_THIRD_NUMBER,third_data);
    aai_queue::finish();
}
void err_print(int status){
    switch(status){
        case AAI_STATUS_SUCCESS:return;
        case AAI_STATUS_REPEAT_INIT:
            puts("error:??????????");
            break;
        case AAI_STATUS_FULL_QUEUE:
            puts("error:????????????");
            break;
        case AAI_STATUS_NULL_QUEUE:
            puts("error:??????????????????");
            break;
        case AAI_STATUS_NO_DLL:
            puts("error:??????dll");
            break;
        case AAI_STATUS_NO_FUNCTION:
            puts("error:??????????");
            break;
        case AAI_STATUS_ADJUST_FAILED:
            puts("error:????????????");
            break;
        case AAI_STATUS_CREATE_WINDOW_ERROR:
            puts("error:????????????");
            break;
        case AAI_STATUS_NO_EXE:
            puts("error:??????exe");
            break;
        case AAI_STATUS_NO_ENOUGH_MEMORY:
            puts("error:????????");
            break;
    }
    system("pause");
}
void open_window(HWND hwnd,int list_number){
    opened_window[list_number]=1;
    char *reg=new char[15+strlen(all_modules[list_to_function[list_number]])];
    sprintf(reg,"%s.exe",all_modules[list_to_function[list_number]]);
    SHELLEXECUTEINFOA ShExecInfo={0};
    ShExecInfo.cbSize=sizeof(SHELLEXECUTEINFOA);
    ShExecInfo.fMask=SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd=NULL;
    ShExecInfo.lpVerb="open";
    ShExecInfo.lpFile=reg;
    ShExecInfo.lpParameters="";
    ShExecInfo.lpDirectory="bin";
    ShExecInfo.nShow=SW_SHOWNORMAL;
    ShExecInfo.hInstApp=NULL;
    ShellExecuteExA(&ShExecInfo);
    if((long long)ShExecInfo.hInstApp<=32)switch((long long)ShExecInfo.hInstApp){
        case SE_ERR_FNF:status=AAI_STATUS_NO_EXE;return;
        case SE_ERR_OOM:status=AAI_STATUS_NO_ENOUGH_MEMORY;return;
    }
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
    DWORD exit_code=0;
    GetExitCodeProcess(ShExecInfo.hProcess,&exit_code);
    status=exit_code;
    opened_window[list_number]=0;
}
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch (uMsg){
        case WM_DESTROY:{
            window_close=1;
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc=BeginPaint(hwnd,&ps);
            FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
            EndPaint(hwnd,&ps);
            return 0;
        }
        case WM_CLOSE:{
            if (MessageBoxA(hwnd,"?????????","AxjcyAI",MB_OKCANCEL)==IDOK){
                DestroyWindow(hwnd);
            }
            return 0;
        }
        case WM_COMMAND:{
            if(LOWORD(wParam)==MAIN_BUTTON){
                int *list_choice=new int[num_list];
                HWND hListBox=GetDlgItem(hwnd,MAIN_LIST);
                int len=SendMessageA(hListBox,LB_GETSELITEMS,num_list,(LPARAM)list_choice);
                for(int i=0;i<len;i++)if(!opened_window[list_choice[i]]){
                    thread thread_window(open_window,hwnd,list_choice[i]);
                    thread_window.detach();
                }
                delete[] list_choice;
            }
            if(LOWORD(wParam)==MAIN_BUTTON+1){
                compute();
            }
            return 0;
        }
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}
void main_window(){
    // ShowWindow(GetConsoleWindow(),SW_HIDE);
    HINSTANCE hInstance=GetModuleHandle(NULL);
    int nCmdShow=SW_SHOWNORMAL;
    LPTSTR szCmdLine=GetCommandLine();
    const wchar_t CLASS_NAME[]=L"AxjcyAI Window Class";
    // puts("------------------");
    WNDCLASS wc={};
    wc.lpfnWndProc=WindowProc;
    wc.hInstance=hInstance;
    wc.lpszClassName=CLASS_NAME;
    RegisterClass(&wc);
    HWND hwnd=CreateWindowEx(0,CLASS_NAME,L"AxjcyAI",
        WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,NULL);
    if(hwnd==NULL){status=AAI_STATUS_CREATE_WINDOW_ERROR;return;}
    HWND hListBox=CreateWindowEx(0,L"ListBox",NULL,WS_VISIBLE|WS_CHILD|WS_BORDER|WS_VSCROLL|LBS_HASSTRINGS|LBS_EXTENDEDSEL,
        0,0,100,200,hwnd,(HMENU)MAIN_LIST,hInstance,0);
    for (int i=0;i<num_list;i++)
        SendMessageA(hListBox,LB_ADDSTRING,0,(LPARAM)all_modules[list_to_function[i]]);
    HWND hwndButton=CreateWindowExA(0,"BUTTON","????????",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
        110,25,50,50,hwnd,(HMENU)MAIN_BUTTON,hInstance,NULL);
    HWND hwndButton2=CreateWindowExA(0,"BUTTON","????????",WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
        110,80,50,50,hwnd,(HMENU)(MAIN_BUTTON+1),hInstance,NULL);
    ShowWindow(hwnd,nCmdShow);
    MSG msg={};
    while(GetMessage(&msg,NULL,0,0)>0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // ShowWindow(GetConsoleWindow(),SW_SHOWNORMAL);
}
int main(){
    status=init();
    if(status){
        err_print(status);
        return 0;
    }
    atexit(finish);
    thread thread_window(main_window);
    thread_window.detach();
    while(!window_close){
        if(status){
            err_print(status);
            return 0;
        }
        // compute();
    }
    if(status){
        err_print(status);
        return 0;
    }
    for(int i=0;i<num_modules;i++)puts(all_modules[i]);
    // finish();
    system("pause");
    return 0;
}
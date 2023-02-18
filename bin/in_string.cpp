#include"../include/universal.hpp"
using namespace std;

const char *str_module="in_string";
const wchar_t *str_module_w=L"in_string";

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch (uMsg){
        case WM_DESTROY:{
            PostQuitMessage(0);
            return 0;
        }
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc=BeginPaint(hwnd,&ps);
            // All painting occurs here, between BeginPaint and EndPaint.
            FillRect(hdc,&ps.rcPaint,(HBRUSH)(COLOR_WINDOW+1));
            SetBkMode(hdc,TRANSPARENT);
            SetTextColor(hdc,RGB(100,100,255));
            TextOutA(hdc,0,0,str_module,strlen(str_module));
            EndPaint(hwnd,&ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int main(){
    ShowWindow(GetConsoleWindow(),SW_HIDE);
    HINSTANCE hInstance=GetModuleHandle(NULL);
    int nCmdShow=SW_SHOWNORMAL;
    LPTSTR szCmdLine=GetCommandLine();
    WNDCLASS wc={};
    wc.lpfnWndProc=WindowProc;
    wc.hInstance=hInstance;
    wc.lpszClassName=str_module_w;
    RegisterClass(&wc);
    HWND hwnd=CreateWindowEx(0,str_module_w,str_module_w,
        WS_OVERLAPPEDWINDOW|WS_VSCROLL|WS_HSCROLL,
        CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
        NULL,NULL,hInstance,NULL
    );
    if(hwnd==NULL)return AAI_STATUS_CREATE_WINDOW_ERROR;
    ShowWindow(hwnd,nCmdShow);
    MSG msg={};
    while(GetMessage(&msg,NULL,0,0)>0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // ShowWindow(GetConsoleWindow(),SW_SHOWNORMAL);
    // system("pause");
    return AAI_STATUS_SUCCESS;
}
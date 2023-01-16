#include<bits/stdc++.h>
using namespace std;
int main(){
    srand(time(0));
    FILE *f_out=fopen("from_main.aad","w");
    for(int i=0;i<100;i++){
        for(int j=0;j<4000;j++)fprintf(f_out,"%lf ",rand()%2001-1000);
        fprintf(f_out,"\n");
    }
    fclose(f_out);
    f_out=fopen("first_data.aad","w");
    for(int i=0;i<100;i++)fprintf(f_out,"%lf ",0);
    fclose(f_out);
    f_out=fopen("first_to_second.aad","w");
    for(int i=0;i<100;i++)fprintf(f_out,"%lf ",rand()%2001-1000);
    fprintf(f_out,"\n");
    for(int i=0;i<100;i++)fprintf(f_out,"%lf ",rand()%100+1);
    fclose(f_out);
    f_out=fopen("second_data.aad","w");
    fprintf(f_out,"%lf\n",0);
    fclose(f_out);
    return 0;
}
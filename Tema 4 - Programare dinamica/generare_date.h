#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NMAX 1000
#define NMIN 2
#define MAX_VALUE 100
#define MIN_VALUE 1

void generare_date(){
    FILE *fin = fopen("date.in","w");
    srand(time(0)); rand();
    int n = (int)rand()/(RAND_MAX/NMAX)+NMIN; rand();
    int m = (int)rand()/(RAND_MAX/NMAX)+NMIN;
    fprintf(fin,"%d %d\n",n,m);

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            int x = rand()/(RAND_MAX/MAX_VALUE)+MIN_VALUE; rand();
            fprintf(fin,"%d ",x);
        }
        fprintf(fin,"\n");
    }
    fclose(fin);
}
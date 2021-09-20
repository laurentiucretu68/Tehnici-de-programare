#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LOWER 1
#define UPPER 10000

typedef struct{
    int index;
    float greutate;
    float pret;
}metal_pretios;

void generare(){
    FILE *fin = fopen("date.in","w");
    srand(time(0)); rand();
    int n = rand()/(RAND_MAX/UPPER)+LOWER;
    metal_pretios *v = (metal_pretios*)malloc(n*sizeof(metal_pretios));
    float cantitate = 0;
    for (int i=0; i<n; i++){
        v[i].index = i+1;
        v[i].greutate = (float)rand()/(float)(RAND_MAX/(UPPER+1));
        v[i].pret = (float)rand()/(float)(RAND_MAX/(UPPER+1));
        cantitate += v[i].greutate;
    }
    float g = (float)rand()/(float)(RAND_MAX/(cantitate+1));
    fprintf(fin,"%d %.2f\n",n,g);
    for (int i=0; i<n; i++)
        fprintf(fin,"%d %.2f %.2f\n",v[i].index,v[i].greutate,v[i].pret);
    fclose(fin);
    free(v);
}
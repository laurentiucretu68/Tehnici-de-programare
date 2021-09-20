#include <stdio.h>
#include <stdlib.h>
#include "generare_date.h"
#include <time.h>

int n,m;
int **matrice;
int di[] = {1,1,1};
int dj[] = {-1,0,1};
int maxim;

void citire(){
    FILE *fin = fopen("date.in","r");
    fscanf(fin,"%d %d",&n,&m);
    matrice = (int**)malloc(n*sizeof(int*));
    for (int i=0; i<n; i++)
        matrice[i] = (int*)malloc(m*sizeof(int));
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            fscanf(fin,"%d",&matrice[i][j]);
    fclose(fin);
}

int valid(int i,int j){
    if (i<0 || i>=n || j<0 || j>=m)
        return 0;
    return 1;
}

void bkt(int i_curent,int j_curent,int suma){
    if (i_curent==n-1){
        if (suma>maxim)
            maxim = suma;
    }
    else{
        for (int i=0; i<3; i++){
            int i_vecin = i_curent + di[i];
            int j_vecin = j_curent + dj[i];
            if (valid(i_vecin,j_vecin)==1){
                bkt(i_vecin,j_vecin,suma+matrice[i_vecin][j_vecin]);
            }
        }
    }
}

void afisare(){
    FILE *fout = fopen("date.out","w");
    fprintf(fout,"%d ",maxim);
    fclose(fout);
}

void dezalocare(){
    for (int i=0; i<n; i++)
        free(matrice[i]);
    free(matrice);
}

int main() {
    double t = clock();
    generare_date();
    citire();
    for (int j=0; j<m; j++)
        bkt(0,j,matrice[0][j]);
    afisare();
    dezalocare();
    t = (clock()-t)/CLOCKS_PER_SEC;
    printf("%d %d %f",n,m,t);
    return 0;
}
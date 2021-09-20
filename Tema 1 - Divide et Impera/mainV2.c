#include <stdio.h>
#include <stdlib.h>
#include "generare_date.h"

void citire(int ***matrice,int *m,int *n,int *x_start,int *y_start){
    FILE *fin = fopen("date.in","r");
    fscanf(fin,"%d %d",m,n);
    *matrice = (int**)malloc(*m*sizeof(int*));
    for (int i=0; i<*m; i++)
        (*matrice)[i] = (int*)malloc(*n*sizeof(int));
    for (int i=0; i<*m; i++)
        for (int j=0; j<*n; j++)
            fscanf(fin,"%d",&(*matrice)[i][j]);
    fscanf(fin,"%d %d",x_start,y_start);
    fclose(fin);
}

void fill(int **matrice,int m,int n,int x_curent,int y_curent){
    if (matrice[x_curent][y_curent]==1)
        return;
    matrice[x_curent][y_curent] = 1;
    fill(matrice,m,n,x_curent-1,y_curent);
    fill(matrice,m,n,x_curent,y_curent+1);
    fill(matrice,m,n,x_curent+1,y_curent);
    fill(matrice,m,n,x_curent,y_curent-1);
}

void afisare(int **matrice,int m,int n){
    FILE *fout = fopen("date.out","w");
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++)
            fprintf(fout,"%d ",matrice[i][j]);
        fprintf(fout,"\n");
    }
    fclose(fout);
}

void dezalocare(int **matrice,int m){
    for (int i=0; i<m; i++)
        free(matrice[i]);
    free(matrice);
}

int main() {
    int m,n;
    int **matrice;
    int x_start,y_start;
    generare_date();
    citire(&matrice,&m,&n,&x_start,&y_start);
    fill(matrice,m,n,x_start,y_start);
    afisare(matrice,m,n);
    dezalocare(matrice,m);
    return 0;
}



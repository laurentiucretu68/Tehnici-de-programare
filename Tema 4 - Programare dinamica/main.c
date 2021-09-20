#include <stdio.h>
#include <stdlib.h>
#include "generare_date.h"

void citire(int ***matrice,int *n,int *m){
    FILE *fin = fopen("date.in","r");
    fscanf(fin,"%d %d",n,m);
    *matrice = (int**)malloc(*n*sizeof(int*));
    for (int i=0; i<*n; i++)
        (*matrice)[i] = (int*)malloc(*m*sizeof(int));
    for (int i=0; i<*n; i++)
        for (int j=0; j<*m; j++)
            fscanf(fin,"%d",&(*matrice)[i][j]);
    fclose(fin);
}

int maxim(int a,int b){
    if (a>b)
        return a;
    return b;
}

int maxim2(int a,int b,int c){
    int maxim = a;
    if (b>maxim)
        maxim = b;
    if (c>maxim)
        maxim = c;
    return maxim;
}

void dezalocare(int **matrice,int n){
    for (int i=0; i<n; i++)
        free(matrice[i]);
    free(matrice);
}

void programare_dinamica(int **matrice,int n,int m){
    int **suma;
    suma = (int**)malloc(n*sizeof(int*));
    for (int i=0; i<n; i++)
        suma[i] = (int*)calloc(m,sizeof(int));

    for (int j=0; j<m; j++)
        suma[n-1][j] = matrice[n-1][j];


    for (int i = n-2; i>=0; i--)
        for (int j=0; j<m; j++){
            if (j==0)
                suma[i][j] = matrice[i][j] + maxim(suma[i+1][j],suma[i+1][j+1]);
            if (j==m-1)
                suma[i][j] = matrice[i][j] + maxim(suma[i+1][j-1],suma[i+1][j]);
            if (j>0 && j<m-1)
                suma[i][j] = matrice[i][j] + maxim2(suma[i+1][j-1],suma[i+1][j],suma[i+1][j+1]);
        }

    int maxim = suma[0][0];
    for (int j=1; j<m; j++)
        if (maxim<suma[0][j])
            maxim = suma[0][j];


    FILE *fout = fopen("date.out","w");
    fprintf(fout,"%d",maxim);
    fclose(fout);
    dezalocare(matrice,n);
    dezalocare(suma,n);
}

int main() {
    int n,m;
    int **matrice;
    generare_date();
    citire(&matrice,&n,&m);
    programare_dinamica(matrice,n,m);
    return 0;
}

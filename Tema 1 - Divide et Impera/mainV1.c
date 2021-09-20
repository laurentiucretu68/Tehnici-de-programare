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
    *x_start = *y_start = 0;
    fclose(fin);
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

int linieUnu(int *v,int n){
    for (int i=0; i<n; i++)
        if (v[i]==1)
            return 1;
    return 0;
}

int* transformareUnu(int *v,int n){
    int prim = -1;
    int ultim = -1;
    for (int i=0; i<=n; i++)
        if (v[i]==1){
            prim = i;
            break;
        }
    for (int i=n; i>=0; i--)
        if (v[i]==1){
            ultim = i;
            break;
        }
    for (int k=prim; k<=ultim; k++)
        v[k] = 1;
    return v;
}

void divide(int **matrice,int i,int m,int n){
    if (i<0 || i>m)
        return;
    if (i == m){
        if (linieUnu(matrice[m],n)==1)
            matrice[m] = transformareUnu(matrice[m],n);
        return;
    }
    int mij= (m+i)/2;
    divide(matrice,i,mij,n);
    divide(matrice,mij+1,m,n);
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
    divide(matrice,0,m-1,n-1);
    afisare(matrice,m,n);
    dezalocare(matrice,m);
    return 0;
}


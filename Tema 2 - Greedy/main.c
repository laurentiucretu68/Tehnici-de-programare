#include <stdio.h>
#include <stdlib.h>
#include "generare_date.h"

typedef struct{
    int index;
    float greutate;
    float pret;
    float pret_gram;
}metal;

void citire(metal **v,int *n,float *g){
    FILE *fin = fopen("date.in","r");
    fscanf(fin,"%d %f",n,g);
    *v = (metal*)malloc(*n*sizeof(metal));
    for (int i=0; i<*n; i++){
        fscanf(fin,"%d %f %f",&(*v)[i].index,&(*v)[i].greutate,&(*v)[i].pret);
        (*v)[i].pret_gram = (float) (*v)[i].pret/(*v)[i].greutate;
    }
    fclose(fin);
}

void interclasare(metal *v,int st,int mij,int dr){
    int i,j,k;
    metal *aux = (metal*)malloc((dr-st+1)*sizeof(metal));
    i = st; j = mij+1; k = 0;
    while (i<=mij && j<=dr)
        if (v[i].pret_gram<v[j].pret_gram)
            aux[k++] = v[i++];
        else
            aux[k++] = v[j++];
    while (i<=mij)
        aux[k++] = v[i++];
    while (j<=dr)
        aux[k++] = v[j++];
    k = 0;
    for (i = st; i<=dr; i++)
        v[i] = aux[k++];
    free(aux);
}

void mergeSort(metal *v,int st,int dr){
    if (st<dr){
        int mij = (st+dr)/2;
        mergeSort(v,st,mij);
        mergeSort(v,mij+1,dr);
        interclasare(v,st,mij,dr);
    }
}

void greedy(metal *v,int n,float g){
    FILE *fout = fopen("date.out","w");
    float pretTotal = 0;
    float cantitateTotala = 0;
    for (int i=0; i<n; i++){
        if (cantitateTotala+v[i].greutate<=g){
            cantitateTotala += v[i].greutate;
            pretTotal += v[i].pret;
            fprintf(fout,"%d 100%%\n",v[i].index);
        }
        else{
            float cantitateFractionara = 100*(g-cantitateTotala)/v[i].greutate;
            pretTotal += (g-cantitateTotala)*v[i].pret_gram;
            cantitateTotala = g;
            fprintf(fout,"%d %f%%\n",v[i].index,cantitateFractionara);
        }
        if (cantitateTotala==g)
            break;
    }
    fprintf(fout,"%.2f",pretTotal);
    fclose(fout);
}

int main() {
    generare();
    int n;
    float g;
    metal *v;
    citire(&v,&n,&g);
    mergeSort(v,0,n-1);
    greedy(v,n,g);
    free(v);
    return 0;
}
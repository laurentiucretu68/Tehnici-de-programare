#include <stdio.h>
#include <stdlib.h>

int n,m;
int **matrice;
int lz1,lz2,cz1,cz2;
int l0,c0,l1,c1;
int di[] = {-1,0,1,0};
int dj[] = {0,1,0,-1};
int solutie;

void citire(){
    FILE *fin = fopen("date.in","r");
    fscanf(fin,"%d %d",&m,&n);
    matrice = (int**)malloc(m*sizeof(int*));
    for (int i=0; i<m; i++)
        matrice[i] = (int*)malloc(n*sizeof(int));
    for (int i=0; i<m; i++)
        for (int j=0; j<n; j++)
            fscanf(fin,"%d",&matrice[i][j]);
    fscanf(fin,"%d %d %d %d",&lz1,&lz2,&cz1,&cz2);
    fscanf(fin,"%d %d %d %d",&l0,&c0,&l1,&c1);
    fclose(fin);

    FILE *fout = fopen("date.out","w");
    fclose(fout);
}

void afisare(){
    solutie++;
    FILE *fout = fopen("date.out","a");
    fprintf(fout,"Solutia numarul %d:\n",solutie);
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            if (i==l0 && j==c0)
                fprintf(fout,"1 ");
            else
                if (matrice[i][j]==1)
                    fprintf(fout,"-1 ");
                else
                    fprintf(fout,"%d ",matrice[i][j]);
        }
        fprintf(fout,"\n");
    }
    fprintf(fout,"\n");
    fclose(fout);
}

int valid(int i,int j){
    if (i<0 || i>=m || j<0 || j>=n)
        return 0;
    if (matrice[i][j] != 0)
        return 0;
    if (i>=lz1 && i<=lz2 && j>=cz1 && j<=cz2)
        return 0;
    return 1;
}

void bkt(int i_curent,int j_curent,int k){
    if (i_curent==l1 && j_curent==c1)
        afisare();
    else{
        for (int i=0; i<4; i++){
            int i_vecin = i_curent + di[i];
            int j_vecin = j_curent + dj[i];
            if (valid(i_vecin,j_vecin)==1){
                matrice[i_vecin][j_vecin] = k+1;
                bkt(i_vecin,j_vecin,k+1);
                matrice[i_vecin][j_vecin] = 0;
            }
        }
    }
}

void dezalocare(){
    for (int i=0; i<m; i++)
        free(matrice[i]);
    free(matrice);
}

int main() {
    citire();
    matrice[l0][c0] = 1;
    bkt(l0,c0,1);
    dezalocare();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LOWER 3
#define UPPER 100

void generare_date(){
    FILE *fin = fopen("date.in","w");
    srand(time(0));
    int m = rand()%(UPPER+1)+LOWER;
    int n = rand()%(UPPER+1)+LOWER;
    fprintf(fin,"%d %d\n",m,n);

    int **matrice = (int**)malloc(m*sizeof(int*));
    for (int i=0; i<m; i++)
        matrice[i] = (int*)calloc(n,sizeof(int));

    int first_line,last_line;
    if (m==3){
        first_line = 0;
        last_line = 2;
    }
    else{
        first_line = rand()%(m-3);
        last_line = rand()%(m-first_line)+first_line;
        while (last_line-first_line<=2)
            last_line++;
    }

    int first_line_first_one, first_line_last_one;
    if (n==3){
        first_line_first_one = 0;
        first_line_last_one = 2;
    }
    else{
        first_line_first_one = rand()%(n-3);
        first_line_last_one = rand()%(n-first_line_first_one)+first_line_first_one;
        while (first_line_last_one-first_line_first_one<=2)
            first_line_last_one++;
    }
    for (int j=first_line_first_one; j<=first_line_last_one; j++)
        matrice[first_line][j] = 1;

    srand(time(0));
    int last_line_first_one, last_line_last_one;
    if (n==3){
        last_line_first_one = 0;
        last_line_last_one = 2;
    }
    else{
        last_line_first_one = rand()%(n-3);
        last_line_last_one = rand()%(n-last_line_first_one)+last_line_first_one;
        while (last_line_last_one-last_line_first_one<=2)
            last_line_last_one++;
    }
    for (int j=last_line_first_one; j<=last_line_last_one; j++)
        matrice[last_line][j] = 1;

    for (int i = first_line+1; i<last_line-1; i++)
        matrice[i][first_line_first_one] = 1;

    if (first_line_first_one < last_line_first_one){
        for (int i = first_line_first_one; i<=last_line_first_one; i++)
            matrice[last_line-1][i] = 1;
    }
    else{
        if (first_line_first_one > last_line_first_one){
            for (int i = first_line_first_one; i>=last_line_first_one; i--)
                matrice[last_line-2][i] = 1;
            matrice[last_line-1][last_line_first_one] = 1;
        }
        else
            matrice[last_line-1][first_line_first_one] = 1;
    }


    for (int i = first_line+1; i<last_line-2; i++)
        matrice[i][first_line_last_one] = 1;

    if (first_line_last_one < last_line_last_one){
        for (int i = first_line_last_one; i<=last_line_last_one; i++)
            matrice[last_line-3][i] = 1;
        for (int i = last_line-2; i<=last_line; i++)
            matrice[i][last_line_last_one] = 1;
    }
    else{
        if (first_line_last_one == last_line_last_one){
            for (int i = first_line+1; i<=last_line-1; i++)
                matrice[i][first_line_last_one] = 1;
        }
        else{
            for (int i = last_line_last_one; i<=first_line_last_one; i++)
                matrice[last_line][i] = 1;
            matrice[last_line-1][first_line_last_one] = 1;
            matrice[last_line-2][first_line_last_one] = 1;
        }
    }

    srand(time(0));
    int x_start = rand()%(last_line)+first_line+1;
    while (x_start>=last_line)
        x_start--;
    int prim;
    int ultim;
    for (int i=0; i<n; i++)
        if (matrice[x_start][i]==1 && matrice[x_start][i+1]==0){
            prim = i;
            break;
        }
    for (int i=n-1; i>=0; i--)
        if (matrice[x_start][i]==1 && matrice[x_start][i-1]==0){
            ultim = i;
            break;
        }

    srand(time(0));
    int y_start = rand()%(ultim)+prim+1;
    while (y_start>=ultim)
        y_start--;

    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++)
            fprintf(fin,"%d ",matrice[i][j]);
        fprintf(fin,"\n");
    }
    fprintf(fin,"%d %d",x_start,y_start);

    for (int i=0; i<m; i++)
        free(matrice[i]);
    free(matrice);
    fclose(fin);
}

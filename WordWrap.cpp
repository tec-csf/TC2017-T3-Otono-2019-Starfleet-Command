//Obtenido de https://www.geeksforgeeks.org/word-wrap-problem-dp-19/

#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX

//Su complejidad es O^2
int printSolution (int p[], int n);

void solveWordWrap (int l[], int n, int M)
{

        // Numero de espacios adicionales si es que existen
        int extras[n+1][n+1];


        int lc[n+1][n+1];

        // c[i] tiene el costo optimo
        int c[n+1];


        int p[n+1];

        int i, j;

        // calcular los espacios adicionales en una linea

        for (i = 1; i <= n; i++)
        {
                extras[i][i] = M - l[i-1];
                for (j = i+1; j <= n; j++)
                        extras[i][j] = extras[i][j-1] - l[j-1] - 1;
        }

        // Calcular costo de lineas tomando en cuenta los espacios
        for (i = 1; i <= n; i++)
        {
                for (j = i; j <= n; j++)
                {
                        if (extras[i][j] < 0)
                                lc[i][j] = INF;
                        else if (j == n && extras[i][j] >= 0)
                                lc[i][j] = 0;
                        else
                                lc[i][j] = extras[i][j]*extras[i][j];
                }
        }

        // Optimizar costo al mínimo posible
        c[0] = 0;
        for (j = 1; j <= n; j++)
        {
                c[j] = INF;
                for (i = 1; i <= j; i++)
                {
                        if (c[i-1] != INF && lc[i][j] != INF &&
                            (c[i-1] + lc[i][j] < c[j]))
                        {
                                c[j] = c[i-1] + lc[i][j];
                                p[j] = i;
                        }
                }
        }

        printSolution(p, n);
}

int printSolution (int p[], int n)
{
        int k;
        if (p[n] == 1)
                k = 1;
        else
                k = printSolution (p, p[n]-1) + 1;
        cout<<"Numero de linea: "<<k<<": Empieza en la palabra no. "<<p[n]<<" termina hasta la no. "<<n<<endl;

        cout << "Este algoritmo tiene complejidad de n^2 en el peor caso";
        return k;
}

int main()
{
        int l[] = {3, 2, 2, 5}; //"Palabras"
        int n = sizeof(l)/sizeof(l[0]);
        int M = 6;
        solveWordWrap (l, n, M);
        return 0;
}

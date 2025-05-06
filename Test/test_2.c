#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50
#define MAX_ARCS 100

const char *types[] = {"Ville", "Hopital", "Entrepot"};

// Matrice d'adjacence pondérée
int graphe[N][N] = {0};

// Tableai des types de sommets
const char *sommetType[N];

void genererTypes()
{
    for (int i = 0; i < N; i++)
    {
        int t = rand() % 3;
        sommetType[i] = types[t];
    }
}

void ajouterArc()
{
    int arcsAjoutes = 0;

    while (arcsAjoutes < MAX_ARCS)
    {
        int u = rand() % N;
        int v = rand() % N;

        if (u != v && graphe[u][v] == 0)
        {
            int distance = rand() % 20 + 1;
            graphe[u][v] = distance;
            arcsAjoutes++;
        }
    }
}

void afficherGraphe()
{
    printf("Types des sommets : \n");
    for (int i = 0; i < N; i++)
    {
        printf("Sommet %d : %s\n", i, sommetType[i]);
    }

    printf("\nArcs du graphe :\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (graphe[i][j] != 0)
            {
                printf("%s %d -> %s %d avec distance %d\n", sommetType[i], i, sommetType[j], j, graphe[i][j]);
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    genererTypes();
    ajouterArc();
    afficherGraphe();

    return 0;
}

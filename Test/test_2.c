#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10        // Nombre de sommets
#define MAX_ARCS 20 // Nombre maximum d'arcs

typedef enum TypeSommet
{
    VILLE,
    HOPITAL,
    ENTREPOT,
} TypeSommet;

const char *nomTypes[] = {"Ville", "Hopital", "Entrepot"};

typedef struct Sommet
{
    int id;
    TypeSommet type;
} Sommet;

// Tableau de sommets
Sommet sommets[N];

// Matrice d'adjacence pondérée
int graphe[N][N] = {0};

// Génère des types aléatoires pour les sommets
void genererSommets()
{
    for (int i = 0; i < N; i++)
    {
        sommets[i].id = i;
        if (i < (N * 0.5))
        {
            sommets[i].type = 0;
        }
        else if (i < (N * 0.75) && sommets[i].type != 1)
        {
            sommets[i].type = 1;
        }
        else
        {
            sommets[i].type = 2;
        }
    }
}

void ajouterArc(int u, int v, int distance)
{
    graphe[u][v] = distance;
}

void genererArc()
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
    printf("Types des sommets :\n");
    for (int i = 0; i < N; i++)
    {
        printf("Sommet %d : %s\n", sommets[i].id, nomTypes[sommets[i].type]);
    }

    printf("\nArcs du graphe :\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (graphe[i][j] > 0)
            {
                printf("%s %d → %s %d avec distance %d\n",
                       nomTypes[sommets[i].type], i,
                       nomTypes[sommets[j].type], j,
                       graphe[i][j]);
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    genererSommets();
    genererArc();
    afficherGraphe();

    return 0;
}

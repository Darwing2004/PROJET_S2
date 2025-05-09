#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999    // Un grand nombre pour représenter l'infini
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
            int distance = rand() % 100 + 1;
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
}

int minDistance(int distance[], int visited[])
{
    int min = INF;
    int min_index = -1;

    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

void printPath(int previous[], int j)
{
    if (previous[j] == -1)
    {
        printf("%d", j);
        return;
    }

    printPath(previous, previous[j]);
    printf(" -> %d", j);
}

void dijkstraToD(int graph[N][N], int start, int end)
{
    int distance[N];
    int visited[N] = {0};
    int previous[N];

    for (int i = 0; i < N; i++)
    {
        distance[i] = INF;
        previous[i] = -1;
    }

    distance[start] = 0;

    for (int count = 0; count < N - 1; count++)
    {
        int u = minDistance(distance, visited);
        if (u == -1)
            break;

        visited[u] = 1; // Marquer le sommet 'u' comme visité

        // Mettre à jour les distances des voisins de 'u'
        for (int v = 0; v < N; v++)
        {
            // Si 'v' est un voisin de 'u' et n'a pas été visité, et si le nouveau chemin est plus court
            if (!visited[v] && graph[u][v] != 0 && distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v]; // Met à jour la distance
                previous[v] = u;                         // Enregistre le prédécesseur de 'v'
            }
        }
    }

        if (distance[end] == INF)
    {
        printf("Il n'existe pas de entre %d et %d :\n", start, end);
    }
    else
    {
        printf("Chemin le plus court entre %d et %d :\n", start, end);
        printPath(previous, end);
        printf("\nDistance totale : %d\n", distance[end]);
    }
}

int main()
{

    int start = 0;
    int end = 5;

    srand(time(NULL));

    genererSommets();
    genererArc();
    afficherGraphe();

    // Affichage de la matrice
    printf("Matrice d'adjacence du graphe :\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", graphe[i][j]);
        }
        printf("\n");
    }

    if (start < 0 || start >= N || end < 0 || end >= N)
    {
        printf("Indices invalides. Veuillez entrer des indices entre 0 et %d.\n", N - 1);
        return 1;
    }

    dijkstraToD(graphe, start, end);

    return 0;
}

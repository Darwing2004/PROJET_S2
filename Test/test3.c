#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SOMMET_MAX 10
#include <limits.h>

typedef struct Summit_city
{
    int ID;
    char type[50];
    char nom[50];
    int population;
} Summit_city;

typedef struct Route
{
    int distance;
    int etat;
    int capacité;
} Route;

// On cherhce a définir un graphe pour pouvoir tester toutes nos fonctionnalité
typedef struct Graphe
{
    Summit_city *sommets;
    Route **chemins;
} Graphe;

void initialisation(Graphe *graphe)
{
    Graphe *graphe = malloc(sizeof(Graphe));
    if(graphe == NULL)
    {
        printf("Erreur malloc Graphe");
        exit(EXIT_FAILURE);
    }

    graphe->chemins = malloc(SOMMET_MAX * sizeof(Route));
    if(graphe->chemins == NULL)
    {
        printf("Erreur malloc Chemin");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < SOMMET_MAX; i++)
    {
        graphe->chemins = malloc(SOMMET_MAX * sizeof(Route));
    }

    for(int i = 0; i < SOMMET_MAX; i++)
    {
        for(int j = 0 ; j < SOMMET_MAX; j++)
        {
            graphe->chemins[i][j].capacité = 0;
            graphe->chemins[i][j].distance = 0;
            graphe->chemins[i][j].etat = -1;
        }
    }
}

void ajouterArete(Graphe *graphe, int u, int v, int poids)
{
    graphe->matrice[u][v] = poids;
    // Si le graphe est non orienté, décommente aussi :
    // g->adj[v][u] = poids;
}

void libererGraphe(Graphe *graphe)
{
    for (int i = 0; i < SOMMET_MAX; i++)
    {
        free(graphe->chemins[i]);
    }
    free(graphe->chemins);
    free(graphe);
}

// CEtte fonction sert a trouver le sommet qui a le poid le plus petit.
int minDistance(int distance[], bool visited[], int N)
{
    int min = INT_MAX, min_index = -1;
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

void afficher_chemin(int pred[], int j)
{
    if (pred[j] == -1)
    {
        printf("%d", j);
        return;
    }
    afficher_chemin(pred, pred[j]);
    printf(" -> %d", j);
}

void dijkstra(Graphe *graphe, int depart, int destination)
{
    int N = graphe->nbSommet;
   
    // Tableau qui stock les poids des sommets (poid : distance entre un sommet)
    int distance[N];

    // Tableau booleen qui marque si le sommet est visité ou non
    bool visited[N];

    // Tableau qui stock les predecesseurs
    int predecessor[N];

    // On initialise les tableaux
    for (int i = 0; i < N; i++)
    {
        // On met pour chaque sommet un poid infini
        distance[i] = INT_MAX;
        // On marque aucun sommet comme visité
        visited[i] = false;
        predecessor[i] = -1;
    }

    distance[depart] = 0;

    for (int i = 0; i < N - 1; i++)
    {
        //minDistance renvoie l'indice de la distance la plus petite entre le départ et le prochain sommet
        int u = minDistance(distance, visited, N);

        if (u == -1)
            break;

        // On marque le sommet comment visité
        visited[u] = true;

        for (int v = 0; v < N; v++)
        {
            if (!visited[v] && graphe->matrice[u][v] != 0 && distance[u] != INT_MAX && distance[u] + graphe->matrice[u][v] < distance[v])
            {
                distance[v] = distance[u] + graphe->matrice[u][v];
                predecessor[v] = u;
            }
        }
    }

    if (distance[destination == INT_MAX])
    {
        printf("Il n'y a pas de chemin entre %d et %d\n", depart, destination);
        printf("\n");
    }
    else
    {
        printf("Distance minimale de %d a %d est %d\n", depart, destination, distance[destination]);
        printf("Chemin : ");
        afficher_chemin(predecessor, destination);
        printf("\n");
    }
}

int main()
{
    int n = 6; // A, B, C, D, E
    Graphe *g = initialisation_matrice(n);

    ajouterArete(g, 0, 1, 2);  // A->B
    ajouterArete(g, 0, 3, 11); // A->C
    ajouterArete(g, 1, 2, 14); // B->C
    ajouterArete(g, 1, 3, 5);  // B->D
    ajouterArete(g, 1, 5, 12); // B->D
    ajouterArete(g, 2, 3, 8);  // C->D
    ajouterArete(g, 2, 4, 10); // C->E
    ajouterArete(g, 3, 4, 2);  // D->E

    // Tu peux ici appeler ton algorithme de Dijkstra avec g->adj

    dijkstra(g, 0, 4);

    libererGraphe(g);
    return 0;
}

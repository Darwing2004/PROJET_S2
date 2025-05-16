#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"

#define N 50

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

void dijkstra(Graphe *graphe, int depart, int destination)
{

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
        // minDistance renvoie l'indice de la distance la plus petite entre le départ et le prochain sommet
        int u = minDistance(distance, visited, N);

        if (u == -1)
            break;

        // On marque le sommet comment visité
        visited[u] = true;

        for (int v = 0; v < N; v++)
        {
            if (!visited[v] && graphe->chemins[u][v] != 0 && distance[u] != INT_MAX && distance[u] + graphe->chemins[u][v] < distance[v])
            {
                distance[v] = distance[u] + graphe->chemins[u][v];
                predecessor[v] = u;
            }
        }
    }

    if (distance[destination] == INT_MAX)
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
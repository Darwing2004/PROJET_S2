#include <stdio.h>
#define V 5
#define INF 9999 // Un grand nombre pour représenter l'infini

int minDistance(int distance[], int visited[])
{
    int min = INF;
    int min_index = -1;

    for (int i = 0; i < V; i++)
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
        printf("%c", 'A' + j);
        return;
    }

    printPath(previous, previous[j]);
    printf(" -> %c", 'A' + j);
}

void dijkstraToD(int graph[V][V], int start, int end)
{
    int distance[V];
    int visited[V] = {0};
    int previous[V];

    for (int i = 0; i < V; i++)
    {
        distance[i] = INF;
        previous[i] = -1;
    }

    distance[start] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(distance, visited);
        if (u == -1)
            break;

        visited[u] = 1; // Marquer le sommet 'u' comme visité

        // Mettre à jour les distances des voisins de 'u'
        for (int v = 0; v < V; v++)
        {
            // Si 'v' est un voisin de 'u' et n'a pas été visité, et si le nouveau chemin est plus court
            if (!visited[v] && graph[u][v] != INF && distance[u] + graph[u][v] < distance[v])
            {
                distance[v] = distance[u] + graph[u][v]; // Met à jour la distance
                previous[v] = u;                         // Enregistre le prédécesseur de 'v'
            }
        }
    }

    printf("Chemin le plus court de A à D :\n");
    if (distance[end] == INF)
    {
        printf("Il n'existe pas de chemin de A à D.\n");
    }
    else
    {
        printPath(previous, end);
        printf("\nDistance totale : %d\n", distance[end]);
    }
}

int main()
{
    int graph[V][V] = {
        // A   B   C   D   E
        {0, 4, 1, INF, INF},    // A
        {INF, 0, 2, 5, INF},    // B
        {INF, INF, 0, 8, 10},   // C
        {INF, INF, INF, 0, 2},  // D
        {INF, INF, INF, INF, 0} // E
    };

    int start = 1;
    int end = 4;

    // Affichage de la matrice
    printf("Matrice d'adjacence du graphe :\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }

    dijkstraToD(graph, start, end);

    return 0;

    return 0;
}

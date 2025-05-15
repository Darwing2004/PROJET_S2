#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SOMMET_MAX 10

typedef struct Summit_city
{
    char type[50];
} Summit_city;

typedef struct Route
{
    int distance;
    int etat;
    int capacite;
} Route;

// On cherhce a définir un graphe pour pouvoir tester toutes nos fonctionnalité
typedef struct Graphe
{
    Summit_city *sommets;
    Route **chemins;
} Graphe;

Graphe *Creation_Graphe()
{
    // ON initialise le graphe de base
    Graphe *graphe = malloc(sizeof(Graphe));
    if (graphe == NULL)
    {
        printf("Erreur malloc Graphe");
        exit(EXIT_FAILURE);
    }

    // On initialise les sommets
    graphe->sommets = malloc(SOMMET_MAX * sizeof(Summit_city));
    if (graphe->sommets == NULL)
    {
        printf("Erreur malloc Sommet");
        exit(EXIT_FAILURE);
    }

    // On initialise la matrice chemin pour les routes.
    graphe->chemins = malloc(SOMMET_MAX * sizeof(Route**));
    if (graphe->chemins == NULL)
    {
        printf("Erreur malloc Chemin");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SOMMET_MAX; i++)
    {
        graphe->chemins = malloc(SOMMET_MAX * sizeof(Route*));
        if (graphe->chemins[i] == NULL)
        {
            printf("Erreur malloc colonne");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < SOMMET_MAX; j++)
        {
            graphe->chemins = malloc(SOMMET_MAX * sizeof(Route));
            if (graphe->chemins[i] == NULL)
            {
                printf("Erreur malloc colonne");
            }
        }

        printf("TEST");

        return graphe;
    }

    for (int i = 0; i < SOMMET_MAX; i++)
    {
        sprintf(graphe->sommets[i].type, "Sommet_%d", i);
        for (int j = 0; j < SOMMET_MAX; j++)
        {
            graphe->chemins[i][j].capacite = 0;
            graphe->chemins[i][j].distance = 0;
            graphe->chemins[i][j].etat = 0;
        }
    }
}

int main()
{
    // Créer le graphe

    Graphe *graphe = Creation_Graphe();

    // Afficher les sommets
    for (int i = 0; i < SOMMET_MAX; i++)
    {
        printf("Sommet %d: %s\n", i, graphe->sommets[i].type);
    }

    // Libérer la mémoire allouée pour les chemins et sommets
    for (int i = 0; i < SOMMET_MAX; i++)
    {
        free(graphe->chemins[i]);
    }
    free(graphe->chemins);
    free(graphe->sommets);
    free(graphe);

    return 0;
}
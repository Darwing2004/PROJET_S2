#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structures.h"

int chemin_court[taille_max];
int longueur_chemin = 0;

int minDistance(int distance[], bool visited[], int n)
{
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

void afficher_chemin(Graphe *G, int pred[], int sommet)
{
    if (pred[sommet] == -1)
    {
        printf("%s", obtenir_nom_sommet(&G->sommets_TAB->sommets[sommet]));
        return;
    }

    afficher_chemin(G, pred, pred[sommet]);
    printf(" -> %s", obtenir_nom_sommet(&G->sommets_TAB->sommets[sommet]));
}

void dijkstra(Graphe *graphe, int depart, int destination)
{
    int n = graphe->sommets_TAB->n_sommets;
    int distance[n];
    bool visited[n];
    int predecessor[n];

    for (int i = 0; i < n; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        predecessor[i] = -1;
    }

    distance[depart] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int min = INT_MAX, u = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && distance[j] < min)
            {
                min = distance[j];
                u = j;
            }
        }

        if (u == -1) break;

        visited[u] = true;

        for (int v = 0; v < n; v++)
        {
            Route r = graphe->chemins[u][v];
            if (r.distance > 0 && r.etat > 0 && r.capacité > 0 && !visited[v])
            {
                if (distance[u] + r.distance < distance[v])
                {
                    distance[v] = distance[u] + r.distance;
                    predecessor[v] = u;
                }
            }
        }
    }

    // Reconstruction du chemin
    longueur_chemin = 0;

    if (distance[destination] == INT_MAX)
    {
        printf("Aucun chemin de %s a %s\n",
               obtenir_nom_sommet(&graphe->sommets_TAB->sommets[depart]),
               obtenir_nom_sommet(&graphe->sommets_TAB->sommets[destination]));
        return;
    }

    int current = destination;
    while (current != -1)
    {
        chemin_court[longueur_chemin++] = current;
        current = predecessor[current];
    }

    // Inversion pour avoir le chemin départ → destination
    for (int i = 0; i < longueur_chemin / 2; i++)
    {
        int tmp = chemin_court[i];
        chemin_court[i] = chemin_court[longueur_chemin - 1 - i];
        chemin_court[longueur_chemin - 1 - i] = tmp;
    }

    // Affichage console facultatif
    printf("Chemin le plus court de %s a %s (distance %d) :\n",
           obtenir_nom_sommet(&graphe->sommets_TAB->sommets[depart]),
           obtenir_nom_sommet(&graphe->sommets_TAB->sommets[destination]),
           distance[destination]);

    for (int i = 0; i < longueur_chemin; i++)
    {
        printf("%s", obtenir_nom_sommet(&graphe->sommets_TAB->sommets[chemin_court[i]]));
        if (i < longueur_chemin - 1) printf(" -> ");
    }
    printf("\n");
}


const char *obtenir_nom_sommet(Sommet *s)
{
    if (strlen(s->ville.nom) > 0)
        return s->ville.nom;
    else if (strlen(s->hopitale.nom) > 0)
        return s->hopitale.nom;
    else if (strlen(s->entrepot.nom) > 0)
        return s->entrepot.nom;
    else
        return "Inconnu";
}

void afficher_sommets_dijkstra(Graphe *G)
{
    if (!G || !G->sommets_TAB || !G->sommets_TAB->sommets)
    {
        printf("Erreur : Graphe ou sommets non initialisés\n");
        return;
    }

    printf("Sommets du graphe (%d sommets) :\n", G->sommets_TAB->n_sommets);

    for (int i = 0; i < G->sommets_TAB->taille_max_sommet; i++)
    {
        Sommet s = G->sommets_TAB->sommets[i];

        if (s.ville.etat == 1)
        {
            printf(" %s (ID %d, pop max %d)\n", s.ville.nom, s.ville.ID, s.ville.population_max);
        }
        else if (s.hopitale.etat == 1)
        {
            printf(" %s (ID %d, patients max %d)\n", s.hopitale.nom, s.hopitale.ID, s.hopitale.patients_max);
        }
        else if (s.entrepot.etat == 1)
        {
            printf(" %s (ID %d, stock : %d %s)\n",
                   s.entrepot.nom,
                   s.entrepot.ID,
                   s.entrepot.stock.quantite,
                   s.entrepot.stock.type);
        }
        else
        {
            printf(" Sommet %d detruit par le seisme !\n", i+1);
        }
    }
}
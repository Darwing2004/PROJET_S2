#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structures.h"

void dfs_groupes(Graphe *G, int sommet, bool *visite, int *groupe, int id_groupe)
{
    visite[sommet] = true;
    groupe[sommet] = id_groupe;

    for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
    {
        Route r = G->chemins[sommet][i];
        if (!visite[i] && r.distance > 0 && r.etat > 0 && r.capacité > 0)
        {
            dfs_groupes(G, i, visite, groupe, id_groupe);
        }
    }
}

int* identifier_groupes_sommets(Graphe *G, int *nb_groupes)
{
    int n = G->sommets_TAB->n_sommets;
    bool *visite = malloc(n * sizeof(bool));
    int *groupe = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        visite[i] = false;
        groupe[i] = -1;
    }

    int compteur_groupes = 0;

    for (int i = 0; i < n; i++)
    {
        if (!visite[i])
        {
            dfs_groupes(G, i, visite, groupe, compteur_groupes);
            compteur_groupes++;
        }
    }

    free(visite);
    *nb_groupes = compteur_groupes;
    return groupe;
}

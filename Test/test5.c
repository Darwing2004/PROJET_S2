#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Graphe *Creation_graphe(int nsommets)
{
    Graphe *G = malloc(sizeof(Graphe));
    if (!G) {
        perror("Erreur d'allocation mémoire pour le graphe");
        exit(EXIT_FAILURE);
    }

    G->sommets_TAB = malloc(sizeof(Tab_sommets));
    if (!G->sommets_TAB) {
        perror("Erreur d'allocation mémoire pour sommets_TAB");
        exit(EXIT_FAILURE);
    }

    G->sommets_TAB->sommets = malloc(nsommets * sizeof(Sommet_ville));
    G->sommets_TAB->n_sommets = 0;
    G->sommets_TAB->n_bats = 0;

    G->chemins = malloc(nsommets * sizeof(Route **));
    for (int i = 0; i < nsommets; i++) {
        G->chemins[i] = malloc(nsommets * sizeof(Route*));
    }

    for (int i = 0; i < nsommets; i++) {
        int sommet_aleatoire = rand() % 100;
        Sommet_ville sommet_ajoutee;
        sommet_ajoutee.ID = i;
        sommet_ajoutee.n_bats = 0;

        if (sommet_aleatoire < 50) {
            strcpy(sommet_ajoutee.type, "Ville");
            sprintf(sommet_ajoutee.nom, "Ville S%d", sommet_ajoutee.ID);
            sommet_ajoutee.population = 100000;
        }
        else if (sommet_aleatoire < 75) {
            strcpy(sommet_ajoutee.type, "Hopital");
            sprintf(sommet_ajoutee.nom, "Hopital S%d", sommet_ajoutee.ID);
            sommet_ajoutee.population = 200;
            sommet_ajoutee.etat = 100;
        }
        else {
            strcpy(sommet_ajoutee.type, "Entrepot");
            sprintf(sommet_ajoutee.nom, "Entrepot S%d", sommet_ajoutee.ID);
            sommet_ajoutee.etat = 100;
        }

        ajouter_sommet(G->sommets_TAB, G, sommet_ajoutee);
    }

    initialiser_graphe_entier(G);

    for (int i = 0; i < nsommets; i++) {
        for (int j = 0; j < nsommets; j++) {
            if (i != j && rand() % 3 == 0) {
                int distance = rand() % 100;
                creation_route(G, i, j, distance);
                creation_route(G, j, i, distance);
            }
        }
    }

    return G;
}

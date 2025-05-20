#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Vehicule flotte[MAX_VEHICULES];
int n_vehicules = 0;
Affectation affectations[MAX_VEHICULES];

// Initialisation des véhicules
void ajouter_vehicule(int capacite, const char *urgence, int priorite, int delai_max)
{
    Vehicule nouveau_vehicule;
    nouveau_vehicule.id = n_vehicules + 1; // Donne un ID unique
    nouveau_vehicule.capacite = capacite;

    strncpy(nouveau_vehicule.urgence, urgence, sizeof(nouveau_vehicule.urgence) - 1);
    nouveau_vehicule.urgence[sizeof(nouveau_vehicule.urgence) - 1] = '\0'; // pour assurer la terminaison
    
    nouveau_vehicule.priorite = priorite;
    nouveau_vehicule.delai_max = delai_max;

    // Ajoute le véhicule à la flotte
    flotte[n_vehicules] = nouveau_vehicule;
    n_vehicules++;
}

// Tri des véhicules par priorité (fonction de tri par insertion)
void trier_vehicules_par_priorite()
{
    for (int i = 1; i < n_vehicules; i++)
    {
        Vehicule temp = flotte[i];
        int j = i - 1;
        // Trie les véhicules en fonction de leur priorité
        while (j >= 0 && flotte[j].priorite < temp.priorite)
        {
            flotte[j + 1] = flotte[j];
            j--;
        }
        flotte[j + 1] = temp;
    }
}

// Fonction pour affecter les véhicules aux routes
void affecter_vehicules(Graphe *G, int ID_sommet_debut)
{
    trier_vehicules_par_priorite(); // Trie les véhicules par priorité

    for (int i = 0; i < n_vehicules; i++)
    {
        affectations[i].id_vehicule = flotte[i].id;
        affectations[i].est_affecte = 0;
        for (int j = 0; j < G->sommets_TAB->n_sommets; j++)
        {
            Route r = G->chemins[ID_sommet_debut][j];

            if (r.capacité >= flotte[i].capacite && r.etat > 0)
            {
                affectations[i].id_destination = j;
                affectations[i].est_affecte = 1;
                printf("Vehicule %d affecte de %s a %s (Urgence : %s)\n",
                       flotte[i].id,
                       obtenir_nom_sommet(&G->sommets_TAB->sommets[ID_sommet_debut]),
                       obtenir_nom_sommet(&G->sommets_TAB->sommets[j]),
                       flotte[i].urgence);
                break; // On sort après la première affectation réussie
            }
        }

        if (!affectations[i].est_affecte)
        {
            printf("Vehicule %d ne peut pas être affecte, aucune route disponible.\n", flotte[i].id);
        }
    }
}

// Affichage des affectations
void afficher_acheminement(Graphe *G, int ID_sommet_debut)
{
    printf("Affectation des vehicules depuis %s :\n", obtenir_nom_sommet(&G->sommets_TAB->sommets[ID_sommet_debut]));

    for (int i = 0; i < n_vehicules; i++)
    {
        if (affectations[i].est_affecte)
        {
            int dest = affectations[i].id_destination;
            printf("Vehicule %d (Type: %s) affecte à la route de %s a %s.\n", flotte[i].id, flotte[i].urgence, obtenir_nom_sommet(&G->sommets_TAB->sommets[ID_sommet_debut]), obtenir_nom_sommet(&G->sommets_TAB->sommets[dest]));
        }
        else
        {
            printf("Vehicule %d (Type: %s) n'a pas ete affecte à une route depuis %s.\n",
                   flotte[i].id,
                   flotte[i].urgence,
                   obtenir_nom_sommet(&G->sommets_TAB->sommets[ID_sommet_debut]));
        }
    }
}

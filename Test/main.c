#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

int main()
{
    Graphe graphe;
    Tab_sommets tab_sommets;

    // Initialiser les structures principales
    initialiser_graphe_entier(&graphe);
    printf("TEST\n");
    initialiser_tableau_batiment(&tab_sommets, 10); // par exemple 10 bâtiments
    
    // Allouer la mémoire pour les sommets dans le graphe
    graphe.sommets = malloc(taille_max * sizeof(Summit_city));
    graphe.sommets_TAB = &tab_sommets;
    tab_sommets.sommets = graphe.sommets;

    // Création de quelques sommets
    for (int i = 0; i < 4; i++)
    {
        Summit_city s;
        s.ID = i;
        sprintf(s.nom, "Ville%d", i);
        s.population = 1000 + i * 100;
        s.batiment = malloc(3 * sizeof(Bat)); // 3 bâtiments par ville

        for (int j = 0; j < 3; j++)
        {
            s.batiment[j].ID_Bat = j;
            s.batiment[j].etat = 100;
            s.batiment[j].etage = 3;
        }

        ajouter_sommet(&tab_sommets, &graphe, s);
    }

    printf("Nombre de sommets ajoutés : %d\n", tab_sommets.n_sommets);
    for (int i = 0; i < tab_sommets.n_sommets; i++)
    {
        printf("Sommet %d : %s\n", i, graphe.sommets[i].nom);
    }

    // Création de quelques routes
    creation_route(&graphe, 0, 1, 10);
    creation_route(&graphe, 1, 2, 15);
    creation_route(&graphe, 2, 3, 20);
    creation_route(&graphe, 3, 0, 25); // boucle

    // Affichage des routes
    printf("==== ROUTES INITIALES ====\n");
    afficher_route(&graphe, 0);

    // Simulation d’un séisme
    printf("\n==== SEISME ====\n");
    seisme(graphe.sommets, 0, &tab_sommets, &graphe);

    // Affichage après séisme
    printf("\n==== ROUTES APRÈS SÉISME ====\n");
    for (int i = 0; i < tab_sommets.n_sommets; i++)
    {
        afficher_route(&graphe, i);
    }

    // Vérification accessibilité
    printf("\n==== VÉRIFICATION D'ACCESSIBILITÉ ====\n");
    verifier_accessibilite(&graphe, 0);

    // Libération mémoire
    for (int i = 0; i < tab_sommets.n_sommets; i++)
    {
        free(graphe.sommets[i].batiment);
    }
    free(graphe.sommets);
    free(tab_sommets.batiments);

    printf("\nAppuyez sur une touche pour quitter...\n");
    getchar();

    return 0;
}

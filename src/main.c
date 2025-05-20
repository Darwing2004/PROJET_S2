#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

void menue_principale(Graphe *mon_graphe)
{
    int choix;
    int continuer = 1;
    int sommet_cible = -1;

    while (continuer)
    {

        printf("************************************************************\n");
        printf("******************** GRAPHE CATASTROPHE ********************\n");
        printf("************************************************************\n");

        printf("[1] AFFICHER LE GRAPHE\n");
        printf("[2] DECLENCHER LE SEISME\n");
        printf("[3] AFFICHER LES ROUTES DU GRAPHES\n");
        printf("[4] ETAT GLOBAL DU GRAPHE\n");
        printf("[5] MISSION 3 : CHEMIN VERS SOMMET IMPACTE\n");
        printf("[6] MISSION 5 : AFFECTATION DES VEHICULES\n");
        printf("[7] MISSION 2 : IDENTIFIER LES GROUPES DE SECOURS ACCESSIBLES\n");
        printf("[8] QUITTER\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            afficher_graphe_raylib(mon_graphe);
            break;
        case 2:
            sommet_cible = seisme(mon_graphe);
            break;
        case 3:
            afficher_routes(mon_graphe);
            break;
        case 4:
            afficher_graphe_global(mon_graphe);
            break;
        case 5:
            if (sommet_cible == -1)
            {
                printf("Aucun seisme n'a ete declenche.\n");
            }
            else
            {
                afficher_sommets_dijkstra(mon_graphe);
                int dep;
                printf("Entrez le sommet de depart pour envoyer les secourss :");
                scanf("%d", &dep);
                dijkstra(mon_graphe, dep - 1, sommet_cible);
                afficher_graphe_raylib_dijkstra(mon_graphe);
            }
            break;
        case 6:
            int depart;
            printf("Entrez l'ID du centre de secours : ");
            scanf("%d", &depart);
            ajouter_vehicule(10, "incendie", 1, 30);
            ajouter_vehicule(5, "evacuation", 2, 45);
            ajouter_vehicule(7, "urgence medicale", 3, 60);
            affecter_vehicules(mon_graphe, depart);
            break;
        case 7:
            afficher_groupes_connexes(mon_graphe);
            break;
        case 8:
            printf(">>> Au revoir !\n");
            continuer = 0;
            break;
        default:
            printf("Option invalide. Veuillez réessayer.\n");
            break;
        }
    }
}

int main(void)
{
    srand(time(NULL));

    Graphe *mon_graphe = creer_graphe_vide();
    initialiser_graphe_entier(mon_graphe);
    creation_sommet(mon_graphe);
    generer_route(mon_graphe);
    placer_sommets(mon_graphe);

    menue_principale(mon_graphe);

    liberer_graphe(mon_graphe);
    free(mon_graphe);
    return 0;
}

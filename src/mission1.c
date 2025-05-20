#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"

Graphe *creer_graphe_vide()
{
    Graphe *G = malloc(sizeof(Graphe));
    if (G == NULL)
    {
        printf("Erreur d'allocation mémoire pour le graphe\n");
        exit(EXIT_FAILURE);
    }
    G->sommets_TAB = NULL;
    G->chemins = NULL;
    return G;
}

void initialiser_graphe_entier(Graphe *G)
{
    G->sommets_TAB = malloc(sizeof(Tab_sommets));
    if (G->sommets_TAB == NULL)
    {
        printf("Erreur d'allocation mémoire pour les sommets\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation de la structure Tab_Sommet (structure qui stock toutes les sommets)
    G->sommets_TAB->sommets = malloc(sizeof(Sommet) * taille_max);
    if (G->sommets_TAB->sommets == NULL)
    {
        printf("Erreur d'allocation memoire pour le tableau de sommet");
        exit(EXIT_FAILURE);
    }

    G->sommets_TAB->n_sommets = 0;

    G->sommets_TAB->taille_max_sommet = taille_max;

    // Initialisation des routes
    G->chemins = malloc(sizeof(Route *) * taille_max);
    if (G->chemins == NULL)
    {
        printf("Erreur d'allocation des routes");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < taille_max; i++)
    {
        G->chemins[i] = malloc(sizeof(Route) * taille_max);
        if (G->chemins[i] == NULL)
        {
            printf("Erreur d'allocation mémoire pour les colonnes");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < taille_max; j++)
        {
            G->chemins[i][j].distance = 0;
            G->chemins[i][j].etat = -1;
            G->chemins[i][j].capacité = -1;
        }
    }
}

void creation_sommet(Graphe *graphe)
{
    if (graphe == NULL || graphe->sommets_TAB == NULL || graphe->sommets_TAB->sommets == NULL)
    {
        fprintf(stderr, "Erreur : graphe ou tableau de sommets non initialisé\n");
        return;
    }
    int compteur_ville = 1;
    int compteur_entrepot = 1;
    int compteur_hoptiale = 1;

    int total = graphe->sommets_TAB->taille_max_sommet;

    for (int i = 0; i < total; i++)
    {

        Sommet sommet = {0};

        if (i < total * 0.5)
        {
            // Création des villes
            snprintf(sommet.ville.nom, sizeof(sommet.ville.nom), "Ville%d", compteur_ville);
            sommet.ville.ID = i + 1;
            sommet.ville.population_max = 100000;
            sommet.ville.etat = 1;

            // Création des batiments
            sommet.ville.nb_bat = NOMBRE_BATIMENT;
            sommet.ville.batiment = malloc(sizeof(Bat) * NOMBRE_BATIMENT);
            if (sommet.ville.batiment == NULL)
            {
                fprintf(stderr, "Erreur d'allocation mémoire pour les bâtiments\n");
                exit(EXIT_FAILURE);
            }
            for (int j = 0; j < NOMBRE_BATIMENT; j++)
            {
                sommet.ville.batiment[j].ID_Bat = j;
                sommet.ville.batiment[j].n_bat = j;
                sommet.ville.batiment[j].capacite = 100;
                sommet.ville.batiment[j].etat = 100;
                sommet.ville.batiment[j].etage = 2;
            }

            compteur_ville++;
        }
        else if (i < taille_max * 0.75)
        {
            // Hopital
            snprintf(sommet.hopitale.nom, sizeof(sommet.hopitale.nom), "Hopitale%d", compteur_hoptiale);
            sommet.hopitale.ID = i + 1;
            sommet.hopitale.patients = 0;
            sommet.hopitale.patients_max = 5500;
            sommet.hopitale.etat = 1;

            compteur_hoptiale++;
        }
        else
        {
            snprintf(sommet.entrepot.nom, sizeof(sommet.entrepot.nom), "Entrepot%d", compteur_entrepot);
            sommet.entrepot.ID = i + 1;
            sommet.entrepot.etat = 1;
            sommet.entrepot.stock.quantite = 1000;
            strcpy(sommet.entrepot.stock.type, "Equipement_medicale");

            compteur_entrepot++;
        }

        graphe->sommets_TAB->sommets[i] = sommet;
        graphe->sommets_TAB->n_sommets++;
    }
}

void afficher_sommets(Graphe *G)
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
            printf(" Sommet %d vide ou non initialisé\n", i);
        }
    }
}

void generer_route(Graphe *G)
{
    if (!G || !G->sommets_TAB || !G->sommets_TAB->sommets)
    {
        printf("Erreur : Graphe ou sommets non initialisés\n");
        return;
    }

    int n = G->sommets_TAB->n_sommets;
    int nb_routes = 75 + rand() % 76; // On choisit entre 75 et 150 routes pour un choix plus réaliste !

    int max_routes_possibles = n * (n - 1);

    if (nb_routes > max_routes_possibles)
    {
        nb_routes = max_routes_possibles;
    }

    int route_creees = 0;

    while (route_creees < nb_routes)
    {
        int id_depart = rand() % n;
        int id_arrive = rand() % n;

        if (id_depart != id_arrive && G->chemins[id_depart][id_arrive].distance == 0)
        {
            int distance = 1 + rand() % 150;

            int capacite_valeurs[] = {1, 2, 3, 4, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 9, 10};
            int capacite = capacite_valeurs[rand() % (sizeof(capacite_valeurs) / sizeof(int))];

            G->chemins[id_depart][id_arrive].distance = distance;
            G->chemins[id_depart][id_arrive].capacité = capacite;
            G->chemins[id_depart][id_arrive].etat = 100;

            route_creees++;
        }
    }
}

const char *type_sommet(Sommet s)
{
    if (s.ville.etat == 1)
        return "Ville";
    if (s.hopitale.etat == 1)
        return "Hopital";
    if (s.entrepot.etat == 1)
        return "Entrepot";
    return "Inconnu";
}

void afficher_routes(Graphe *G)
{
    if (!G || !G->sommets_TAB || !G->sommets_TAB->sommets)
    {
        printf("Erreur : Graphe ou sommets non initialisés\n");
        return;
    }

    int n = G->sommets_TAB->n_sommets;
    printf("Liste des routes :\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (G->chemins[i][j].distance > 0)
            {
                printf("Route de %d (%s) vers %d (%s) :\n  distance = %d, capacite = %d, etat = %d\n\n",
                       i, type_sommet(G->sommets_TAB->sommets[i]),
                       j, type_sommet(G->sommets_TAB->sommets[j]),
                       G->chemins[i][j].distance,
                       G->chemins[i][j].capacité,
                       G->chemins[i][j].etat);
            }
        }
    }
}

int seisme(Graphe *G)
{
    if (G == NULL)
    {
        printf("Erreur : sommet_seisme, sommet ou graphe non initialisés\n");
        exit(EXIT_FAILURE);
    }

    // Effectuer la catstrophe sur une sommet de manière aléatoire
    int n = G->sommets_TAB->n_sommets;
    if (n == 0)
    {
        printf("Aucun sommet disponible pour le séisme.\n");
        exit(EXIT_FAILURE);
    }
    int id = rand() % n;
    Sommet *s = &G->sommets_TAB->sommets[id];
    float magnitude = 9.0; //  0.0 + (rand() / (float)RAND_MAX) * (10.0 - 0.0);
    printf("Un seisme de magnitude %.2f s'est declanche sur le sommet %s (ID %d) !! \n", magnitude, s->ville.nom, s->ville.ID);

    int seisme_impact = 0;
    if (magnitude < 5.0)
    {
        seisme_impact = 0;
    }
    else if (magnitude >= 5.0 && magnitude <= 5.9)
    {
        seisme_impact = 1;
    }
    else if (magnitude >= 6.0 && magnitude <= 6.9)
    {
        seisme_impact = 35;
    }
    else if (magnitude >= 7.0 && magnitude <= 7.9)
    {
        seisme_impact = 70;
    }
    else if (magnitude >= 8.0)
    {
        seisme_impact = 150;
    }

    // Si c'est une ville, on applique le séisme sur les bâtiments
    if (s->ville.etat == 1)
    {
        printf("Seisme sur %s (ID %d)\n", s->ville.nom, s->ville.ID);
        s->ville.etat = s->ville.etat - seisme_impact;
        if(s->ville.etat <= 0)
        {
            s->ville.etat = 0;
        }
        for (int i = 0; i < s->ville.nb_bat; i++)
        {
            s->ville.batiment[i].etat = s->ville.batiment[i].etat - seisme_impact;
            if (s->ville.batiment[i].etat <= 0)
            {
                printf("Batiment %d de %s detruit\n", s->ville.batiment[i].ID_Bat, s->ville.nom);
                s->ville.batiment[i].etat = 0;
                s->ville.batiment->n_bat--;
            }
            else
            {
                printf("Batiment %d de  %s endommage\n", s->ville.batiment[i].ID_Bat, s->ville.nom);
            }
        }
    }

    // Si c'est un hopital, on applique le séisme sur l'hôpital
    if (s->hopitale.etat == 1)
    {
        printf("Seisme sur l'%s (ID %d)\n", s->hopitale.nom, s->hopitale.ID);
        s->hopitale.etat = s->hopitale.etat - seisme_impact;
        if (s->hopitale.etat <= 0)
        {
            printf("Hopital %s detruit\n", s->hopitale.nom);
            s->hopitale.etat = 0;
        }
        else
        {
            printf("Hopital %s endommage\n", s->hopitale.nom);
        }
    }

    // si c'est un entrepot, on applique le séisme sur l'entrepot
    if (s->entrepot.etat == 1)
    {
        printf("Seisme sur l'entrepot %s (ID %d)\n", s->entrepot.nom, s->entrepot.ID);
        s->entrepot.etat = s->entrepot.etat - seisme_impact;
        if (s->entrepot.etat <= 0)
        {
            printf("Entrepot %s détruit\n", s->entrepot.nom);
            s->entrepot.etat = 0;
        }
        else
        {
            printf("Entrepot %s endommage\n", s->entrepot.nom);
        }
    }

    // On impact les routes du sommet
    for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
    {
        if (G->chemins[id][i].distance != 0)
        {
            G->chemins[id][i].etat = G->chemins[id][i].etat - seisme_impact;
            if (G->chemins[id][i].etat <= 0)
            {
                printf("Route de la %s (ID %d) vers %s (ID %d) detruite\n",
                       type_sommet(G->sommets_TAB->sommets[id]), id,
                       type_sommet(G->sommets_TAB->sommets[i]), i);
                G->chemins[id][i].etat = 0;
            }
            else
            {
                printf("Route de la %s (ID %d) vers %s (ID %d) endommage\n",
                       type_sommet(G->sommets_TAB->sommets[id]), id,
                       type_sommet(G->sommets_TAB->sommets[i]), i);
            }
        }
    }

    return id;
}

void afficher_graphe_global(Graphe *G)
{
    if (G == NULL)
    {
        printf("Erreur : graphe non initialisé\n");
        return;
    }

    int totale_ville = 0;
    int totale_hopital = 0;
    int totale_entrepot = 0;
    int totale_route = 0;
    int totale_batiment = 0;
    int batiments_morts = 0;
    int routes_detruites = 0;

    for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
    {
        Sommet *sommet = &G->sommets_TAB->sommets[i];

        // Ville
        if (sommet->ville.etat == 1 && sommet->ville.batiment != NULL)
        {
            totale_ville++;
            for (int j = 0; j < NOMBRE_BATIMENT; j++)
            {
                totale_batiment++;
                if (sommet->ville.batiment[j].etat <= 0)
                {
                    batiments_morts++;
                }
            }
        }

        // Hopital
        else if (sommet->hopitale.etat == 1)
        {
            totale_hopital++;
        }

        // Entrepôt
        else if (sommet->entrepot.etat == 1)
        {
            totale_entrepot++;
        }
    }

    // Comptage des routes (attention à ne pas doubler les arcs)
    for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
    {
        for (int j = i + 1; j < G->sommets_TAB->n_sommets; j++)
        {
            if (G->chemins[i][j].distance > 0)
            {
                totale_route++;
                if (G->chemins[i][j].etat <= 0 || G->chemins[i][j].capacité <= 0)
                    routes_detruites++;
            }
        }
    }

    // Affichage
    printf("ETAT GLOBAL DU GRAPHE :\n");
    printf(" - Villes             : %d\n", totale_ville);
    printf(" - Hopitaux           : %d\n", totale_hopital);
    printf(" - Entrepôts          : %d\n", totale_entrepot);
    printf(" - Bâtiments détruits : %d / %d\n", batiments_morts, totale_batiment);
    printf(" - Routes détruites   : %d / %d\n", routes_detruites, totale_route);
}


void liberer_graphe(Graphe *G)
{
    if (!G)
        return;

    // Libération des sommets
    if (G->sommets_TAB)
    {
        if (G->sommets_TAB->sommets)
        {
            for (int i = 0; i < G->sommets_TAB->n_sommets; i++)
            {
                Sommet *s = &G->sommets_TAB->sommets[i];

                // Libération des bâtiments si c'est une ville
                if (s->ville.etat == 1 && s->ville.batiment != NULL)
                {
                    free(s->ville.batiment);
                    s->ville.batiment = NULL;
                }
            }

            free(G->sommets_TAB->sommets);
            G->sommets_TAB->sommets = NULL;
        }

        free(G->sommets_TAB);
        G->sommets_TAB = NULL;
    }

    // Libération des chemins (matrice d'adjacence)
    if (G->chemins)
    {
        int n = G->sommets_TAB ? G->sommets_TAB->n_sommets : taille_max; // Sécurité
        for (int i = 0; i < n; i++)
        {
            if (G->chemins[i])
            {
                free(G->chemins[i]);
                G->chemins[i] = NULL;
            }
        }
        free(G->chemins);
        G->chemins = NULL;
    }

    // Optionnel : libération du pointeur Graphe fait dans le main
    // free(G); ← déjà fait dans ton main
}